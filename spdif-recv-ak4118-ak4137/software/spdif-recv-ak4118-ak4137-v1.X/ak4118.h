/**
 * PIC16F18056 based async sample rate converter
 * for AK4118 / AK4137
 *
 * Copyright (c) 2024-2025, Michael Schenk
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
 * TBD
 */
enum AK4118AudioDataFormat {
    AK4118_I2S = 1, /* I2S format */

};


typedef struct {
    uint8_t input;
    uint8_t sampling_rate;
    uint8_t status_register;
} PreviousRegisters_t;

typedef struct {
    enum AK4118AudioDataFormat data_format;
    PreviousRegisters_t previous;
} AK4118_t;

void ak4118_init(AK4118_t* instance);
void ak4118_set_input(int input);
void ak4118_print_samplerate(void);
void ak4118_print_spdif_status(void);
void ak4118_print_input(void);

#ifdef	__cplusplus
}
#endif
