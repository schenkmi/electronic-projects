/**
 * PIC16F18056 based SPDIF receiver and async sample rate converter
 * for SRC4392, AK4118, AK4137
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
 * commercially licensed software with Michael Schenk software
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

//#include "mcc_generated_files/system/system.h"

/* I2C addresses */
#define SRC4392_I2C_ADDR        0x70    /* 1110000 R(1) or /W(0) => 0xe0 write, 0xe1 read */
#define PCM1792A_I2C_ADDR       0x4c    /* 1001100 R(1) or /W(0) => 0x98 write, 0x99 read */

#define CS8416_I2C_ADDR     0x10 /* Page 34: [0010 AD2 AD1 AD0] added R(1) or /W(0) => 0x20 write, 0x21 read */




/* Functions */
#define __USE_SRC4392__
//#define __USE_AK4118__
//#define __USE_AK4137__
//#define __USE_CS8416__
//#define __USE_PCM1792A__
//#define __USE_IR__
//#define __USE_PCM1702__
#define __USE_PCM1704__

/* Rotary Encoder */

//#define __USE_TWO_ROTARY_ENCODER__


#define ENC1_CHANNELA_GETVALUE      ENC1CHANA_GetValue()
#define ENC1_CHANNELB_GETVALUE      ENC1CHANB_GetValue()

//#define ENC2_CHANNELA_GETVALUE      ENC2CHANA_GetValue()
//#define ENC2_CHANNELB_GETVALUE      ENC2CHANB_GetValue()

