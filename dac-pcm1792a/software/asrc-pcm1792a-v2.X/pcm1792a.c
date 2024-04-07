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

#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "pcm1792a.h"

#define PCM1792A_I2C_SLAVE_ADDR     0x4c /* 1001100 R /W => 0x98 write, 0x99 read */

#define PCM1792A_REG16              0x10 /* 0x10 == Reg 16, Digital Attenuation Level Setting left */
#define PCM1792A_REG16_VALUE        0xff /* 0dB, not attenuation */

#define PCM1792A_REG17              0x11 /* 0x11 == Reg 17, Digital Attenuation Level Setting left */
#define PCM1792A_REG17_VALUE        0xff /* 0dB, not attenuation */

#define PCM1792A_REG19              0x13 /* 0x13 == Reg 19 */
#define PCM1792A_REG19_VALUE        0x02 /* 0x02 FLT = Slow rolloff */

static void pcm1792a_write(uint8_t reg, uint8_t val) {
  I2C1_Write1ByteRegister(PCM1792A_I2C_SLAVE_ADDR, reg, val);
}

void pcm1792a_init(void) {
  pcm1792a_write(PCM1792A_REG19, PCM1792A_REG19_VALUE);

  // attenuation left -31.5dB
  //pcm1792a_write(PCM1792A_REG16, 0xc0);
  // attenuation right -31.5dB
  //pcm1792a_write(PCM1792A_REG17, 0xc0);
}
