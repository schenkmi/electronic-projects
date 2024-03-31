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

#pragma once

#ifdef	__cplusplus
extern "C" {
#endif

// TODO define enum
/*
 * DIT routing mode enums
 */
#define DIT_UPSAMPLE		0	// upsample
#define DIT_LOOPOUT		1	// loop-back

enum SRC4392DigitalAudioInterfaceTransmitter { DITUpsample = 0, DITPassthrough = 1 /*Loopout = 1 */}; 

/*
 * Digital de-emphasis enums
 */
#define DEEMPH_AUTO		0	// auto
#define DEEMPH_OFF		1	// off

enum SRC4392DeEmphasis { DeEmphasisAuto = 0, DeEmphasisOff = 1};
    
enum UpsamplingRate { fs192kHz = 0, fs96kHz = 1 };

typedef struct {
  
  enum UpsamplingRate upsample_rate;
  uint8_t output_word_length;
} SRC4392_t;
    
void src4392_init(SRC4392_t* instance);

void set_deemphasis(enum SRC4392DeEmphasis de_emphasis);
void set_upsample(enum UpsamplingRate rate);
void set_dit_mode(SRC4392_t* instance, uint8_t input, enum SRC4392DigitalAudioInterfaceTransmitter dit);
void set_input(uint8_t input, enum SRC4392DigitalAudioInterfaceTransmitter dit);
uint8_t get_sample_rate(SRC4392_t* instance);



#ifdef	__cplusplus
}
#endif



