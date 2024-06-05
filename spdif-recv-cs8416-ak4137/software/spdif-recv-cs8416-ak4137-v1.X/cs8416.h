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

enum CS8416OutputFormat {
    CS_MSB = 0, /* Left justified (MSB justified) */
    CS_LSB = 1,      /* Right justified (LSB justified) */
    CS_I2S = 2, /* I2S format */
};

/**
 * Output world length enum
 */
enum CS8416OutputWordLength {
    CS_OWL24Bit = 0,
    CS_OWL20Bit = 1,
    CS_OWL16Bit = 2,
    CS_OWLDirect = 3,
};

typedef struct {
    enum CS8416OutputFormat output_format;
    enum CS8416OutputWordLength output_word_length;
} CS8416_t;

void cs8416_init(CS8416_t* instance);

#ifdef	__cplusplus
}
#endif
