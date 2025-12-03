# RP2350 CPU-less Serving Approach

Working document.

## Overview
Autonomous ROM emulation with zero CPU involvement after initialization. Estimated total latency: ~10 cycles @ 150MHz = ~67ns.

## PIO_CS (Chip Select Monitor)

Notes:
- This PIO runs completely independently of the data path PIO and DMAs.
- This only works for a 2364 with active low CS line.  However, adapting to other high CS and/or multiple CS lines is likely straightforward - by inverting the INOVER flag - and configuring the PIO for the set of CS lines.  However, this will require CS lines to always be contiguous, probably meaning swapping A10 and A11 around with respect to hardware rev B.

**Purpose:** Monitor CS lines and control data pin direction

**Algorithm:**
```
; Any active high CS lines are inverted via INOVER, so active = 0
; - set_count = 8 for data pins
; - set_base = data pins GPIO base
; - in_base = lowest CS GPIO
; - n needs to be number of CS lines (and they must be contiguous GPIOs)
; in_base and n need to be configured at runtime

loop:
    in pins, n            ; Read n CS pins into ISR
    mov x, isr            ; Copy ISR to X scratch register
    jmp !x, cs_active     ; If X == 0 (all CS active), jump
    jmp loop              ; Otherwise keep checking

cs_active:
    mov pindirs, ~null     ; Set data pins to output
    
wait_inactive:
    in pins, n            ; Read CS pins again
    mov x, isr            
    jmp !x, wait_inactive ; If still all zero, keep waiting
    
    ; At least one CS is now inactive (X != 0)
    mov pindirs, null     ; Set data pins to input
    jmp loop
```

**Constraints:**
- All CS lines must be on consecutive GPIOs
- Active-high CS lines must use INOVER to invert, making "active" = bit 0 for all lines

**Timing:** 
- Loop checking: 3 cycles when CS inactive
- CS active detection: 1 cycle
- CS inactive detection: 3 cycles per check

**Timing:** Responds within 7 cycles of CS edge, <50ns @ 150MHz

---

## PIO_ADDR (Address Reader)

**Purpose:** Read address from GPIOs and construct full RAM address

**Algorithm:**
```
; auto push mode with 32-bit threshold
; preload Y with upper 16 bits of base address (0x2000)
; - in_base = address GPIO base
; - autopush enabled at 32-bit threshold 
; tx fifo -> triggers DMA_1 via DREQ

loop:
    in y, 16              ; Shift upper address bits into ISR (0x2000)
    in pins, 16           ; Shift GPIO address bits into ISR (autopush)
    wait 1                ; Wait 1 cycle to allow DMAs to keep up
    jmp loop
```

**Timing:** 4 cycles per address, < 30ns @ 150MHz

**Output:** Complete 32-bit address (e.g., 0x20001234) pushed to FIFO

---

## DMA_1 (Address Forwarder)

**Purpose:** Forward addresses from PIO to DMA_2's READ_ADDR register

**Configuration:**
- **Trigger:** PIO_ADDR TX FIFO DREQ
- **Read from:** PIO_ADDR RX FIFO (alias for TX)
- **Write to:** DMA_2's `READ_ADDR` register (CHx_READ_ADDR)
- **Transfer size:** 32-bit word
- **Transfer count:** 1 (single transfer per trigger)
- **Chain to:** DMA_2

**Operation:**
1. DREQ fires when PIO_ADDR autopushes
2. Read 32-bit address from PIO FIFO
3. Write to DMA_2's READ_ADDR register
4. Trigger DMA_2 via chain
5. Idle until next DREQ

**Timing:** ~2-3 cycles, < 25ns @ 150MHz

---

## DMA_2 (ROM Data Fetcher)

**Purpose:** Read byte from ROM table and write to GPIO

**Configuration:**
- **Trigger:** Chained from DMA_1
- **Read from:** Address set dynamically by DMA_1
- **Write to:** `GPIO_OUT` register
- **Transfer size:** 8-bit byte
- **Transfer count:** 1 (single transfer per trigger)

**Operation:**
1. Triggered by DMA_1 chain
2. Read byte from ROM table at address in READ_ADDR
3. Write byte to GPIO_OUT (auto-replicated to data pins)
4. Idle until next chain trigger

**Timing:** ~2-3 cycles, < 25ns @ 150MHz

**Note:** Byte write to GPIO_OUT is automatically replicated across the 32-bit bus, setting all byte lanes to the same value. Data pins see the correct byte regardless of which GPIO positions they occupy.

---

## Data Flow Diagram

```
Address GPIOs → PIO_ADDR (3 cycles)
                    ↓ (autopush + DREQ)
                DMA_1 (2-3 cycles)
                    ↓ (writes to DMA_2 READ_ADDR + chain)
                DMA_2 (2-3 cycles)
                    ↓ (reads ROM[addr], writes to GPIO)
                Data GPIOs

CS GPIO → PIO_CS → Data Pin Direction (independent, parallel)
```

---

## Initialization Requirements

**ROM Table:**
- Must be aligned to 64KB boundary
- Located at 0x20000000 (start of RAM)
- Size: 64KB (0x10000 bytes)
- Allocation and alignment handled by linker.

**GPIOs:**
- Address pins: Must be consecutive, mappable to PIO IN PINS (bits 0-15)
- Data pins: 8 pins, at 8 bit offset, contiguous, any position (byte replication handles alignment)
- CS pin: Single GPIO

**DMA_1 Initialization:**
- Set READ_ADDR to PIO_ADDR FIFO
- Set WRITE_ADDR to DMA_2's READ_ADDR register
- Set DREQ to PIO_ADDR TX
- Set CHAIN_TO to DMA_2 channel number
- Enable channel

**DMA_2 Initialization:**
- Set READ_ADDR to 0x00000000 (will be overwritten immediately)
- Set WRITE_ADDR to GPIO_OUT register
- Set transfer size to 8-bit
- Enable channel (triggered only by chain)

---

## Key Enabling Techniques

1. **64KB Alignment Trick:** By aligning ROM table to 64KB boundary, lower 16 bits of base address are 0x0000, allowing PIO to "add" offset via bit concatenation instead of arithmetic.

2. **Byte Replication:** RP2350's automatic byte replication on narrow writes to 32-bit registers eliminates need for masking or additional PIO stage.

3. **Dynamic DMA Addressing:** DMA_1 writing to DMA_2's READ_ADDR register enables indirect memory access without CPU involvement.

4. **Parallel CS Control:** CS monitoring runs completely independently, no synchronization required with data path.
