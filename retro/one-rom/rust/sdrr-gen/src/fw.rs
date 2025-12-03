// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

// Firmware specific types

use onerom_config::mcu::Processor;

/// PLL configuration and calculation
pub struct PllConfig {
    pub proc: Processor,
}

impl PllConfig {
    pub fn new(proc: Processor) -> Self {
        Self { proc }
    }

    /// Calculate PLL values for target frequency using HSI (16 MHz)
    /// Returns (PLLM, PLLN, PLLP, PLLQ) or None if frequency not achievable
    fn calculate_stm32_pll_hsi(
        &self,
        target_freq_mhz: u32,
        overclock: bool,
    ) -> Option<(u8, u16, u8, u8)> {
        // Validate target frequency is within limits
        if target_freq_mhz > self.proc.max_sysclk_mhz() && !overclock {
            return None;
        }

        // HSI = 16 MHz, target VCO input = 2 MHz for best jitter
        const HSI_MHZ: u32 = 16;
        const PLLM: u8 = 8; // 16/8 = 2 MHz VCO input
        const VCO_IN_MHZ: u32 = HSI_MHZ / PLLM as u32;

        // Try PLLP values: 2, 4, 6, 8
        for pllp in [2u8, 4, 6, 8] {
            let vco_mhz = target_freq_mhz * pllp as u32;

            // Check VCO frequency is in valid range
            if vco_mhz >= self.proc.vco_min_mhz() && vco_mhz <= self.proc.vco_max_mhz(overclock) {
                let plln = vco_mhz / VCO_IN_MHZ;

                // Check PLLN is in valid range (50-432)
                if (50..=432).contains(&plln) {
                    // Calculate PLLQ for USB (48 MHz target)
                    let pllq_raw = (vco_mhz as f32 / 48.0).round() as u8;
                    let pllq = pllq_raw.clamp(2, 15);

                    return Some((PLLM, plln as u16, pllp, pllq));
                }
            }
        }

        None
    }

    /// Calculate RP2350 PLL values for 12MHz XOSC input
    /// Returns (REFDIV, FBDIV, POSTDIV1, POSTDIV2) or None if not achievable
    fn calculate_rp2350_pll_12mhz(
        &self,
        target_freq_mhz: u32,
        overclock: bool,
    ) -> Option<(u8, u16, u8, u8)> {
        // Validate target frequency
        if target_freq_mhz > self.proc.max_sysclk_mhz() && !overclock {
            return None;
        }

        const XOSC_MHZ: u32 = 12;
        const REFDIV: u8 = 1; // Fixed for 12MHz

        // Try POSTDIV combinations (prefer higher PD1:PD2 ratios)
        for pd2 in 1..=7u8 {
            for pd1 in 1..=7u8 {
                let vco_mhz = target_freq_mhz * pd1 as u32 * pd2 as u32;

                if vco_mhz >= self.proc.vco_min_mhz() && vco_mhz <= self.proc.vco_max_mhz(overclock)
                {
                    let fbdiv = vco_mhz / XOSC_MHZ;
                    if (16..=320).contains(&fbdiv) && (vco_mhz.is_multiple_of(XOSC_MHZ)) {
                        return Some((REFDIV, fbdiv as u16, pd1, pd2));
                    }
                }
            }
        }
        None
    }

    /// Generate PLL #defines for target frequency
    fn generate_stm32_pll_defines(&self, target_freq_mhz: u32, overclock: bool) -> Option<String> {
        if let Some((m, n, p, q)) = self.calculate_stm32_pll_hsi(target_freq_mhz, overclock) {
            // Calculate intermediate values for comments
            let hsi_mhz = 16;
            let vco_input_mhz = hsi_mhz / m as u32;
            let fvco_mhz = vco_input_mhz * n as u32;
            let sysclk_mhz = fvco_mhz / p as u32;
            let usb_mhz = fvco_mhz / q as u32;

            // Convert PLL_P division factor to register encoding
            let pll_p_reg = match p {
                2 => "0b00",
                4 => "0b01",
                6 => "0b10",
                8 => "0b11",
                _ => unreachable!("Invalid PLL_P value: {}", p),
            };

            Some(format!(
                "//   HSI={}MHz\n//   VCO_input={}MHz\n//   fVCO={}MHz\n//   SYSCLK={}MHz\n//   USB={}MHz\n#define PLL_M    {}\n#define PLL_N    {}\n#define PLL_P    {}  // div {}\n#define PLL_Q    {}",
                hsi_mhz, vco_input_mhz, fvco_mhz, sysclk_mhz, usb_mhz, m, n, pll_p_reg, p, q
            ))
        } else {
            None
        }
    }

    // Unlike the Pico SDK's vcocalc.py we are interested in power savings over decrease in jitter.
    fn generate_rp2350_pll_defines(&self, target_freq_mhz: u32, overclock: bool) -> Option<String> {
        if let Some((refdiv, fbdiv, postdiv1, postdiv2)) =
            self.calculate_rp2350_pll_12mhz(target_freq_mhz, overclock)
        {
            // Calculate intermediate values for comments
            const CLK_REF_MHZ: u32 = 12;
            let vco_input_mhz = CLK_REF_MHZ / refdiv as u32;
            let fvco_mhz = vco_input_mhz * fbdiv as u32;
            let sysclk_mhz = fvco_mhz / (postdiv1 as u32 * postdiv2 as u32);

            Some(format!(
                "//   CLK_REF={}MHz\n//   VCO_input={}MHz\n//   fVCO={}MHz\n//   SYSCLK={}MHz\n#define PLL_SYS_REFDIV    {}\n#define PLL_SYS_FBDIV     {}\n#define PLL_SYS_POSTDIV1  {}\n#define PLL_SYS_POSTDIV2  {}",
                CLK_REF_MHZ, vco_input_mhz, fvco_mhz, sysclk_mhz, refdiv, fbdiv, postdiv1, postdiv2
            ))
        } else {
            None
        }
    }

    pub fn generate_pll_defines(&self, target_freq_mhz: u32, overclock: bool) -> Option<String> {
        match self.proc {
            Processor::RP2350 => self.generate_rp2350_pll_defines(target_freq_mhz, overclock),
            _ => self.generate_stm32_pll_defines(target_freq_mhz, overclock), // Rename existing function
        }
    }

    fn calculate_pll_hsi(
        &self,
        target_freq_mhz: u32,
        overclock: bool,
    ) -> Option<(u8, u16, u8, u8)> {
        match self.proc {
            Processor::RP2350 => self.calculate_rp2350_pll_12mhz(target_freq_mhz, overclock),
            _ => self.calculate_stm32_pll_hsi(target_freq_mhz, overclock),
        }
    }

    pub fn is_frequency_valid(&self, target_freq_mhz: u32, overclock: bool) -> bool {
        #[allow(clippy::match_single_binding)]
        match self {
            _ => {
                // F4 family uses HSI PLL, check if target frequency is achievable
                self.calculate_pll_hsi(target_freq_mhz, overclock).is_some()
            }
        }
    }
}
