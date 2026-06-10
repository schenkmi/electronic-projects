/**
 * PIC16F18056 based async sample rate converter
 * for AK4118 / AK4137
 *
 * Copyright (c) 2024-2026, Michael Schenk
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

#include "mcc_generated_files/system/system.h"

bool I2C1_Read1ByteRegister(uint16_t address, uint8_t reg, uint8_t* data) {
    *data = 0;
    
    if (!I2C1_WriteRead(address, &reg, 1, data, 1)) {
        return false;
    }
    
    /* wait until transfer finishes */
    while (I2C1_IsBusy());
    
    /* check for errors */
    if (I2C1_ErrorGet() != I2C_ERROR_NONE) {
        return false;
    }
    
    return true;
    
}

bool I2C1_Write1ByteRegister(uint16_t address, uint8_t reg, uint8_t data) {
    uint8_t blob[2] = { reg, data};

    if (!I2C1_Write(address, blob, (sizeof(blob) / sizeof(blob[0])))) {
        return false;
    }

    /* wait until transfer finishes */
    while (I2C1_IsBusy());
    
    /* check for errors */
    if (I2C1_ErrorGet() != I2C_ERROR_NONE) {
        return false;
    }
    
    return true;
}
