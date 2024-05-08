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


#include "mcc_generated_files/system/system.h"

uint8_t  I2C1_Read1ByteRegister(uint16_t address, uint8_t reg) {
bool i2c_status;
uint8_t value;

i2c_status = I2C1_WriteRead(address, &reg, 1, &value, 1);
if (i2c_status) {
    while (I2C1_IsBusy());
    return value;
} else {
    return 0;
}

}

#if 0
static void AT24CM02_DataToSendSet(block_t *block, uint8_t *dataToSend)
{
    dataToSend[0] = (block->wordAdress >> 8) &0xFF;
    dataToSend[1] = block->wordAdress & 0xFF;
 
    for (uint16_t index = 0; index < block->dataSize; ++index) {
        dataToSend[index + 2] = *(block->data + index);
    }
}
#endif
void I2C1_Write1ByteRegister(uint16_t address, uint8_t reg, uint8_t data) {
    bool i2c_status;
    
    //uint16_t to_write = (reg << 8 || data);
    uint8_t blob[2] = { reg, data};
    
    i2c_status = I2C1_Write(address, blob, (sizeof(blob) / sizeof(blob[0])));
if (i2c_status) {
    while (I2C1_IsBusy());
}
    
}

