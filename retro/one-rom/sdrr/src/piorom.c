// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

// RP2350 PIO/DMA autonomous ROM serving support

#include "include.h"
#include "piorom.h"

#if defined(RP_PIO)

// # Introduction

// This file contains a completely autonomous PIO and DMA based ROM serving
// implementation.  Once started, the PIO state machines and DMA channels
// serve ROM data in response to external chip select and address lines
// without any further CPU intervention.
//
// # Algorithm Summary
//
// The implementation uses three PIO state machines and 2 DMA channels, with
// the following overall operation:
// - PIO SM0 - Chip Select/Output Data Handler
// - PIO SM1 - Address Reader
// - DMA0    - Address Forwarder
// - DMA1    - Data Byte Fetcher
// - PIO SM2 - Data Byte Writer 
//
//     CS active   Data to Outputs                 CS Inactive  Data to Inputs
//             |   |                                         |  |
//             v   v                                         v  v
// SM0 ----------+-------------------------------------------------->
//     ^         |                                                  |
//     |         | (Optional IRQ0)                                  |
//     |         v                                                  |
//     |        SM1 ------> DMA0 --------> DMA1 -------> SM2        |
//     |         |            |             |             |         |
//     |         v            v             v             v         |
//     |     Read Addr  Forward Addr  Get Data Byte  Write Data     |
//     |  (Optional Loop)                                           |
//     |                                                            v
//     <-------------------------------------------------------------
//                                                   (Not to scale)
//
// # Timings
//
// It is difficult to be sure, but based on observed data, and theoretical
// estimates, the timings are estimated as follows:
// - Address valid to correct data byte is 11-14 cycles
// - Previous data valid after address change delay 14-11 cycles (although
//   it is much less than this is CS is made inactive, which is very likely)
// - CS active to data output is 5-6 cycles
// - CS inactive to data inputs is 3 cycles
//
// Physical settling time of lines will add to this.  Also, experience has
// shown that the system is likely to introduce other, unplanned for, stalls
// and other delays.  In particular if running _anything_ else, such as having
// an SWD debug probe connected, may introduce delays and jitter due to bus
// contention.
//
// At a max rated RP2350 clock speed of 150MHz this is:
// - 73-93ns from address to data
// - 33-40ns from CS active to data output
// - 20ns from CS inactive to data inputs
//
// At 50MHz:
// - 220-280ns from address to data
// - 280-220ns from previous data valid after address change
// - 100-120ns from CS active to data output
// - 60ns from CS inactive to data inputs
//
// Overclocked to 300MHz:
// - 37-47ns from address to data
// - 17-20ns from CS active to data output
// - 10ns from CS inactive to data inputs
//
// Address to data breakdown:
// - 2 cycle delay in GPIO state reaching PIO due to input-sync
// - SM1 address read 3-4 cycles:
//   - 3 is best case scenario
//   - 6 is worst case, but this "swallows" the input-sync delay, leading to 4
// - Triggering DMA via DREQ from SM1 RX FIFO 1 cycle
// - DMAs take 2-3 cycles each:
//   - 3 cycles is likely due to single cycle stall due to contention, likely
//     with other DMA channel.
//   - Assume no stall in transfer between them.
// - SM2 data byte output 1 cycle
//
// Previous data valid after address change breakdown:
// - Inverse of address to data breakdown
//
// CS active to data output breakdown:
// - 2 cycle delay in GPIO state reaching PIO due to input-sync
// - SM0 best case is 3 cycles - mov x, pins; jmp x--, N; mov pindirs, ~null
// - SM0 worst case adds 3 cycles, 2 of which "swallow" the input-sync delay
//
// CS active to inactive breakdown:
// - 2 cycle delay in GPIO state reaching PIO due to input-sync
// - SM0 best case is 3 cycles - mov x, pins; jmp !x, N; mov pindirs, null
// - SM0 worst case add 2 cycles, but these "swallow" the input-sync delay
//
// These timings do not quite add up.  The C64 character ROM is a 2332A, with
// 350ns access time - the maximum time allowed to go from address valid to
// valid.  As we can serve this ROM successfully at around 50MHz - with our
// worse cast estimate of 280ns for this time - either our estimates are wrong,
// or the C64 VIC-II requires better of the ROM than its specification - or
// both.  Worst case it seems like our estimates may be 20% under (i.e add 25%
// to them).
// 
// Therefore 50ns operation may require the RP2350 to be clocked closer to
// 400MHz than 300Mhz.  This is still likely to be within the RP2350's
// capabilities.
//
// # Detailed Operation
//
// The detailed operation is as follows:
//
// PIO0 SM0 - CS Handler
//  - (Initially ensures data pins are inputs.)
//  - Monitors the chip select lines.
//  - When all CS lines are active, optionally triggers an IRQ to signal the
//    address read SM to read the address lines.
//  - Sets the data pins to outputs after an optional delay.  The data lines
//    will not be serving the correct byte yet.
//  - Tight loops, checking for CS going inactive.
//  - When CS goes inactive again, sets data pins back to inputs and starts
//    over.
//
// PIO0 SM1 - Address Read
//  - (One time - reads high 16 bits of ROM table address from its TX FIFO.
//    This is preloaded to the TX FIFO by the CPU before starting the PIOs.)
//  - Prepares by pushing high 16 bits of ROM table address into its OSR.
//  - Optionally waits for IRQ from CS Handler SM.
//  - After optional delay (used in non-IRQ case), reads the address lines (16
//    bits) into OSR, completing the ROM table lookup address for the byte to
//    be served.
//  - Pushes the complete 32 bit ROM table lookup address into its RX FIFO 
//    (triggering DMA Channel 0).
//  - Loops back to 2nd step (pushing high 16 bits of ROM table address into
//    OSR).
//
// DMA Channel 0 - Address Forwarder
//  - Triggered by PIO0 SM1 RX FIFO using DREQ_PIO0_RX1 (SM1 RX FIFO).
//  - Reads the 32 bit ROM table lookup address from PIO0 SM1 RX FIFO.
//  - Writes the address into DMA Channel 1 READ_ADDR or READ_ADDR_TRIG
//    register.
//
// DMA Channel 1 - Data Byte Fetcher
//  - Triggered either DMA Channel 0 writing to this channels READ_ADDR_TRIG
//    or using DREQ_PIO0_RX1 (SM1 RX FIFO) - in which case this DMA is paced
//    identically to DMA Channel 0.
//  - Reads the ROM byte from the address specified in its READ_ADDR register.
//  - Writes the byte into PIO0 SM2 TX FIFO.
//  - Waits to be re-triggered by DMA Channel 0 writing to READ_ADDR_TRIG or
//    DREQ_PIO_RX1 (SM1 RX FIFO).
//
// PIO0 SM2 - Data Byte Output
//  - Waits for a data byte to become available in its TX FIFO.
//  - When data byte available, outputs the data byte on the data pins.
//  - Loops back to waiting for next data byte.
//
// There are a number of hardware pre-requisites for this to work correctly:
// - RP2350, not the RP2040.  This implementation uses:
//   - pinsdirs as a mov destination
//   - mov using pins as a source, only moving the configured "IN" pins.
//   Neither of these are supported by the RP2040's PIOs.
// - All Chip Select (or CE/OE) lines must be connected to contiguous GPIOs.
// - Any active high chip seledct lines must be inverted prior to use, by
//   using GPIO input inversion (INOVER).
// - All Data lines must be connected to contiguous GPIOs.
// - All Address lines must be connected to contiguous GPIOs, and be limited
//   to a 64KB address space.  (Strictly other powers of two could be
//   supported.)
//
// In order to minimise jitter, it is advisable to ensure the following:
// - The DMA channels have high AHB5 bus priority for both reads
//   and writes using the BUS_PRIORITY register.
// - Nothing else attempts to read or write to the 4 banks of SRAM the
//   64KB ROM table is striped across.
// - If other DMAs are enabled, the DMAs within this module should have a
//   higher priority set.
// - Nothing else accesses peripherals on the AHB5 splitter during operation.
//
// Possible enhancements:
// - May want to check CS is still active before setting data pins to outputs
//   in SM2.
//
// Note that a combined PIO/CPU implementation has also been explored (see
// PIO_CONFIG_NO_DMA).  This is discussed further below, but in summary, it
// matches DMA performance, while consuming a CPU core.
//
// # Supported PIO configuration options
//
// Note where min/max clock speeds are given below they tended to vary by
// 1-2Mhz, based on the day.  Likely due to temperature variations affecting
// the host's timing.  It is unlikely the RP2350's timing varies, given it
// has a modern, extremely accurate, clock source.
//
// For these tests, the RP2350 was not overclocked - the max supported clock
// speed it known to be higher than 150MHz for these ROMs, but there is a max
// speed, particularly for character ROMs, due to the video chip requiring a
// byte to be held after CS is dectivated.
//
// # PIO_CONFIG_DEFAULT
//
// - READ_IRQ = 1
// - ADDR_READ_DELAY = 0
//
// Here the IRQ from CS handler SM is used to trigger the address read SM.
// This works well serving a C64 charaxcter ROM at higher clock speeds
// (roughly 115-150MHz).
//
// Min/Max speeds:
// - PAL C64 Char ROM: 115-150MHz
// - PAL C64 Kernal ROM: 45-150MHz
// - PAL VIC-20 Char ROM: 44-150MHz
//
// # PIO_CONFIG_SLOW_CLOCK_KERNAL
//
// - READ_IRQ = 0
// - ADDR_READ_DELAY = 1
//
// Here 1 cycles is sufficient time to allow DMA chain to avoid backing up.
// However, the VIC-II requires a 2 cycle delay from the character ROM - see
// PIO_CONFIG_SLOW_CLOCK_CHAR.
//
// Min/Max speeds:
// - PAL C64 Kernal ROM: 41-150MHz
// - PAL VIC-20 Kernal ROM: 22-150MHz
//
// # PIO_CONFIG_SLOW_CLOCK_CHAR
//
// - READ_IRQ = 0
// - ADDR_READ_DELAY = 2
//
// Add an additional cycle of delay before reading address lines to allow the
// byte to remain on the bus slightly later, as seems to be required by a
// VIC-II chip of a character ROM
//
// Min/Max speeds:
// - PAL C64 Char ROM: 51-150MHz
// - PAL VIC-20 Char ROM: 51-150MHz

// Whether to use DMA (or instead, use the CPU to read bytes).  If set,
// ADDR_READ_IRQ is ignored.
//
// This option is not maintained any may be broken.  It was implemented to test
// which was faster - DMA or CPU.  It turns out to be identical performance -
// both serve a C64 character from down to 51MHz but no further without
// glitches.  Similarly, both serve a kernal down to 41MHz.
//
// Therefore the DMA approach has been selected as superior as it frees up the
// CPU for other applications.
//
// (Actually it is possible to implement an even more pathological assembly
// CPU loop which shaves the char ROM down to 50MHz, but it's likely fragile,
// breaking if the CPU loop ever takes an extra cycle, such as when a debug
// probe is connected.)
//
// #define PIO_CONFIG_NO_DMA  1

// Fallback default configuration
#if !defined(PIO_CONFIG_ADDR_READ_IRQ) && !defined(PIO_CONFIG_ADDR_READ_DELAY) && !defined(PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY) && !defined(PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY)
#if !defined(PIO_CONFIG_DEFAULT) && !defined(PIO_CONFIG_SLOW_CLOCK_KERNAL) && !defined(PIO_CONFIG_SLOW_CLOCK_CHAR) && !defined(PIO_CONFIG_NO_DMA)
#pragma message("No PIO config specified - using PIO_CONFIG_DEFAULT")
#define PIO_CONFIG_DEFAULT
#endif // !PIO_CONFIG_DEFAULT && !PIO_CONFIG_SLOW_CLOCK && !PIO_CONFIG_SLOW_CLOCK_CHAR
#endif // Fallback default

// Pre-defined PIO configuration options
#if defined(PIO_CONFIG_DEFAULT)
#define PIO_CONFIG_ADDR_READ_IRQ                1
#define PIO_CONFIG_ADDR_READ_DELAY              0
#define PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY      0
#define PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY  0
#elif defined(PIO_CONFIG_SLOW_CLOCK_KERNAL)
#define PIO_CONFIG_ADDR_READ_IRQ                0
#define PIO_CONFIG_ADDR_READ_DELAY              1
#define PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY      0
#define PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY  0
#elif defined(PIO_CONFIG_SLOW_CLOCK_CHAR)
#define PIO_CONFIG_ADDR_READ_IRQ                0
#define PIO_CONFIG_ADDR_READ_DELAY              2
#define PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY      0
#define PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY  0
#elif defined(PIO_CONFIG_NO_DMA)
#define PIO_CONFIG_ADDR_READ_IRQ                0
#define PIO_CONFIG_ADDR_READ_DELAY              1
#define PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY      0
#define PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY  0
#endif // PIO_CONFIG_DEFAULT

// Whether to use IRQ from CS handler to address read SM
#if !defined(PIO_CONFIG_ADDR_READ_IRQ)
#define PIO_CONFIG_ADDR_READ_IRQ  1
#endif // PIO_CONFIG_ADDR_READ_IRQ

// Whether to delay setting data pins to outputs at the start of the address
// read SM, after any optional IRQ, and, if so, by how many PIO cycles.
//
// Counter intuitively, this is useful to ensure the data remains valid longer,
// by delaying when it is actually read.  It is hard to add delays later in the
// chain, as the DMA transfers are tightly coupled to the PIO state machines.
//
// If PIO_CONFIG_ADDR_READ_IRQ=0 then this delay is essential to allow time for
// the DMA chain to process the address read before the next one.  So, set this
// to _at least_ 1 in that case.
//
// It may be that DMA Channel 0 requires only 2 cycles most of the time, but
// occassionally requires 3 (e.g. due to bus contention from the other DMA
// channel), because a C64 kernal _almost_ fully boots with both IRQ and this
// set to 0.  But not quite!
#if !defined(PIO_CONFIG_ADDR_READ_DELAY)
#define PIO_CONFIG_ADDR_READ_DELAY  0
#endif // PIO_CONFIG_ADDR_READ_DELAY

// Whether to delay setting data pins to outputs after CS goes active, and,
// if so, by how many PIO cycles.
//
// This may not be useful in practice, as ROM specifications tend to require
// that data become valid within a certain time after CS goes active - not
// that it _doesn't_ go active for a certain time.
#if !defined(PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY)
#define PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY  0
#endif // PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY

// Whether to hold data lines as outputs for a number of cycles after CS goes
// inactive, before setting them back to inputs, and, if so, by how many PIO
// cycles.
//
// This may not be useful in practice, as ROM specifications tend not to
// require a hold time after CS goes inactive.  (They do specify a hold time
// after address changes - see PIO_CONFIG_ADDR_READ_DELAY.)
#if !defined(PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY)
#define PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY  0
#endif // PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY

// Number of data and address lines
#define NUM_DATA_LINES    8
#define NUM_ADDR_LINES    16

// PIO ROM serving configuration structure
typedef struct piorom_config {
    uint8_t num_cs_pins;
    uint8_t invert_cs[3];

    uint8_t cs_base_pin;
    uint8_t data_base_pin;
    uint8_t num_data_pins;
    uint8_t addr_base_pin;
    
    uint8_t num_addr_pins;
    uint8_t addr_read_irq;
    uint8_t addr_read_delay;
    uint8_t cs_active_delay;

    uint8_t cs_inactive_delay;
    uint8_t no_dma;
    uint8_t pad[2];

    uint32_t rom_table_addr;

    uint16_t sm0_clkdiv_int;
    uint8_t sm0_clkdiv_frac;
    uint8_t pad0;

    uint16_t sm1_clkdiv_int;
    uint8_t sm1_clkdiv_frac;
    uint8_t pad1;

    uint16_t sm2_clkdiv_int;
    uint8_t sm2_clkdiv_frac;
    uint8_t pad2;
} piorom_config_t;

//
// PIO state machine programs
//

// Base instructions for SM0
#define MOV_PINDIRS_NULL        0xa063
#define MOV_X_PINS              0xa020
#define JMP_X_DEC(DEST)         (0x0040 | ((DEST) & 0x1F))
#define MOV_PINDIRS_NOT_NULL    0xa06b
#define JMP_NOT_X(DEST)         (0x0020 | ((DEST) & 0x1F))

// Optional instructions for SM0
#define IRQ_SET(X)              (0xc000 | ((X) & 0x07))
#define NOP                     0xa042

// Base instructions for SM1
#define PULL_BLOCK              0x80a0
#define MOV_X_OSR               0xa027
#define IN_X(NUM)               (0x4020 | ((NUM) & 0x1F))
#define IN_PINS(NUM)            (0x4000 | ((NUM) & 0x1F))

// Base instructions for SM2
#define MOV_PINS_NULL           0xa003
#define OUT_PINS(NUM)           (0x6000 | ((NUM) & 0x1F))

// Optional instructions for SM1
#define WAIT_IRQ_HIGH(X)        (0x20c0 | ((X) & 0x07))

// General purpose instructions

// Add a side-set delay to any instruction (max 31 cycles)
#define ADD_DELAY(INST, DELAY)  ((INST) | (((DELAY) & 0x1F) << 8))

// Clear OSR
#define OUT_NULL(X)             (0x6000 | ((X) & 0x1F))

// Clear ISR
#define IN_NULL(X)              (0x4000 | ((X) & 0x1F))

// Jump to instruction unconditionally
#define JMP(X)                  (0x0000 | ((X) & 0x1F))

// Forward declarations for debug logging functions
#if defined(DEBUG_LOGGING)
static void piorom_instruction_decoder(uint32_t instr, char out_str[64]);
static void piorom_log_pio_sm(
    const char *sm_name,
    uint8_t pio_sm,
    piorom_config_t *config,
    uint32_t *instr_scratch,
    uint8_t start,
    uint8_t wrap_bottom,
    uint8_t wrap_top
);
#endif // DEBUG_LOGGING

// SM0 - CS Handler
//
// The program is constructed dynamically in pio_load_programs().  The overall
// algorithm is as follows:
//
// .wrap_target                      ; Start of CS loop
// 0xa063, //  mov    pindirs, null  ; set data pins to inputs
// 0xa020, //  mov    x, pins        ; read CS lines
// 0x0041, //  jmp    x--, 1         ; CS inactive, loop back to re-read CS
//                                   ; Note the decrement of x is unused -
//                                   ; but there is no jmp x instruction
// 0xc000, //  irq    set 0 [N]      ; OPTIONAL: signal CS active to address
//                                   ; read SM
//                                   ; OPTIONAL: N cycle delay before setting
//                                   ; data pins to outputs
// 0xaN42, //  nop    [N]            ; OPTIONAL: N cycle delay before setting
//                                   ; data pins to outputs (if not on irq)
// 0xa06b, //  mov    pindirs, ~null ; set data pins to output
// 0xa020, //  mov    x, pins        ; read CS lines again
// 0x002Y, //  jmp    !x, Y [N]      ; CS still active, if so jump back one
//                                   ; instruction.
// 0xaN42, //  nop    [N]            ; OPTIONAL: N cycle delay before setting
//                                   ; data pins to inputs

// .wrap                             ; End of CS loop 

// SM1 - Address Read
//
// The program is constructed dynamically in pio_load_programs().  The overall
// algorithm is as follows:
//
// ; One time setup - get high word of ROM table address from TX FIFO.  This
// ; is 0x2001 as of v0.5.5.
// pull   block         ; get high word of ROM table address
// mov    x, osr        ; store high word in X
//
// .wrap_target         ; Start of address read loop
// in     x, 16         ; read high address bits from X
// wait   1 irq, 0 [N]  ; OPTIONAL: wait for CS to go active (and clears IRQ)
//                      ; OPTIONAL: N cycle delay after IRQ before reading
//                      ; address
// in     pins, 16      ; read address lines (autopush)
// .wrap                ; End of address read loop

// SM2 - Data Byte Output
//
// The program is constructed dynamically in pio_load_programs().  The overall
// algorithm is as follows:
//
// .wrap_target
// out    pins, 8       ; Auto-pulls byte from TX FIFO (from DMA Channel 1)
//                      ; and outputs on data pins
// .wrap

// Loads the PIO programs into the PIO instruction memory.
//
// Constructs all state machine instructions dynamically based on the config.
static void piorom_load_programs(piorom_config_t *config) {
    volatile pio_sm_reg_t *sm_reg;
    uint8_t offset = 0;
    uint8_t num_cs_pins = config->num_cs_pins;
    uint8_t cs_base_pin = config->cs_base_pin;
    uint8_t num_data_pins = config->num_data_pins;
    uint8_t data_base_pin = config->data_base_pin;
    uint8_t num_addr_pins = config->num_addr_pins;
    uint8_t addr_base_pin = config->addr_base_pin;
    uint32_t rom_table_addr = config->rom_table_addr;
    uint8_t addr_read_irq = config->addr_read_irq;
    uint8_t addr_read_delay = config->addr_read_delay;
    uint8_t cs_active_delay = config->cs_active_delay;
    uint8_t no_dma = config->no_dma;
    uint32_t instr_scratch[32];

    // Clear all PIO0 IRQs
    PIO0_IRQ = 0x000000FF;

    //
    // SM0 - CS handler
    //

    // Load the CS handler program
    uint8_t sm0_start = offset;
    uint8_t sm0_wrap_bottom = offset;
    instr_scratch[offset++] = MOV_PINDIRS_NULL;
    uint8_t load_cs_offset = offset;
    instr_scratch[offset++] = MOV_X_PINS;
    instr_scratch[offset++] = JMP_X_DEC(load_cs_offset);
    if (addr_read_irq) {
        if (!cs_active_delay) {
            instr_scratch[offset++] = IRQ_SET(0);
        } else {
            instr_scratch[offset++] = ADD_DELAY(IRQ_SET(0), cs_active_delay);
        }
    } else {
        if (cs_active_delay) {
            instr_scratch[offset++] = ADD_DELAY(NOP, (cs_active_delay - 1));
        }
    }
    instr_scratch[offset++] = MOV_PINDIRS_NOT_NULL;
    uint8_t check_cs_gone_inactive = offset;
    instr_scratch[offset++] = MOV_X_PINS;
    uint8_t sm0_wrap_top = offset;
    instr_scratch[offset++] = JMP_NOT_X(check_cs_gone_inactive);
    if (config->cs_inactive_delay) {
        instr_scratch[offset++] = ADD_DELAY(NOP, (config->cs_inactive_delay - 1));
        sm0_wrap_top++;
    }

    // Configure the CS handler SM
    sm_reg = PIO0_SM_REG(0);
    sm_reg->clkdiv = PIO_CLKDIV_INT(
        config->sm0_clkdiv_int,
        config->sm0_clkdiv_frac
    );
    sm_reg->execctrl =
        PIO_WRAP_BOTTOM(sm0_wrap_bottom) |
        PIO_WRAP_TOP(sm0_wrap_top);
    sm_reg->shiftctrl =
        PIO_IN_COUNT(num_cs_pins) | // Reading the CS pins
        PIO_IN_SHIFTDIR_L;          // Direction doesn't matter, as we're just
                                    // testing for zero
    sm_reg->pinctrl =
        PIO_OUT_COUNT(num_data_pins) |  // "Output" data pins (just direction
                                        // not value)
        PIO_OUT_BASE(data_base_pin) |   // Data pins
        PIO_IN_BASE(cs_base_pin);       // CS pins are input
    sm_reg->instr = JMP(sm0_start); // Jump to start of program

    //
    // SM1 - Address read
    //

    // Load the address read program
    uint8_t sm1_start = offset;
    uint8_t sm1_wrap_bottom = offset;
    // The ADDR_READ_DELAY gets added either to the IRQ (if it exists) or the
    // IN instruction (if no IRQ).  In the no IRQ case it is not important on
    // which instruction we add the delay, as it doesn't affect how "old" the
    // address will be went sent to the DMA, just how _frequently_ it is read.
    if (!addr_read_irq && addr_read_delay) {
        instr_scratch[offset++] = ADD_DELAY(IN_X(16), addr_read_delay);
    } else {
        instr_scratch[offset++] = IN_X(16);
    }
    if (addr_read_irq || no_dma) {
        if (!addr_read_delay) {
            instr_scratch[offset++] = WAIT_IRQ_HIGH(0);
        } else {
            instr_scratch[offset++] = ADD_DELAY(WAIT_IRQ_HIGH(0), addr_read_delay);
        }
    }
    uint8_t sm1_wrap_top = offset;
    instr_scratch[offset++] = IN_PINS(16);

    // Configure the address read SM
    sm_reg = PIO0_SM_REG(1);
    sm_reg->clkdiv = PIO_CLKDIV_INT(config->sm1_clkdiv_int, config->sm1_clkdiv_frac);
    sm_reg->execctrl = 
        PIO_WRAP_BOTTOM(sm1_wrap_bottom) |
        PIO_WRAP_TOP(sm1_wrap_top);
    sm_reg->shiftctrl =
        PIO_IN_COUNT(num_addr_pins) |   // Reading the address pins (unused as
                                        // this is for mov instructions)
        PIO_AUTOPUSH |          // Auto push when we hit threshold
        PIO_PUSH_THRESH(32) |   // Push when we have 32 bits (16 from X and 16
                                // from address pins)
        PIO_IN_SHIFTDIR_L |     // Shift left, so address lines are in low bits
        PIO_OUT_SHIFTDIR_L;     // Direction doesn't matter, as we push 32 bits
    sm_reg->pinctrl =
        PIO_IN_BASE(addr_base_pin); // Address pin base as start of input

    // Preload the ROM table address into the X register
    PIO0_SM_TXF(1) = (rom_table_addr >> 16) & 0xFFFF;   // Write high word to TX FIFO
    sm_reg->instr = PULL_BLOCK;     // Pull it into OSR
    sm_reg->instr = MOV_X_OSR;      // Store it in X

    // Jump to start of program
    sm_reg->instr = JMP(sm1_start); // Jump to start of program

    // 
    // SM2 - Data byte output

    // Load the data byte output program
    uint8_t sm2_start = offset;
    uint8_t sm2_wrap_bottom = offset;
    uint8_t sm2_wrap_top = offset;
    instr_scratch[offset++] = OUT_PINS(num_data_pins);

    // Configure the data byte SM
    sm_reg = PIO0_SM_REG(2);
    sm_reg->clkdiv = PIO_CLKDIV_INT(config->sm2_clkdiv_int, config->sm2_clkdiv_frac);
    sm_reg->execctrl = 
        PIO_WRAP_BOTTOM(sm2_wrap_bottom) |
        PIO_WRAP_TOP(sm2_wrap_top);
    sm_reg->shiftctrl = 
        PIO_OUT_SHIFTDIR_R |    // Writes LSB of OSR
        PIO_AUTOPULL |          // Auto pull when we hit threshold
        PIO_PULL_THRESH(num_data_pins);     // Pull when we have 8 bits
    sm_reg->pinctrl =
        PIO_OUT_BASE(data_base_pin) |       // Data pins
        PIO_OUT_COUNT(num_data_pins);       // Number of data pins
    sm_reg->instr = JMP(sm2_start); // Jump to start of program

    // Copy the constructed instructions into PIO instruction memory
    for (int ii = 0; ii < offset; ii++) {
        PIO0_INSTR_MEM(ii) = instr_scratch[ii];
    }

    // Log loaded program information
#if defined(DEBUG_LOGGING)
    DEBUG("PIO ROM serving programs:");
    piorom_log_pio_sm(
        "Chip Select Handler",
        0,
        config,
        instr_scratch,
        sm0_start,
        sm0_wrap_bottom,
        sm0_wrap_top
    );
    piorom_log_pio_sm(
        "Address Read",
        1,
        config,
        instr_scratch,
        sm1_start,
        sm1_wrap_bottom,
        sm1_wrap_top
    );
    piorom_log_pio_sm(
        "Data Byte Output",
        2,
        config,
        instr_scratch,
        sm2_start,
        sm2_wrap_bottom,
        sm2_wrap_top
    );
#endif // DEBUG_LOGGING
}

// Starts the PIO state machines for ROM serving.
static void piorom_start_pios() {
    PIO0_CTRL_SM_ENABLE(0x7); // Enable SM0, SM1 and SM2
}

// Set GPIOs to PIO function for ROM serving
static void piorom_set_gpio_func(piorom_config_t *config) {
    uint8_t num_cs_pins = config->num_cs_pins;
    uint8_t cs_base_pin = config->cs_base_pin;
    uint8_t *cs_pin_invert = config->invert_cs;
    uint8_t data_base_pin = config->data_base_pin;
    uint8_t addr_base_pin = config->addr_base_pin;

    // Data pins
    for (int ii = data_base_pin;
        ii < (data_base_pin + NUM_DATA_LINES);
        ii++) {
        GPIO_CTRL(ii) = GPIO_CTRL_FUNC_PIO0;
    }

    // Address pins
    for (int ii = addr_base_pin;
        ii < (addr_base_pin + NUM_ADDR_LINES);
        ii++) {
        GPIO_CTRL(ii) = GPIO_CTRL_FUNC_PIO0;
    }

    // CS pins
    //
    // We MUST set these after the address pins, as the CS pins may be part of
    // the address pin range (they are on a 24 pin ROM).
    for (int ii = 0; ii < num_cs_pins; ii++) {
        uint8_t pin = cs_base_pin + ii;
        uint8_t invert = cs_pin_invert[ii];
        // Set to PIO function - this clears everything else.
        GPIO_CTRL(pin) = GPIO_CTRL_FUNC_PIO0;
        if (!invert) {
            DEBUG("  CS pin %d active low CTRL=0x%08X", pin, GPIO_CTRL(pin));
        } else {
            // Turn CS line into active low by inverting the GPIO before the
            // PIO reads it
            GPIO_CTRL(pin) |= GPIO_CTRL_INOVER_INVERT;
            DEBUG("  CS pin %d active high CTRL=0x%08X", pin, GPIO_CTRL(pin));
        }
    }
}

// Setup the DMA channels for ROM serving
static void piorom_setup_dma(
    piorom_config_t *config,
    uint8_t pio_block,
    uint8_t sm_addr_read,
    uint8_t sm_data_byte
) {
    volatile dma_ch_reg_t *dma_reg;

    // DMA Channel 0 - Receives ROM table lookup address from PIO0 SM1 and
    // sends it onto DMA Channel 1.  Paced by PIO0 SM1 RX FIFO DREQ.
    dma_reg = DMA_CH_REG(0);
    dma_reg->read_addr = (uint32_t)&PIO0_SM_RXF(sm_addr_read);
    if (config->addr_read_irq) {
        // When address read is triggerd by IRQ, we only want a single
        // transfer per IRQ.  We need to trigger channel 1 manually.
        dma_reg->write_addr = (uint32_t)&DMA_CH_READ_ADDR_TRIG(1);
        dma_reg->transfer_count = 1;
    } else {
        // When address read is not triggered by IRQ, we want continuous
        // transfers to channel 1.  No triggering is necessary, as channel 1
        // will be paced by the PIO0 SM1 RX FIFO DREQ, like this channel.
        dma_reg->write_addr = (uint32_t)&DMA_CH_READ_ADDR(1);
        dma_reg->transfer_count = 0xffffffff;
    }
    dma_reg->ctrl_trig =
        DMA_CTRL_TRIG_TREQ_SEL(DREQ_PIO_X_SM_Y_RX(pio_block, sm_addr_read)) |
        DMA_CTRL_TRIG_EN |
        DMA_CTRL_TRIG_DATA_SIZE_32BIT;

    // DMA Channel 1 - Reads ROM data from memory and sends to PIO0 SM2.
    // Also paced by PIO0 SM1 RX FIF DREQ, so runs in lock-step with channel
    // 0.
    dma_reg = DMA_CH_REG(1);
    dma_reg->read_addr = 0; // To be set by DMA Channel 0
    dma_reg->write_addr = (uint32_t)&PIO0_SM_TXF(sm_data_byte);
    uint32_t ctrl_trig = 
        DMA_CTRL_TRIG_EN |
        DMA_CTRL_TRIG_DATA_SIZE_8BIT;
    if (config->addr_read_irq) {
        // When address read is triggerd by IRQ, we only want a single
        // transfer per IRQ.  We need to re-trigger channel 1 manually.
        dma_reg->transfer_count = 1;
        ctrl_trig |= DMA_CTRL_TRIG_TREQ_SEL(DMA_CTRL_TRIG_TREQ_PERM);
    } else {
        // When address read is not triggered by IRQ, we want continuous
        // transfers.
        dma_reg->transfer_count = 0xffffffff;
        ctrl_trig |= DMA_CTRL_TRIG_TREQ_SEL(DREQ_PIO_X_SM_Y_RX(pio_block, sm_addr_read));
    }
    dma_reg->ctrl_trig = ctrl_trig;

    // Set DMA Read as high priority on the AHB5 bus for both:
    // - Reads (from RAM and PIO RX FIFO)
    // - Writes (to PIO TX FIFO and DMA READ_ADDR)
    BUSCTRL_BUS_PRIORITY |=
        BUSCTRL_BUS_PRIORITY_DMA_R_BIT |
        BUSCTRL_BUS_PRIORITY_DMA_W_BIT;
}

// Get lowest data GPIO from the pin info
static uint8_t get_lowest_data_gpio(
    const sdrr_info_t *info
) {
    uint8_t lowest = MAX_USED_GPIOS;
    for (int ii = 0; ii < 8; ii++) {
        if (info->pins->data[ii] < lowest) {
            lowest = info->pins->data[ii];
        }
    }
    return lowest;
}

// Get lowest address GPIO from the pin info
static uint8_t get_lowest_addr_gpio(
    const sdrr_info_t *info
) {
    uint8_t lowest = MAX_USED_GPIOS;
    for (int ii = 0; ii < 16; ii++) {
        if (info->pins->addr[ii] < lowest) {
            lowest = info->pins->addr[ii];
        }
    }
    return lowest;
}

// Construct the PIO ROM serving configuration from the SDRR and ROM set info
static void piorom_finish_config(
    piorom_config_t *config,
    const sdrr_info_t *info,
    const sdrr_rom_set_t *set,
    uint32_t rom_table_addr
) {
    // Figure out number of CS pins from ROM type
    const sdrr_rom_info_t *rom = set->roms[0];
    switch (rom->rom_type) {
        case ROM_TYPE_2364:
            config->num_cs_pins = 1;
            break;

        case ROM_TYPE_2332:
            config->num_cs_pins = 2;
            break;

        default:
            LOG("!!! PIO ROM serving only supports 2364 and 2332 ROM types");
            limp_mode(LIMP_MODE_INVALID_CONFIG);
            config->num_cs_pins = 1;
            break;
    }

    // Figure out base CS pin from SDRR info
    if (config->num_cs_pins == 1) {
        config->cs_base_pin = info->pins->cs1;
    } else {
        if (info->pins->cs1 < info->pins->cs2) {
            if (info->pins->cs2 > (info->pins->cs1 + 1)) {
                LOG("!!! CS pins for 2332 ROM must be contiguous");
                limp_mode(LIMP_MODE_INVALID_CONFIG);
            }
            config->cs_base_pin = info->pins->cs1;
        } else {
            if (info->pins->cs1 > (info->pins->cs2 + 1)) {
                LOG("!!! CS pins for 2332 ROM must be contiguous");
                limp_mode(LIMP_MODE_INVALID_CONFIG);
            }
            config->cs_base_pin = info->pins->cs2;
        }
    }

    // Find any CS lines which need to be inverted.  Make sure to make CS
    // lines against the pin numbers - the lower pin number is first, whether
    // that is CS1 or CS2 (or CS3).
    for (int ii = 0; (ii < config->num_cs_pins) && (ii < 3); ii++) {
        if (info->pins->cs1 == (config->cs_base_pin + ii)) {
            if (rom->cs1_state == CS_ACTIVE_HIGH) {
                config->invert_cs[ii] = 1;
            } else {
                config->invert_cs[ii] = 0;
            }
        } else if (info->pins->cs2 == (config->cs_base_pin + ii)) {
            if (rom->cs2_state == CS_ACTIVE_HIGH) {
                config->invert_cs[ii] = 1;
            } else {
                config->invert_cs[ii] = 0;
            }
        }
    }

    // Figure out base address pin from SDRR info
    config->addr_base_pin = get_lowest_addr_gpio(info);

    // Figure out base data pin from SDRR info
    config->data_base_pin = get_lowest_data_gpio(info);

    // Set the ROM table address
    config->rom_table_addr = rom_table_addr;

    // Final checks
    if (config->rom_table_addr & 0xFFFF) {
        LOG("!!! PIO ROM serving requires ROM table address to be 64KB aligned");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }
    if ((config->rom_table_addr == 0) || (config->rom_table_addr == 0xFFFFFFFF)) {
        LOG("!!! PIO ROM serving requires valid ROM table address");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }
    if (config->cs_base_pin >= 26) {
        LOG("!!! PIO ROM serving requires CS pins to be GPIO 0-25");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }
    if (config->data_base_pin >= 26) {
        LOG("!!! PIO ROM serving requires Data pins to be GPIO 0-25");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }
    if (config->addr_base_pin >= 26) {
        LOG("!!! PIO ROM serving requires Address pins to be GPIO 0-25");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }
    if (config->addr_read_irq > 1) {
        LOG("!!! PIO ROM serving invalid addr_read_irq config");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }
    if (config->addr_read_delay > 32) {
        LOG("!!! PIO ROM serving invalid addr_read_delay config");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }
    if (config->cs_active_delay > 32) {
        LOG("!!! PIO ROM serving invalid cs_active_delay config");
        limp_mode(LIMP_MODE_INVALID_CONFIG);
    }

    // Log final configuration
    DEBUG("PIO ROM serving configuration:");
    DEBUG("  CS GPIOs: %d-%d", config->cs_base_pin, config->cs_base_pin + config->num_cs_pins - 1);
    for (int ii = 0; ii < config->num_cs_pins; ii++) {
        DEBUG("  - CS GPIO %d invert: %d", config->cs_base_pin + ii, config->invert_cs[ii]);
    }
    DEBUG("  Data GPIOs: %d-%d", config->data_base_pin, config->data_base_pin + config->num_data_pins - 1);
    DEBUG("  Address GPIOs: %d-%d", config->addr_base_pin, config->addr_base_pin + config->num_addr_pins - 1);
    DEBUG("  PIO algorithm options:");
    DEBUG("  - Address Read IRQ:   %d", config->addr_read_irq);
    DEBUG("  - Address Read Delay: %d", config->addr_read_delay);
    DEBUG("  - CS Active Delay:    %d", config->cs_active_delay);
    DEBUG("  ROM Table Address:  0x%08X", config->rom_table_addr);
}

// Default PIO ROM serving configuration
static piorom_config_t piorom_config = {
    .num_cs_pins = 0,
    .invert_cs = {0, 0, 0},
    .cs_base_pin = 255,
    .data_base_pin = 255,
    .num_data_pins = NUM_DATA_LINES,
    .addr_base_pin = 255,
    .num_addr_pins = NUM_ADDR_LINES,
    .addr_read_irq = PIO_CONFIG_ADDR_READ_IRQ,
    .addr_read_delay = PIO_CONFIG_ADDR_READ_DELAY,
    .cs_active_delay = PIO_CONFIG_CS_TO_DATA_OUTPUT_DELAY,
    .cs_inactive_delay = PIO_CONFIG_CS_INACTIVE_DATA_HOLD_DELAY,
#if defined(PIO_CONFIG_NO_DMA) && !PIO_CONFIG_NO_DMA
    .no_dma = 1,
#else // !PIO_CONFIG_NO_DMA
    .no_dma = 0,
#endif // PIO_CONFIG_NO_DMA
    .pad = {0, 0},
    .rom_table_addr = 0,
    .sm0_clkdiv_int = 1,
    .sm0_clkdiv_frac = 0,
    .pad0 = 0,
    .sm1_clkdiv_int = 1,
    .sm1_clkdiv_frac = 0,
    .pad1 = 0,
    .sm2_clkdiv_int = 1,
    .sm2_clkdiv_frac = 0,
    .pad2 = 0,
};

// Configure and start the Autonomous PIO/DMA ROM serving implementation.
void piorom(
    const sdrr_info_t *info,
    const sdrr_rom_set_t *set,
    uint32_t rom_table_addr
) {
    DEBUG("%s", log_divider);

    piorom_config_t *config = &piorom_config;

    piorom_finish_config(config, info, set, rom_table_addr);

    // Bring PIO0 and DMA out of reset
    RESET_RESET &= ~(RESET_PIO0 | RESET_DMA);
    while (!(RESET_DONE & (RESET_PIO0 | RESET_DMA)));

    // Setup the DMA channels:
    // - PIO block 0
    // - SM1 is the address read SM
    // - SM2 is the data byte output SM
    if (!config->no_dma) {
        piorom_setup_dma(config, 0, 1, 2);
    }

    // Configure GPIOs for PIO function
    // - 2 CS pins
    // - CS pins start at GPIO 10
    // - CS active high/low config
    // - Data pins start at GPIO 0
    // - Address pins start at GPIO 8
    piorom_set_gpio_func(config);

    // Load and configure the PIO programs
    // - 2 CS pins
    // - CS pins start at GPIO 10
    // - Data pins start at GPIO 0
    // - Address pins start at GPIO 8
    piorom_load_programs(config);

    if (!config->no_dma) {
        // Start the PIOs.  This kicks off the autonomous ROM serving.
        piorom_start_pios();

        while (1) {
            // Low power wait for (VBUS) interrupt.  Avoids any potential SRAM or
            // peripheral access that might introduce jitter on the PIO/DMA
            // serving.
            __asm volatile("wfi");
        }
    } else {
        register volatile uint32_t *ctrl asm("r0") = &PIO0_CTRL;
        register volatile uint32_t *rxf1 asm("r2") = &PIO0_SM_RXF(1);
        register volatile uint32_t *txf2 asm("r3") = &PIO0_SM_TXF(2);
        register volatile uint32_t *irq  asm("r4") = &PIO0_IRQ_FORCE;
        register uint32_t irq_set asm("r5") = 0x1;  // Set IRQ 0

        asm volatile (
            // Enable SM0/1/2
            "movs r1, #0x7\n"
            "str  r1, [r0]\n"

            // 6 cycle version with IRQ triggering SM1 to read address -
            // essentially pacing SM1, avoiding addr reads backing up
            "1:\n"
            "ldr  r0, [r2]\n"       // Read address from SM1 RX (1 cycle + 1 stall)
            "ldrb r1, [r0]\n"       // Read byte from that address (1 cycle)
            "str  r5, [r4]\n"       // Set IRQ triggering SM1 to re-read (1 cycle)
            "str  r1, [r3]\n"       // Write byte to SM2 TX (1 cycle)
            "b    1b\n"             // Loop (1 cycle)

            // Pathological 5 cycle version, requires no IRQ detection in SM1.
            // Shaves char ROM ser ing down to 50MHz.
            //"1:\n"
            //"str  r1, [r3]\n"       // Write byte to SM2 TX (1 cycle)
            //"ldr  r0, [r2]\n"       // Read address from SM1 RX (1 cycle + 1 stall)
            //"ldrb r1, [r0]\n"       // Read byte from that address (1 cycle)
            //"b    1b\n"             // Loop (1 cycle)

            :
            : "r"(ctrl), "r"(rxf1), "r"(txf2), "r"(irq), "r"(irq_set)
            : "r1", "memory"
        );
    }
}

#if defined(DEBUG_LOGGING)
static const char* piorom_get_jmp_condition(uint8_t cond) {
    switch (cond) {
        case 0b000: return "";
        case 0b001: return "!x";
        case 0b010: return "x--";
        case 0b011: return "!y";
        case 0b100: return "y--";
        case 0b101: return "x!=y";
        case 0b110: return "pin";
        case 0b111: return "!osre";
        default: return "???";
    }
}

static const char* piorom_get_wait_source(uint8_t src) {
    switch (src) {
        case 0b00: return "gpio";
        case 0b01: return "pin";
        case 0b10: return "irq";
        case 0b11: return "jmppin";
        default: return "???";
    }
}

static const char* piorom_get_in_source(uint8_t src) {
    switch (src) {
        case 0b000: return "pins";
        case 0b001: return "x";
        case 0b010: return "y";
        case 0b011: return "null";
        case 0b100: return "reserved";
        case 0b101: return "reserved";
        case 0b110: return "isr";
        case 0b111: return "osr";
        default: return "???";
    }
}

static const char* piorom_get_out_dest(uint8_t dest) {
    switch (dest) {
        case 0b000: return "pins";
        case 0b001: return "x";
        case 0b010: return "y";
        case 0b011: return "null";
        case 0b100: return "pindirs";
        case 0b101: return "pc";
        case 0b110: return "isr";
        case 0b111: return "exec";
        default: return "???";
    }
}

static const char* piorom_get_mov_dest(uint8_t dest) {
    switch (dest) {
        case 0b000: return "pins";
        case 0b001: return "x";
        case 0b010: return "y";
        case 0b011: return "pindirs";
        case 0b100: return "exec";
        case 0b101: return "pc";
        case 0b110: return "isr";
        case 0b111: return "osr";
        default: return "???";
    }
}

static const char* piorom_get_mov_op(uint8_t op) {
    switch (op) {
        case 0b00: return "";
        case 0b01: return "~";
        case 0b10: return "::";
        case 0b11: return "reserved";
        default: return "???";
    }
}

static const char* piorom_get_mov_source(uint8_t src) {
    switch (src) {
        case 0b000: return "pins";
        case 0b001: return "x";
        case 0b010: return "y";
        case 0b011: return "null";
        case 0b100: return "reserved";
        case 0b101: return "status";
        case 0b110: return "isr";
        case 0b111: return "osr";
        default: return "???";
    }
}

static const char* piorom_get_set_dest(uint8_t dest) {
    switch (dest) {
        case 0b000: return "pins";
        case 0b001: return "x";
        case 0b010: return "y";
        case 0b011: return "reserved";
        case 0b100: return "pindirs";
        case 0b101: return "reserved";
        case 0b110: return "reserved";
        case 0b111: return "reserved";
        default: return "???";
    }
}

static char* append_str(char* dest, const char* src) {
    while (*src) {
        *dest++ = *src++;
    }
    return dest;
}

static char* append_char(char* dest, char c) {
    *dest++ = c;
    return dest;
}

static char* append_uint(char* dest, uint32_t val) {
    if (val == 0) {
        *dest++ = '0';
        return dest;
    }
    
    char temp[11];
    int i = 0;
    while (val > 0) {
        temp[i++] = '0' + (val % 10);
        val /= 10;
    }
    
    while (i > 0) {
        *dest++ = temp[--i];
    }
    return dest;
}

static char* append_delay(char* dest, uint8_t delay) {
    if (delay > 0) {
        dest = append_str(dest, " [");
        dest = append_uint(dest, delay);
        dest = append_char(dest, ']');
    }
    return dest;
}

void piorom_instruction_decoder(uint32_t instr, char out_str[64]) {
    uint8_t opcode = (instr >> 13) & 0x7;
    uint8_t delay = (instr >> 8) & 0x1F;
    char* p;
    
    switch (opcode) {
        case 0b000: { // JMP
            uint8_t condition = (instr >> 5) & 0x7;
            uint8_t address = instr & 0x1F;
            p = out_str;
            p = append_str(p, "jmp ");
            p = append_str(p, piorom_get_jmp_condition(condition));
            p = append_str(p, ", ");
            p = append_uint(p, address);
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
        
        case 0b001: { // WAIT
            uint8_t pol = (instr >> 7) & 0x1;
            uint8_t source = (instr >> 5) & 0x3;
            uint8_t index = instr & 0x1F;
            p = out_str;
            p = append_str(p, "wait ");
            p = append_uint(p, pol);
            p = append_char(p, ' ');
            p = append_str(p, piorom_get_wait_source(source));
            p = append_str(p, ", ");
            p = append_uint(p, index);
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
        
        case 0b010: { // IN
            uint8_t source = (instr >> 5) & 0x7;
            uint8_t bitcount = instr & 0x1F;
            p = out_str;
            p = append_str(p, "in ");
            p = append_str(p, piorom_get_in_source(source));
            p = append_str(p, ", ");
            p = append_uint(p, bitcount);
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
        
        case 0b011: { // OUT
            uint8_t dest = (instr >> 5) & 0x7;
            uint8_t bitcount = instr & 0x1F;
            p = out_str;
            p = append_str(p, "out ");
            p = append_str(p, piorom_get_out_dest(dest));
            p = append_str(p, ", ");
            p = append_uint(p, bitcount);
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
        
        case 0b100: { // PUSH/PULL/MOV indexed
            uint8_t bit7 = (instr >> 7) & 0x1;
            uint8_t bit4 = (instr >> 4) & 0x1;
            p = out_str;
            
            if (bit4 == 0) {
                // PUSH or PULL
                uint8_t if_flag = (instr >> 6) & 0x1;
                uint8_t block = (instr >> 5) & 0x1;
                
                if (bit7 == 0) {
                    // PUSH
                    p = append_str(p, "push");
                    if (if_flag) {
                        p = append_str(p, " iffull ");
                    } else {
                        p = append_char(p, ' ');
                    }
                    p = append_str(p, block ? "block" : "noblock");
                } else {
                    // PULL
                    p = append_str(p, "pull");
                    if (if_flag) {
                        p = append_str(p, " ifempty ");
                    } else {
                        p = append_char(p, ' ');
                    }
                    p = append_str(p, block ? "block" : "noblock");
                }
            } else {
                // MOV indexed
                uint8_t idx_i = (instr >> 3) & 0x1;
                uint8_t index = instr & 0x3;
                
                if (bit7 == 0) {
                    // MOV RX
                    p = append_str(p, "mov rxfifo[");
                    if (idx_i) {
                        p = append_uint(p, index);
                    } else {
                        p = append_char(p, 'y');
                    }
                    p = append_str(p, "], isr");
                } else {
                    // MOV TX
                    p = append_str(p, "mov txfifo[");
                    if (idx_i) {
                        p = append_uint(p, index);
                    } else {
                        p = append_char(p, 'y');
                    }
                    p = append_str(p, "], osr");
                }
            }
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
        
        case 0b101: { // MOV
            uint8_t dest = (instr >> 5) & 0x7;
            uint8_t op = (instr >> 3) & 0x3;
            uint8_t source = instr & 0x7;
            p = out_str;
            
            // Check for nop (mov y, y)
            if (dest == 0b010 && op == 0b00 && source == 0b010) {
                p = append_str(p, "nop");
            } else {
                p = append_str(p, "mov ");
                p = append_str(p, piorom_get_mov_dest(dest));
                p = append_str(p, ", ");
                p = append_str(p, piorom_get_mov_op(op));
                p = append_str(p, piorom_get_mov_source(source));
            }
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
        
        case 0b110: { // IRQ
            uint8_t clr = (instr >> 6) & 0x1;
            uint8_t wait = (instr >> 5) & 0x1;
            uint8_t idx_mode = (instr >> 3) & 0x3;
            uint8_t index = instr & 0x7;
            p = out_str;
            p = append_str(p, "irq ");
            
            // prev/next
            if (idx_mode == 0b01) {
                p = append_str(p, "prev ");
            } else if (idx_mode == 0b11) {
                p = append_str(p, "next ");
            }
            
            // set/wait/clear
            if (clr) {
                p = append_str(p, "clear ");
            } else if (wait) {
                p = append_str(p, "wait ");
            }
            
            p = append_uint(p, index);
            
            // rel
            if (idx_mode == 0b10) {
                p = append_str(p, " rel");
            }
            
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
        
        case 0b111: { // SET
            uint8_t dest = (instr >> 5) & 0x7;
            uint8_t data = instr & 0x1F;
            p = out_str;
            p = append_str(p, "set ");
            p = append_str(p, piorom_get_set_dest(dest));
            p = append_str(p, ", ");
            p = append_uint(p, data);
            p = append_delay(p, delay);
            *p = '\0';
            break;
        }
    }
}

void piorom_log_pio_sm(
    const char *sm_name,
    uint8_t pio_sm,
    piorom_config_t *config,
    uint32_t *instr_scratch,
    uint8_t start,
    uint8_t wrap_bottom,
    uint8_t wrap_top
) {
    // Scratch for instruction decoding
    char instr[64];

    // Get clock divider for this SM
    uint16_t clkdiv_int;
    uint8_t clkdiv_frac;
    if (pio_sm == 0) {
        clkdiv_int = config->sm0_clkdiv_int;
        clkdiv_frac = config->sm0_clkdiv_frac;
    } else if (pio_sm == 1) {
        clkdiv_int = config->sm1_clkdiv_int;
        clkdiv_frac = config->sm1_clkdiv_frac;
    } else {
        clkdiv_int = config->sm2_clkdiv_int;
        clkdiv_frac = config->sm2_clkdiv_frac;
    }

    // Log
    DEBUG("  SM%d - %s:", pio_sm, sm_name);
    DEBUG(
        "    CLKDIV: %d.%02d EXECCTRL: 0x%08X SHIFTCTRL: 0x%08X PINCTRL: 0x%08X",
        clkdiv_int,
        clkdiv_frac,
        PIO0_SM_REG(pio_sm)->execctrl,
        PIO0_SM_REG(pio_sm)->shiftctrl,
        PIO0_SM_REG(pio_sm)->pinctrl
    );
    DEBUG("      .program sm%d", pio_sm);
    for (int ii = start; ii <= wrap_top; ii++) {
        if (ii == wrap_bottom) {
            DEBUG("      .wrap_target");
        }
        piorom_instruction_decoder(instr_scratch[ii], instr);
        DEBUG("        0x%02X: 0x%04X ; %s", ii - start, instr_scratch[ii], instr);
        if (ii == wrap_top) {
            DEBUG("      .wrap");
        }
    }
}
#endif // DEBUG_LOGGING

#endif // RP_PIO