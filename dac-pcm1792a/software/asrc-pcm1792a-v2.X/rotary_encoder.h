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

#include <stdint.h>

#pragma once

#ifdef	__cplusplus
extern "C" {
#endif

#define DIR_NONE  0x00 /* read() return value - No complete step/movement */
#define DIR_CW    0x10 /* read() return value - Clockwise step/movement */
#define DIR_CCW   0x20 /* return value - Counter-clockwise step/movement */

//uint8_t encoder1_read(volatile uint8_t* rotary_encoder_state);
//uint8_t encoder2_read(volatile uint8_t* rotary_encoder_state);


#define CHAN_SEL_MASK                  0x0f

#define EEPROM_ADDR_CHANNEL            0x04 /* EEPROM address of current channel */

#define ROTARY_MIN_CHANNEL                0 /* minimum channel */
#define ROTARY_MAX_CHANNEL                3 /* maximum channel */
#define ROTARY_MULTI_CHANNEL              3 /* on 12PPR this gaves 3 clicks */

#define ROTARY_ATTENUATION_BITS           6 /* 6 bits */
#define ROTARY_MIN_ATTENUATION            0 /* minimum attenuation */
#define ROTARY_MAX_ATTENUATION         ((1 << ROTARY_ATTENUATION_BITS) - 1) /* (0x3f) maximum attenuation */
#define ROTARY_MULTI_ATTENUATION          1 /* on 12PPR this gaves 1 clicks */

#define MAIN_LOOP_WAIT                    1 /* 1ms */
#define EEPROM_SAVE_STATUS_VALUE       1000 /* 1 seconds on a 1ms loop */
#define RELAIS_SETUP_TIME                 1 /* 1ms */

#define ROTARY_PUSH_DEBOUNCE             20 /* 20 ms on a 1ms timer IRQ */
#define STORE_DEFAULT_ATTENUATION_TIME ((3 /* seconds */ * 1000) / ROTARY_PUSH_DEBOUNCE) /* 3 seconds till storing default attenuation */


enum Control { Combined = 0, Volume = 0, Channel = 1};
enum Mode { Single = 0, Dual = 1 };

typedef struct {
  uint8_t direction;
  int encoder_count[2 /* Volume = 0,  Channel = 1 */];
  /* rotary encoder state */
  uint8_t rotary_encoder_state;
  /* encoder push button */
  int encoder_push_debounce_counter;
  int encoder_push_counter;
  int encoder_push_action;
} RotaryEncoder_t;

typedef struct {
  int default_attenuation;
  int attenuation;
} ChannelVolume_t;

typedef struct {
  enum Mode mode; /* single or dual encoder mode */
  int channel;
  int last_channel;
  int attenuation;
  int last_attenuation;
  int eeprom_save_status_counter;
  ChannelVolume_t channel_attenuation[ROTARY_MAX_CHANNEL + 1]; /* channel 0..3 */
  /* irq changed */
  volatile enum Control control;
  RotaryEncoder_t encoder[2 /* 0 = Combined/Volume, 1 = Channel */];
} Instance_t;





void eeprom_save_status(volatile Instance_t* instance);

void process_encoder_button(volatile Instance_t* instance);

void rotary_encoder_timer_callback(void);

#ifdef	__cplusplus
}
#endif
