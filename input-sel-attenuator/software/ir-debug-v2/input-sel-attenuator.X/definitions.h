/**
 * PIC16F18056 based input channel selection + attenuator
 *
 * Copyright (c) 2025-2025, Michael Schenk
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

#include "mcc_generated_files/system/system.h"
#include "rotary_encoder.h"
#include "irmp/irmp.h"

#define ATT_CTRL_DIRECTION                1 /* attenuator relay control with direction algorithm */
#define ATT_CTRL_MAKE_BEFORE_BREAK        2 /* attenuator relay control with make before break algorithm */
#define ATT_CTRL ATT_CTRL_MAKE_BEFORE_BREAK /* define algorithm to be used for attenuator relay control */

#define STARTUP_WAIT                    250 /* wait 250ms after SYSTEM_Initialize */

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
#define RELAIS_MAX_SETUP_TIME             3 /* 3ms for G6K-2F DC5 */

#define ROTARY_PUSH_DEBOUNCE_TIME        20 /* 20 ms on a 1ms timer IRQ */
#define ROTARY_PUSH_LONG_PRESS_TIME    1000 /* 1000 ms on a 1ms timer IRQ */
#define ROTARY_PUSH_DOUBLE_CLICK_TIME   500 /* 500 ms on a 1ms timer IRQ */

#define DEFAULT_SAVE_COUNTDOWN         1000 /* 1000 ms on a 1ms timer IRQ */

/* One For All TV Hitachi 2676 */
#define IR_PROTOCOL       IRMP_RC5_PROTOCOL
#define IR_REMOTE_ADDRESS            0x0001
#define IR_KEY_1                          1
#define IR_KEY_2                          2
#define IR_KEY_3                          3
#define IR_KEY_4                          4
#define IR_KEY_OK                        53
#define IR_KEY_CH_UP                     32
#define IR_KEY_CH_DOWN                   33
#define IR_KEY_VOL_UP                    16
#define IR_KEY_VOL_DOWN                  17
#define IR_KEY_MUTE                      13

enum Control { Combined = 0, Volume = 0, Channel = 1};
enum Mode { Single = 0, Dual = 1 };
enum SaveMode { SaveNever = 0, SaveOnChange = 1, SaveOnLongPress = 2 };

enum ButtonPress { NoPress = 0,  SinglePress = 1, DoublePress = 2, LongPress = 3 };
typedef struct {
  bool button_pressed;
  bool   waiting_for_double;
  int click_count;
  uint16_t press_time;
  uint16_t release_time; 
  enum ButtonPress press;
} Button_t;

typedef struct {
  uint8_t direction;
  int encoder_count[2 /* Volume = 0,  Channel = 1 */];
  /* rotary encoder state */
  uint8_t rotary_encoder_state;
  /* encoder push button */
  Button_t button;
} RotaryEncoder_t;

typedef struct {
  int default_attenuation;
  int attenuation;
} ChannelVolume_t;

enum SaveAction { NoSaveAction = 0,  SaveVolume = 0x1, SaveChannel = 0x2 };

typedef struct {
  IRMP_DATA data;
} IR_t;

typedef struct {
  enum Mode mode; /* single or dual encoder mode */
  enum SaveMode save_mode[2 /* 0 = Volume, 1 = Channel */];
  uint8_t save_action;
  int save_countdown_counter;
  int channel;
  int last_channel;
  int attenuation;
  int last_attenuation;
  ChannelVolume_t channel_attenuation[ROTARY_MAX_CHANNEL + 1]; /* channel 0..3 */
  /* irq changed */
  volatile enum Control control;
  uint16_t ms_counter; 
  RotaryEncoder_t encoder[2 /* 0 = Combined/Volume, 1 = Channel */];
  /* IR receiver */
  IR_t ir;
} Instance_t;

extern volatile Instance_t instance;
