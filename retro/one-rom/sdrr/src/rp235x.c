// One ROM RP235X Specific Routines

// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

#include "include.h"
#include "roms.h"

// Internal function prototypes
static void setup_xosc(void);
static void setup_pll(void);
static void setup_usb_pll(void);
static void setup_qmi(void);
static void setup_vreg(void);
static void setup_adc(void);
static void setup_cp(void);
static void final_checks(void);
uint16_t get_temp(void);

// RP2350 firmware needs a special boot block so the bootloader will load it.
// See datasheet S5.9.5 and ../include/reg-rp235x.h.
// It must be in the first 4KB of the flash firmware image.  This follows our
// reset vectors, which is fine.  Given we do not include a VECTOR_TABLE
// block, the bootloader assumes it is present at the start of flash - which it
// is.
__attribute__((section(".rp2350_block"))) const rp2350_boot_block_t rp2350_arm_boot_block = {
    .start_marker    = 0xffffded3,
    .image_type_tag  = 0x42,
    .image_type_len  = 0x1,
    .image_type_data = 0b0001000000100001,
    .type            = 0xff,
    .size            = 0x0001,
    .pad             = 0,
    .next_block      = 0,
    .end_marker      = 0xab123579
};

void platform_specific_init(void) {
    // RP235X needs to reset the JTAG interface to enable SWD (for example for
    // RTT logging)
    RESET_RESET |= RESET_JTAG;
    RESET_RESET &= ~RESET_JTAG;
    while (!(RESET_DONE & RESET_JTAG));
    DEBUG("JTAG reset complete");
}

// Set up interrupt to fire when VBUS sensed on PA9
void setup_vbus_interrupt(void) {
    // Check we have the information required to enable DFU
    if ((sdrr_info.extra->usb_port != PORT_0) ||
        (sdrr_info.extra->vbus_pin >= MAX_USED_GPIOS)) {
        LOG("!!! Invalid USB port or pin for VBUS detect - not enabling USB DFU");
        return;
    }
    uint8_t vbus_pin = sdrr_info.extra->vbus_pin;

    // Enable VBUS detect interrupt
    GPIO_CTRL(vbus_pin) = GPIO_CTRL_RESET;      // Enable SIO
    uint32_t reg_offset = vbus_pin / 8;         // Which INTEx register (0-3)
    uint32_t bit = ((vbus_pin % 8) * 4) + 3;    // Bit within that register
    volatile uint32_t *inte = &IO_BANK0_PROC0_INTE0 + reg_offset;
    volatile uint32_t *intr = &IO_BANK0_INTR0 + reg_offset;
    *inte |= (1 << bit);                        // Enable rising edge interrupt
    *intr = (1 << bit);                         // Clear any pending
    NVIC_ISER0 |= (1 << IO_IRQ_BANK0);          // Enable IO_BANK0 interrupt in NVIC

    // Set as input, pull-down, output disable
    GPIO_PAD(vbus_pin) |= (PAD_PD | PAD_OUTPUT_DISABLE | PAD_INPUT);

    // Wait for pull-down to settle.  Using same delay as STM32 implementation.
    for (volatile int ii = 0; ii < 1000; ii++);

    // Check if VBUS already present
    if (GPIO_READ(vbus_pin)) {
        LOG("VBUS already present - entering bootloader");
        for (volatile int ii = 0; ii < 1000000; ii++);
        enter_bootloader();
    }
}

// VBUS interrupt Handler
void vbus_connect_handler(void) {
    // Clear the interrupt
    uint8_t vbus_pin = sdrr_info.extra->vbus_pin;
    uint32_t reg_offset = vbus_pin / 8;
    uint32_t bit = ((vbus_pin % 8) * 4) + 3;
    volatile uint32_t *intr = &IO_BANK0_INTR0 + reg_offset;
    *intr = (1 << bit);

    // Disable interrupts before logging
    __asm volatile("cpsid i");

        // Log and pause for log to complete
    LOG("VBUS detected - entering bootloader");
    for (volatile int ii = 0; ii < 1000000; ii++);

    enter_bootloader();
}

void setup_clock(void) {
    LOG("Setting up clock");

    setup_xosc();
    setup_qmi();
    setup_vreg();
    setup_pll();
    setup_cp();
    final_checks();
}

void setup_gpio(void) {
    // Take IO bank and pads bank out of reset
    RESET_RESET &= ~(RESET_IOBANK0 | RESET_PADS_BANK0);
    while (!(RESET_DONE & (RESET_IOBANK0 | RESET_PADS_BANK0)));

    // Set all GPIO pins to SIOs, inputs, output disable, no pulls
    for (int ii = 0; ii < MAX_USED_GPIOS; ii++) {
        GPIO_CTRL(ii) = GPIO_CTRL_RESET;
        GPIO_PAD(ii) = PAD_INPUT | PAD_OUTPUT_DISABLE;
    }

    // Go through the data pins, disabling the output disable and setting the
    // drive strength.  We don't actually set as an output here.
    // Set the drive strength to 8mA and slew rate to fast.
    for (int ii = 0; ii < 8; ii++) {
        uint8_t pin = sdrr_info.pins->data[ii];
        if (pin < MAX_USED_GPIOS) {
            GPIO_PAD(sdrr_info.pins->data[ii]) &= ~PAD_OUTPUT_DISABLE;
            GPIO_PAD(sdrr_info.pins->data[ii]) |= PAD_DRIVE(PAD_DRIVE_8MA) | PAD_SLEW_FAST;
            GPIO_CTRL(pin) = GPIO_CTRL_FUNC_SIO;
        } else {
            LOG("!!! Data pin %d out of range", pin);
        }
    }

    // If there's a status LED, set it up as an output pin, high (LED off).
    if (sdrr_info.pins->status != INVALID_PIN) {
        uint8_t pin = sdrr_info.pins->status;
        if (pin < MAX_USED_GPIOS) {
            GPIO_PAD(pin) &= ~(PAD_OUTPUT_DISABLE | PAD_INPUT);
            GPIO_PAD(pin) |= PAD_DRIVE(PAD_DRIVE_4MA);
            SIO_GPIO_OE_SET = (1 << pin);
            SIO_GPIO_OUT_SET = (1 << pin);
        } else {
            LOG("!!! Status LED pin %d out of range", pin);
        }
    } else {
        DEBUG("No status LED pin defined");
    }
}

// Reconfigure flash (QMI) speed if required
void setup_qmi(void) {
#if TARGET_FREQ_MHZ > (MAX_FLASH_CLOCK_FREQ_MHZ * 256)
#error "Flash divider > 256 not supported by the hardware"
#endif
    if (TARGET_FREQ_MHZ > MAX_FLASH_CLOCK_FREQ_MHZ) {
        DEBUG("Target clock speed exceeds max flash speed %dMHz vs %dHz", TARGET_FREQ_MHZ, MAX_FLASH_CLOCK_FREQ_MHZ);

        // Calculate the divider
        uint8_t divider = TARGET_FREQ_MHZ / MAX_FLASH_CLOCK_FREQ_MHZ;
        if (TARGET_FREQ_MHZ % MAX_FLASH_CLOCK_FREQ_MHZ) {
            divider += 1;
        }

        uint32_t m0 = XIP_QMI_M0_TIMING;
        DEBUG("Current QMI M0 TIMING: 0x%08X", m0);

        m0 &= ~XIP_QMI_M0_CLKDIV_MASK;
        m0 |= (divider & XIP_QMI_M0_CLKDIV_MASK) << XIP_QMI_M0_CLKDIV_SHIFT;

        LOG("Updating M0 clock divider to %d", divider);

        DEBUG("Updating QMI M0 TIMING: 0x%08X", m0);

        XIP_QMI_M0_TIMING = m0;
    }
}

void setup_vreg(void) {
    uint32_t vreg_ctrl = POWMAN_VREG_CTRL;
    uint32_t vreg = POWMAN_VREG;
    DEBUG("Current VREG_CTRL: 0x%08X", vreg_ctrl);
    DEBUG("Current VREG_STATUS: 0x%08X", POWMAN_VREG_STATUS);
    DEBUG("Current VREG: 0x%08X", vreg);

    if (TARGET_FREQ_MHZ > 300) {
        uint8_t voltage;
        uint8_t high_temp = HT_TH_100;
        uint8_t unlimited_voltage = 0;
        if (TARGET_FREQ_MHZ <= 330) {
            voltage = VREG_1_15V;
        } else if (TARGET_FREQ_MHZ <= 360) {
            voltage = VREG_1_20V;
        } else if (TARGET_FREQ_MHZ <= 390) {
            voltage = VREG_1_25V;
        } else if (TARGET_FREQ_MHZ <= 420) {
            voltage = VREG_1_30V;
        } else {
            unlimited_voltage = 1;
            if (TARGET_FREQ_MHZ <= 450) {
                LOG("!!! Setting voltage to 1.40V !!!");
                voltage = VREG_1_40V;
            } else if (TARGET_FREQ_MHZ <= 480) {
                LOG("!!! Setting voltage to 1.50V !!!");
                voltage = VREG_1_50V;
            } else {
                // Seems good to around 540
#if TARGET_FREQ_MHZ > 540
#error "Current max is 540MHz with 1.6V"
#endif
                LOG("!!! Setting voltage to 1.60V !!!");
                voltage = VREG_1_60V;
            }
        }

        DEBUG("Unlocking VREG");
        vreg_ctrl |= POWMAN_PASSWORD |
                POWMAN_VREG_CTRL_UNLOCK;
        POWMAN_VREG_CTRL = vreg_ctrl;
        while (!(POWMAN_VREG_CTRL & POWMAN_VREG_CTRL_UNLOCK));

        if (unlimited_voltage) {
            LOG("!!! Disabling voltage limit for >420MHz operation !!!");
            vreg_ctrl |= POWMAN_VREG_CTRL_DISABLE_VOLTAGE_LIMIT;
            POWMAN_VREG_CTRL = vreg_ctrl;
            while (!(POWMAN_VREG_CTRL & POWMAN_VREG_CTRL_DISABLE_VOLTAGE_LIMIT));
        }

        DEBUG("Setting VREG high temp to %d", high_temp);
        vreg_ctrl &= ~(HT_TH_MASK << HT_TH_SHIFT);
        vreg_ctrl |= POWMAN_PASSWORD |
                        POWMAN_VREG_CTRL_HT_TH(high_temp);
        POWMAN_VREG_CTRL = vreg_ctrl;
        DEBUG("Current VREG_CTRL: 0x%08X", POWMAN_VREG_CTRL);

        DEBUG("Setting VREG voltage to %d", voltage);
        while (POWMAN_VREG & POWMAN_VREG_UPDATE);
        vreg &= ~(VREG_MASK << VREG_SHIFT);
        vreg |= POWMAN_VREG_VOLTAGE(voltage) | POWMAN_PASSWORD;
        POWMAN_VREG = vreg;
        while (POWMAN_VREG & POWMAN_VREG_UPDATE);

        LOG("Set voltage regulator - POWMAN_VREG: 0x%08X", POWMAN_VREG);

        for (volatile int ii = 0; ii < 5000; ii++) {
            // Wait a bit for the voltage to stabilise
            // 2,000 loops is too few at 540MHz, 5,000 seems like enough
            // Not required if DEBUG logging is on
        }
    } 
}

// Set up the PLL with the generated values
void setup_pll(void) {
    // Release PLL_SYS from reset
    RESET_RESET &= ~RESET_PLL_SYS;
    while (!(RESET_DONE & RESET_PLL_SYS));

    // Power down the PLL, set the feedback divider
    PLL_SYS_PWR = PLL_PWR_PD | PLL_PWR_VCOPD;

    // Set feedback divider and reference divider
    PLL_SYS_FBDIV_INT = PLL_SYS_FBDIV;
    PLL_SYS_CS = PLL_CS_REFDIV(PLL_SYS_REFDIV);

    // Power up VCO (keep post-dividers powered down)
    PLL_SYS_PWR = PLL_PWR_POSTDIVPD;

    // Wait for PLL to lock
    while (!(PLL_SYS_CS & PLL_CS_LOCK));

    // Set post dividers and power up everything
    PLL_SYS_PRIM = PLL_PRIM_POSTDIV1(PLL_SYS_POSTDIV1) |
                     PLL_PRIM_POSTDIV2(PLL_SYS_POSTDIV2);

    // Power up post dividers
    PLL_SYS_PWR = 0;

    // Switch to the PLL
    CLOCK_SYS_CTRL = CLOCK_SYS_SRC_AUX | CLOCK_SYS_AUXSRC_PLL_SYS;
    while ((CLOCK_SYS_SELECTED & (1 << 1)) == 0);
}

void setup_usb_pll(void) {
    DEBUG("Setting up USB PLL");

    // Release PLL_USB from reset
    RESET_RESET &= ~RESET_PLL_USB;
    while (!(RESET_DONE & RESET_PLL_USB));

    // Power down the PLL, set the feedback divider
    PLL_USB_PWR = PLL_PWR_PD | PLL_PWR_VCOPD;

    // For 48MHz: 12MHz × 40 ÷ 10 ÷ 1 = 48MHz
    PLL_USB_FBDIV_INT = 40;
    PLL_USB_CS = PLL_CS_REFDIV(1);

    // Power up VCO (keep post-dividers powered down)
    PLL_USB_PWR = PLL_PWR_POSTDIVPD;

    // Wait for lock
    while (!(PLL_USB_CS & PLL_CS_LOCK));

    // Set post dividers: 40 × 12MHz = 480MHz → ÷10 ÷1 = 48MHz
    PLL_USB_PRIM = PLL_PRIM_POSTDIV1(10) | PLL_PRIM_POSTDIV2(1);

    // Power up
    PLL_USB_PWR = 0;
}

void setup_adc(void) {
        DEBUG("Setting up ADC");

        // Route USB PLL to ADC (USB is the default source so no need to set)
        CLOCK_ADC_CTRL |= CLOCK_ADC_ENABLE;
        while (!(CLOCK_ADC_CTRL & CLOCK_ADC_ENABLED));
        DEBUG("ADC clock enabled");

        // Take ADC out of reset
        RESET_RESET &= ~(RESET_ADC);
        while (!(RESET_DONE & RESET_ADC));

        // Enable ADC and temperature sensor
        DEBUG("ADC out of reset");
        ADC_CS |= ADC_CS_TS_EN | ADC_CS_EN;
        while (!(ADC_CS & ADC_CS_READY));          

        DEBUG("ADC ready");
}

uint16_t get_temp(void) {
    // Start a conversion
    ADC_CS |= ADC_CS_AINSEL(ADC_CS_TS);
    ADC_CS |= ADC_CS_START_ONCE;

    // Wait for it to complete
    while (!(ADC_CS & ADC_CS_READY));

    // Return the result
    return (uint16_t)(ADC_RESULT & ADC_RESULT_MASK);
}

void final_checks(void) {
    if (TARGET_FREQ_MHZ > 300) {
        DEBUG("!!!Extreme overlocking - enabling and reading temp sensor");

        // USB clock required for ADC
        setup_usb_pll();

        // Set up ADC
        setup_adc();

        // Take a reading
        uint16_t temp = get_temp();
        (void)temp;  // In case not logged

        LOG("!!! Temperature sensor reading: 0x%03X", temp);
    }
}

void setup_cp(void) {
#if defined(RP_USE_CP)
    // Enable Coprocessor 0 to enable MCR instructions
    SCB_CPACR &= ~(0b11 << 0);
    SCB_CPACR |= SCB_CPACR_CP0_FULL;
    __asm volatile ("dsb");
    __asm volatile ("isb");
    DEBUG("CP0 enabled");
#endif // RP_USE_CP
}

void setup_mco(void) {
    LOG("!!! MCO not supported on RP235X");
}

// Set up the image select pins to be inputs with the appropriate pulls.
uint32_t setup_sel_pins(uint32_t *sel_mask) {
    uint32_t num;
    uint32_t pad;

    if (sdrr_info.pins->sel_jumper_pull == 0) {
        // Jumper will pull down, so we pull up
        pad = PAD_INPUT_PU;
    } else if (sdrr_info.pins->sel_jumper_pull == 1) {
        // Jumper will pull up, so we pull down
        pad = PAD_INPUT_PD;
    } else {
        LOG("!!! Invalid sel pull %d", sdrr_info.pins->sel_jumper_pull);
        return 0;
    }

    *sel_mask = 0;
    num = 0;
    for (int ii = 0; (ii < MAX_IMG_SEL_PINS); ii++) {
        uint8_t pin = sdrr_info.pins->sel[ii];
        if (pin < MAX_USED_GPIOS) {
            // Enable pull-up
            GPIO_PAD(pin) = pad;

            // Set the pin in our bit mask
            *sel_mask |= (1 << pin);

            num += 1;
        } else if (pin != INVALID_PIN) {
            LOG("!!! Sel pin %d >= %d - not using", pin, MAX_USED_GPIOS);
        }
    }

    // Short delay to allow the pulls to settle.
    for(volatile int ii = 0; ii < 10; ii++);

    return num;
}

// Get the value of the sel pins.  If, on this board, the MCU pulls are low
// (i.e. closing the jumpers pulls them up) we return the value as is, as
// closed should indicate 1.  In the other case, where MCU pulls are high
// (closing jumpers) pulls the pins low, we invert - so closed still indicates
// 1.
//
// We will probably make this behaviour configurable soon.
//
// On all RP2350 boards, the SEL pins are pulled low by jumpers to indicate
// a 1, so reverse to the default STM32F4 behavior.
uint32_t get_sel_value(uint32_t sel_mask) {
    uint8_t invert;
    uint32_t gpio_value;

    if (sdrr_info.pins->sel_jumper_pull == 0) {
        // Closing the jumper produces a 0, so invert
        invert = 1;
    } else {
        // Closing the jumper produces a 1, so don't invert
        invert = 0;
    }

    gpio_value = SIO_GPIO_IN & sel_mask;
    if (invert) {
        // If we are inverting, we need to flip the bits
        gpio_value = ~gpio_value;
    }

    return gpio_value;
}

void disable_sel_pins(void) {
    for (int ii = 0; (ii < MAX_IMG_SEL_PINS); ii++) {
        uint8_t pin = sdrr_info.pins->sel[ii];
        if (pin < MAX_USED_GPIOS) {
            // Disable pulls
            GPIO_PAD(pin) = ~(PAD_PU | PAD_PD);

        }
    }
}

void setup_status_led(void) {
    // No-op - done in setup_gpio()
}

void blink_pattern(uint32_t on_time, uint32_t off_time, uint8_t repeats) {
    if (sdrr_info.status_led_enabled && sdrr_info.pins->status_port == PORT_0 && sdrr_info.pins->status <= 29) {
        uint8_t pin = sdrr_info.pins->status;
        for(uint8_t i = 0; i < repeats; i++) {
            status_led_on(pin);
            delay(on_time);
            status_led_off(pin);
            delay(off_time);
        }   
    }
}

// Enters bootloader mode.
void enter_bootloader(void) {
    // Look up the reboot function from ROM
    typedef int (*reboot_fn_t)(uint32_t flags, uint32_t delay_ms, uint32_t p0, uint32_t p1);
    typedef void *(*rom_table_lookup_fn)(uint32_t code, uint32_t mask);
    
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Warray-bounds"
    rom_table_lookup_fn rom_table_lookup = 
        (rom_table_lookup_fn)(uintptr_t)*(uint16_t*)(0x00000016);
#pragma GCC diagnostic pop
    
    // 0x0004 is ARM secure mode
    uint32_t reboot_code = ('B' << 8) | 'R';
    reboot_fn_t reboot = (reboot_fn_t)rom_table_lookup(reboot_code, 0x0004);

    if (reboot == NULL) {
        LOG("!!! Unable to find reboot function in ROM - cannot enter bootloader");
        return;
    }

    // Reboot into BOOTSEL mode with status LED as activity indicator (active low)
    uint32_t flags = 0x0100 | 0x0002;   // No return on success | BOOTSEL mode
    uint32_t ms_delay = 10; // 10ms delay before reboot, needs to be non-zero
    uint32_t p0 = 0;
    uint32_t p1 = 0;

    // There is a bug in the Pico SDK and RP2350 datasheet defining p0 and p1
    // for reboot() when using REBOOT_TYPE_BOOTSEL (0x0002).  p0 and p1 have
    // been transposed.  p1 is the status LED pin, p0 the flags.  We don't want
    // to enable the status LED, because it looks too much like One ROM is
    // ready to serve bytes.  Hence we leave it disabled.  This makes it light
    // up dimly, just like during initial power-on.
    // 
    // However, we do want to explicitly disable mass storage mode, so we set
    // bit 0 of p0 (not p1!).  If you want mass storage mode, jump BOOTSEL to
    // GND when plugging in.
    p0 |= 0x01;     // Disable mass storage mode
    reboot(flags, ms_delay, p0, p1);
}

void check_config(
    const sdrr_info_t *info,
    const sdrr_rom_set_t *set
) {
    // Currently only support emulating a 24 pin ROM
    if (info->pins->rom_pins != 24) {
        LOG("!!! Have been told to emulate unsupported %d pin ROM", info->pins->rom_pins);
    }

    // Check ports (banks on RP235X) are as expected
    if (info->pins->data_port != PORT_0) {
        LOG("!!! Data pins should be using bank 0");
    }
    if (info->pins->addr_port != PORT_0) {
        LOG("!!! Address pins should be using bank 0");
    }
    if (info->pins->cs_port != PORT_0) {
        LOG("!!! CS pins should be using bank 0");
    }
    if (info->pins->sel_port != PORT_0) {
        LOG("!!! Sel pins should be using bank 0");
    }

    // We expect to use pins 0-15 or 8-23 for address lines
    uint8_t seen_a_0_7 = 0;
    uint8_t seen_a_16_23 = 0;
    for (int ii = 0; ii < 13; ii++) {
        uint8_t pin = info->pins->addr[ii];
        if (pin < 8) {
            seen_a_0_7 = 1;
        } else if (pin > 15) {
            seen_a_16_23 = 1;
        }
    }
    if (seen_a_0_7 && seen_a_16_23) {
        LOG("!!! ROM address lines using invalid mix of pins");
    }

    // We expect to use pins 0-7 or 16-23 for data lines
    uint8_t seen_d_0_7 = 0;
    uint8_t seen_d_16_23 = 0;
    for (int ii = 0; ii < 8; ii++) {
        uint8_t pin = info->pins->data[ii];
        if (pin < 8) {
            seen_d_0_7 = 1;
        } else if (pin > 15) {
            seen_d_16_23 = 1;
        }
    }
    if (seen_d_0_7 && seen_d_16_23) {
        LOG("!!! ROM data lines using invalid mix of pins");
    }

    // Check X1/X2 pins
    if (set->rom_count > 1) {
        if (seen_a_0_7 && (info->pins->x1 > 16)) {
            LOG("!!! Multi-ROM mode, but pin X1 invalid");
        }
        if (seen_a_0_7 && (info->pins->x2 > 17)) {
            LOG("!!! Multi-ROM mode, but pin X2 invalid");
        }
        if (seen_a_16_23 && ((info->pins->x1 < 8) || (info->pins->x1 > 23))) {
            LOG("!!! Multi-ROM mode, but pin X1 invalid");
        }
        if (seen_a_16_23 && ((info->pins->x2 < 8) || (info->pins->x2 > 23))) {
            LOG("!!! Multi-ROM mode, but pin X2 invalid");
        }
        if (info->pins->x1 == info->pins->x2) {
            LOG("!!! Multi-ROM mode, but pin X1==X2");
        }
        if (info->pins->x_jumper_pull > 1) {
            LOG("!!! X jumper pull value invalid");
        }
    }

    // Check CS pins
    if (info->pins->cs1 > 15) {
        LOG("!!! CS1 pin invalid");
    }
    if (info->pins->cs2 > 15) {
        LOG("!!! CS2 pin invalid");
    }
    if (info->pins->cs3 > 15) {
        LOG("!!! CS3 pin invalid");
    }

    // Check sel jumper pull value
    if (info->pins->sel_jumper_pull > 1) {
        LOG("!!! Sel jumper pull value invalid");
    }

    // Warn if serve mode is incorrectly set for multiple ROM images
    if ((set->rom_count == 1) && (set->serve == SERVE_ADDR_ON_ANY_CS)) {
        // Correction is done in main_loop() using a local variable
        LOG("!!! Single ROM image - wrong serve mode - will correct");
    }
}

void platform_logging(void) {
#if defined(BOOT_LOGGING)
    LOG("%s", log_divider);
    LOG("Detected hardware info ...");

    // Reset the SysInfo registers
    RESET_RESET &= ~RESET_SYSINFO;

    // Output hardware information
    LOG("MCU: RP235X");
    LOG("Chip ID: 0x%08X", SYSINFO_CHIP_ID);
    char *package;
    if (SYSINFO_PACKAGE_SEL & 0b1) {
        package = "QFN60";
    } else {
        package = "QFN80";
    }
    LOG("Package: %s", package);
    LOG("Chip gitref: 0x%08X", SYSINFO_GITREF_RP2350);
    LOG("Running on core: %d", SIO_CPUID);
    LOG("PCB rev %s", sdrr_info.hw_rev);
    LOG("Firmware configured flash size: %dKB", MCU_FLASH_SIZE_KB);
    if ((MCU_RAM_SIZE_KB != RP2350_RAM_SIZE_KB) || (MCU_RAM_SIZE != RP2350_RAM_SIZE_KB * 1024)) {
        LOG("!!! RAM size mismatch: actual %dKB (%d bytes), firmware expected: %dKB (%d bytes)", MCU_RAM_SIZE_KB, MCU_RAM_SIZE, RP2350_RAM_SIZE_KB, RP2350_RAM_SIZE_KB * 1024);
    } else {
        LOG("Firmware configured RAM size: %dKB (default)", MCU_RAM_SIZE_KB);
    }
    LOG("Flash configured RAM: %dKB (%d bytes)", MCU_RAM_SIZE_KB, MCU_RAM_SIZE);

    LOG("Target freq: %dMHz", TARGET_FREQ_MHZ);
    LOG("PLL values: %d/%d/%d/%d (refdiv/fbdiv/postdiv1/postdiv2)", PLL_SYS_REFDIV, PLL_SYS_FBDIV, PLL_SYS_POSTDIV1, PLL_SYS_POSTDIV2);

#endif // BOOT_LOGGING
}

void setup_xosc(void) {
    // Initialize XOSC peripheral.  We are using the 12MHz xtal from the
    // reference hardware design, so we can use values from the datasheet.
    // See S8.2 for more details.
    //
    // Specifically:
    // - Set the startup delay to 1ms
    // - Enable the XOSC giving it the appropriate frequency range (1-15MHz)
    // - Wait for the XOSC to be enabled and stable
    XOSC_STARTUP = 47;
    XOSC_CTRL = XOSC_ENABLE | XOSC_RANGE_1_15MHz;
    while (!(XOSC_STATUS & XOSC_STATUS_STABLE));
    LOG("XOSC enabled and stable");

    // Switch CLK_REF to use XOSC instead of the ROSC
    CLOCK_REF_CTRL = CLOCK_REF_SRC_XOSC;
    while ((CLOCK_REF_SELECTED & CLOCK_REF_SRC_SEL_XOSC) != CLOCK_REF_SRC_SEL_XOSC);
}
