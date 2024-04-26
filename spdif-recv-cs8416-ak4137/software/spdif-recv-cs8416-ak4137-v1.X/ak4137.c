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
#include "i2c.h"
#include "ak4137.h"

#include <stddef.h>


#define AK4137_I2C_SLAVE_ADDR     0x11 /* Page 34: [00100 CAD1 CAD0] added R(1) or /W(0) => 0x22 write, 0x23 read */



#define AK4137_REG_RESET_MUTE         0x00


#define AK4137_REG_PCMCONT0         0x01
#define  AK4137_REG_PCMCONT0_SLOW     (1 << 7) 
#define  AK4137_REG_PCMCONT0_SHORT_DELAY     (1 << 6) 
#define  AK4137_REG_PCMCONT0_DEEMPHASIS_OFF     (1 << 4) 
#define AK4137_REG_PCMCONT0_INPUT_FMT_24LSB (1 << 0)
#define AK4137_REG_PCMCONT0_INPUT_FMT_I2S (3 << 0)

#define AK4137_REG_PCMCONT1         0x02


static AK4137_t* ak4137_instance = NULL;

/* Read one byte from the AK4137 via I2C */
static uint8_t ak4137_instance_read(uint8_t reg)
{
  return I2C1_Read1ByteRegister(AK4137_I2C_SLAVE_ADDR, reg); 
}


/* Write one byte to the AK4137 via I2C */
static void ak4137_instance_write(uint8_t reg, uint8_t val) {
    I2C1_Write1ByteRegister(AK4137_I2C_SLAVE_ADDR, reg, val);
}

void ak4137_preinit(AK4137_t* instance) {
    
    /* output word length page 48 */
    switch (instance->output_word_length) {
        case OWL32Bit:
            OBIT0_SetLow();
            OBIT1_SetLow();
            break;
        case OWL20Bit:
            OBIT0_SetLow();
            OBIT1_SetHigh();
            break;
        case OWL16Bit:
            OBIT0_SetHigh();
            OBIT1_SetHigh();
            break;
        case OWL24Bit:   
        default:
            /* 24Bit output */
            OBIT0_SetHigh();
            OBIT1_SetLow();
            break;
    }
    
    /* I2S format see page 48 */
    ODIF0_SetHigh();
    ODIF1_SetLow();
    
    /* enable dither */
    DITHER_SetHigh();
    
    /* mode 0 see page 46 */
    
    // CM0 ... CM3
    // 1 0 1 0 => LRCLK 192kHz (Mode 5 128FSO)
    // X X X 1 => LRCLK 384kHz (Mode 6 64FSO)
    
    /* For MCLK = 24.576MHz */
    switch (instance->output_sampling_frequency) {
        case AKFS384kHz:
            CM0_SetHigh();
            CM1_SetLow();
            CM2_SetHigh();
            CM3_SetHigh();
            break;
        case AKFS192kHz:
        default:
            CM0_SetHigh();
            CM1_SetLow();
            CM2_SetHigh();
            CM3_SetLow();
            break;
    }

    

}


void ak4137_init(AK4137_t* instance) {
    uint8_t reg;
    ak4137_instance = instance;
    
    /* reset release */
    ak4137_instance_write(AK4137_REG_RESET_MUTE, 0x01);
    
    reg = (AK4137_REG_PCMCONT0_SLOW | AK4137_REG_PCMCONT0_SHORT_DELAY | \
           AK4137_REG_PCMCONT0_DEEMPHASIS_OFF);
    
    switch (ak4137_instance->input_format) {
        case LSB32Bit:
            reg |= (0x00 << 0);
            break;
        case LSB24Bit:
            reg |= (0x01 << 0);
            break;
        case MSB32Bit:
            reg |= (0x02 << 0);
            break;
        case I2S32or16Bit:
            reg |= (0x03 << 0);
            break;
    }
  
    ak4137_instance_write(AK4137_REG_PCMCONT0, reg);   
}
