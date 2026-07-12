/**
 * PIC16F18056 based async sample rate converter
 * for AK4118 / AK4137
 *
 * Copyright (c) 2026-2026, Michael Schenk
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

#include "project_configuration.h"

#ifdef __USE_AK4118__

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

/**
 * Audio Serial Interface Format DIF[2..0]
 */
enum AK4118AudioDataOutputFormat {
    AK4118_16Bit_Right = 0, /* SDTO 16bit, Right justified */
    AK4118_18Bit_Right = 1, /* SDTO 18bit, Right justified */
    AK4118_20Bit_Right = 2, /* SDTO 20bit, Right justified */
    AK4118_24Bit_Right = 3, /* SDTO 24bit, Right justified */
    AK4118_24Bit_Left = 4,  /* SDTO 24bit, Left justified  */
    AK4118_I2S = 5,         /* SDTO 24bit, I2S             */
};

typedef struct {
    uint8_t input;
    uint8_t sampling_rate;
    uint8_t status_register;
} PreviousRegisters_t;

typedef struct {
    enum AK4118AudioDataOutputFormat data_format;
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

#endif /* __USE_AK4118__ */
