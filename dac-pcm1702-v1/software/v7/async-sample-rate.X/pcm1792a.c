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

#include "i2c.h"
#include "pcm1792a.h"
#include <stddef.h>

#define PCM1792A_I2C_SLAVE_ADDR     0x4c /* 1001100 R(1) or /W(0) => 0x98 write, 0x99 read */

#define PCM1792A_REG16              0x10 /* 0x10 == Reg 16, Digital Attenuation Level Setting left */
#define  PCM1792A_REG16_VALUE        0xff /* 0dB, not attenuation */

#define PCM1792A_REG17              0x11 /* 0x11 == Reg 17, Digital Attenuation Level Setting right */
#define  PCM1792A_REG17_VALUE        0xff /* 0dB, not attenuation */



#define PCM1792A_REG18              0x12 /* 0x13 == Reg 18 */
#define  PCM1792A_REG18_ATT_CTRL_EN     (1 << 7) 


#define PCM1792A_REG19              0x13 /* 0x13 == Reg 19 */
#define  PCM1792A_REG19_FLT_SLOW     (1 << 1) 

static PCM1792A_t* pcm1792a_instance = NULL;

/* Read one byte from the PCM1792A via I2C */
static uint8_t pcm1792a_read(uint8_t reg)
{
  return I2C1_Read1ByteRegister(PCM1792A_I2C_SLAVE_ADDR, reg); 
}


/* Write one byte to the PCM1792A via I2C */
static void pcm1792a_write(uint8_t reg, uint8_t val) {
    I2C1_Write1ByteRegister(PCM1792A_I2C_SLAVE_ADDR, reg, val);
}

void pcm1792a_init(PCM1792A_t* instance) {
    pcm1792a_instance = instance;
    
    /* digital filter setup */
    uint8_t value = pcm1792a_read(PCM1792A_REG19);
    if (instance->filter_rolloff == TI_Sharp) {
        value &= ~PCM1792A_REG19_FLT_SLOW;
    } else if (instance->filter_rolloff == TI_Slow) {
        value |= PCM1792A_REG19_FLT_SLOW; 
    }
        
    pcm1792a_write(PCM1792A_REG19, value);

    /* no attenuation */
    pcm1792a_write(PCM1792A_REG16, PCM1792A_REG16_VALUE);
    pcm1792a_write(PCM1792A_REG17, PCM1792A_REG17_VALUE);
}

void pcm1792a_set_attenuation(int right, int left) {
    uint8_t right_att = (right < 0) ? 0 : (right > 0xff) ? 0xff : (uint8_t)right;
    uint8_t left_att = (left < 0) ? 0 : (left > 0xff) ? 0xff : (uint8_t)left;
 
    pcm1792a_write(PCM1792A_REG16, left_att);
    pcm1792a_write(PCM1792A_REG17, right_att);
    
    /* we must enable attenuation control in register 18*/
    uint8_t reg = pcm1792a_read(PCM1792A_REG18);
    reg |= PCM1792A_REG18_ATT_CTRL_EN;

    pcm1792a_write(PCM1792A_REG18, reg);
    
}
