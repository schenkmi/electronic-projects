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
    OWL32Bit = 0,
    OWL24Bit = 1,
    OWL20Bit = 2,
    OWL16Bit = 3,
};


enum AK4137InputFormat {
    LSB32Bit = 0,
    LSB24Bit = 1,
    MSB32Bit = 2,
    I2S32or16Bit = 3,
};

/* MCLK 24.576MHz */
enum AK4137OutputSamplingFrequency {
    AKFS96kHz = 0,
    AKFS192kHz = 1,
    AKFS384kHz = 2,
};

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

