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
//#define DIT_UPSAMPLE		0	// upsample
//#define DIT_LOOPOUT		1	// loop-back

enum SRC4392DigitalAudioInterfaceTransmitter { DITUpsample = 0, DITPassthrough = 1 /*Loopout = 1 */}; 

/*
 * Digital de-emphasis enums
 */
//#define DEEMPH_AUTO		0	// auto
//#define DEEMPH_OFF		1	// off

enum SRC4392DeEmphasis { DeEmphasisAuto = 0, DeEmphasisOff = 1};
    
enum SRC4392UpsamplingRate { UpsamplingTo192kHz = 0, UpsamplingTo96kHz = 1 };


enum SRC4392OutputWordLength { OWL24Bit = 0x00, OWL20Bit = 0x40, OWL18Bit = 0x80, OWL16Bit = 0xc0 };








//// Sample rate enums
//#define SAMPLERATE_UNKNOWN	0	// unknown
//#define SAMPLERATE_32KHZ	1	// 32.0KHz
//#define SAMPLERATE_44KHZ	2	// 44.1KHz
//#define SAMPLERATE_48KHZ	3	// 48.0KHz
//#define SAMPLERATE_64KHZ	4	// 64.0KHz
//#define SAMPLERATE_88KHZ	5	// 88.2KHz
//#define SAMPLERATE_96KHZ	6	// 96.0KHz
//#define SAMPLERATE_128KHZ	7	// 128.0KHz
//#define SAMPLERATE_176KHZ	8	// 176.4KHz
//#define SAMPLERATE_192KHZ	9	// 192.0KHz



enum SRC4392SamplingRate {
    SamplingRateUnknown = 0,
    SamplingRate32_kHz = 1,
    SamplingRate44_1_kHz = 2,
    SamplingRate48_kHz = 3,
    SamplingRate64_kHz = 4,
    SamplingRate88_2_kHz = 5,
    SamplingRate96_kHz = 6,
    SamplingRate128_kHz = 7,
    SamplingRate176_4_kHz = 8,
    SamplingRate192_kHz = 9,
};




typedef struct {
  enum SRC4392DeEmphasis deemphases;
  
  enum SRC4392DigitalAudioInterfaceTransmitter digital_audio_interface_transmitter;
  
  enum SRC4392UpsamplingRate upsample_rate;
  enum SRC4392OutputWordLength output_word_length;
} SRC4392_t;



void src4392_init(SRC4392_t* instance);

//void set_deemphasis(enum SRC4392DeEmphasis de_emphasis);
//void set_upsample(enum SRC4392UpsamplingRate rate);
//void set_dit_mode(SRC4392_t* instance, uint8_t input, enum SRC4392DigitalAudioInterfaceTransmitter dit);



//void set_input(uint8_t input, enum SRC4392DigitalAudioInterfaceTransmitter dit);


void set_input(int input);

enum SRC4392SamplingRate get_sample_rate(void);



#ifdef	__cplusplus
}
#endif



