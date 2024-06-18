/**
 * PIC16F18056 based async sample rate converter
 * for CS8416 / AK4137
 *
 * Copyright (c) 2024-2024, Michael Schenk
 * All Rights Reserved
 *
 * Author: Michael Schenk
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * OEMs, ISVs, VARs and other distributors that combine and distribute
 * commercially licensed software with Michael Schenks software
 * and do not wish to distribute the source code for the commercially
 * licensed software under version 2, or (at your option) any later
 * version, of the GNU General Public License (the "GPL") must enter
 * into a commercial license agreement with Michael Schenk.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file LICENSE.txt. If not, write to
 * the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * http://www.gnu.org/licenses/gpl-2.0.html
 */

#pragma once

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Output world length enum
 */
enum AK4137OutputWordLength {
    AK_OWL32Bit = 0,
    AK_OWL24Bit = 1,
    AK_OWL20Bit = 2,
    AK_OWL16Bit = 3,
};

enum AK4137InputFormat {
    AK_LSB32Bit = 0,
    AK_LSB24Bit = 1,
    AK_MSB32Bit = 2,
    AK_I2S32or16Bit = 3,
};

/* MCLK 24.576MHz */
enum AK4137OutputSamplingFrequency {
    AK_FS96kHz = 0,
    AK_FS192kHz = 1,
    AK_FS384kHz = 2,
};

/**
 * Neutrik A2-D
 *
 * Reference PCM1702 DAC 1kHz 0dBFs sinus => 0dB reference (Vout = 2.12 Veff)
 * 
 * Short Delay Slow Rolloff
 * ------------------------
 * Freq       Attenuation  
 * 2kHz      -0.02dB
 * 4kHz      -0.43dB
 * 10kHz    -11.43dB
 * 
 * Short Delay Sharp Rolloff
 * ------------------------
 * Freq       Attenuation  
 * 2kHz       0.00dB
 * 4kHz       0.00dB
 * 10kHz     -0.03dB
 * 16kHz     -0.12dB
 * 20kHz     -0.23dB
 */
enum AK4137DigitalFilter {
    AK_SharpRollOff = 0,
    AK_SlowRollOff = 1,
    AK_ShortDelaySharpRollOff = 2,
    AK_ShortDelaySlowRollOff = 3,
};

typedef struct {
    enum AK4137InputFormat input_format;
    enum AK4137DigitalFilter digital_filter;
    enum AK4137OutputSamplingFrequency output_sampling_frequency;
    enum AK4137OutputWordLength output_word_length;
} AK4137_t;

void ak4137_preinit(AK4137_t* instance);
void ak4137_init(AK4137_t* instance);

#ifdef	__cplusplus
}
#endif

