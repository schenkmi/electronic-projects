/**
 * PIC16F18446 based async sample rate converter
 * for TI/BB SRC4392/SRC4382
 * PCM1792A
 *
 * Copyright (c) 2021-2024, Michael Schenk
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

#include <stdbool.h>

#pragma once

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * DIT routing mode enum
 */
enum SRC4392DigitalAudioInterfaceTransmitter { 
    DITUpsample = 0,
    DITPassthrough = 1,
}; 

/**
 * Digital de-emphasis enum
 */
enum SRC4392DeEmphasis {
    DeEmphasisAuto = 0,
    DeEmphasisOff = 1,
};

/**
 * Upsampling rate enum
 */
enum SRC4392UpsamplingRate {
    UpsamplingTo192kHz = 0,
    UpsamplingTo96kHz = 1,
};

/**
 * Output world length enum
 */
enum SRC4392OutputWordLength {
    OWL24Bit = 0x00,
    OWL20Bit = 0x40,
    OWL18Bit = 0x80,
    OWL16Bit = 0xc0,
};

/**
 * Sampling rate enum
 */
enum SRC4392SamplingRate {
    SamplingRateUnknown = 0,
    SamplingRate32_kHz = 1,
    SamplingRate44_1_kHz = 2,
    SamplingRate48_kHz = 3,
    SamplingRate64_kHz = 4,
    SamplingRate88_2_kHz = 5,
    SamplingRate96_kHz = 6,
    SamplingRate128_kHz = 7,
    SamplingRate176_4_kHz = 8,
    SamplingRate192_kHz = 9,
};

typedef struct {
  enum SRC4392DeEmphasis deemphases; 
  enum SRC4392DigitalAudioInterfaceTransmitter digital_audio_interface_transmitter;
  enum SRC4392UpsamplingRate upsample_rate;
  enum SRC4392OutputWordLength output_word_length;
} SRC4392_t;

void src4392_init(SRC4392_t* instance);
void src4392_set_input(int input);
void src4392_set_attenuation(int right, int left);
void src4392_mute(bool mute);
enum SRC4392SamplingRate src4392_get_sample_rate(void);
void src4392_test();

#ifdef	__cplusplus
}
#endif
