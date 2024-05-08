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

#include "mcc_generated_files/system/system.h"
#include "rotary_encoder.h"

extern volatile Instance_t instance;


/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */
#define R_START 0x0

#if 1 /* ENABLE_HALF_STEP */
/* Use the half-step state table (emits a code at 00 and 11) */
#define R_CCW_BEGIN   0x1
#define R_CW_BEGIN    0x2
#define R_START_M     0x3
#define R_CW_BEGIN_M  0x4
#define R_CCW_BEGIN_M 0x5

const unsigned char ttable[][4] = {
  // 00                  01              10            11
  {R_START_M,           R_CW_BEGIN,     R_CCW_BEGIN,  R_START},           // R_START (00)
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},           // R_CCW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},           // R_CW_BEGIN
  {R_START_M,           R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},           // R_START_M (11)
  {R_START_M,           R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},  // R_CW_BEGIN_M
  {R_START_M,           R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW}  // R_CCW_BEGIN_M
};
#else
/* Use the full-step state table (emits a code at 00 only) */
#define R_CW_FINAL   0x1
#define R_CW_BEGIN   0x2
#define R_CW_NEXT    0x3
#define R_CCW_BEGIN  0x4
#define R_CCW_FINAL  0x5
#define R_CCW_NEXT   0x6

const unsigned char ttable[][4] = {
  // 00         01           10           11
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},           // R_START
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},  // R_CW_FINAL
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},           // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},           // R_CW_NEXT
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},           // R_CCW_BEGIN
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW}, // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START}            // R_CCW_NEXT
};
#endif

/**
 * Grab state of input pins, determine new state from the pins
 * and state table, and return the emit bits (ie the generated event).
 * @param rotary_encoder_state
 * @return 
 */
static uint8_t encoder1_read(volatile uint8_t* rotary_encoder_state) {
    /* read CHANA and CHANB, CW => up, CCW => down */
    uint8_t pinstate = (uint8_t)((ENC1_CHANA_GetValue() << 1) | ENC1_CHANB_GetValue());
    *rotary_encoder_state = ttable[*rotary_encoder_state & 0xf][pinstate];
    return (*rotary_encoder_state & 0x30);
}

/**
 * Grab state of input pins, determine new state from the pins
 * and state table, and return the emit bits (ie the generated event).
 * @param rotary_encoder_state
 * @return 
 */
static uint8_t encoder2_read(volatile uint8_t* rotary_encoder_state) {
#if 1
    return 0;
#else
    /* read CHANA and CHANB, CW => up, CCW => down */
    uint8_t pinstate = (uint8_t)((ENC2_CHANA_GetValue() << 1) | ENC2_CHANB_GetValue());
    *rotary_encoder_state = ttable[*rotary_encoder_state & 0xf][pinstate];
    return (*rotary_encoder_state & 0x30);
#endif
}

void eeprom_save_status(volatile Instance_t* instance) {
  if (instance->eeprom_save_status_counter != -1) {
    if (--instance->eeprom_save_status_counter == 0) {
      /* if stored default channel not equal current one, update default channel */
      if (eeprom_read(EEPROM_ADDR_CHANNEL) != (unsigned char) instance->channel) {
        eeprom_write(EEPROM_ADDR_CHANNEL, (unsigned char) instance->channel);
      }

      /* if default value for channel changed, store it */
      if (eeprom_read((unsigned char) instance->channel) != (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation) {
        /* store current default attenuation which is applied after a channel switch */
        eeprom_write((unsigned char) instance->channel, (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation);
      }
      instance->eeprom_save_status_counter = -1; /* not action */
    }
  }
}

void process_encoder_button(volatile Instance_t* instance) {
  if (instance->mode == Dual) { /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    /* Encoder 1 attenuation */
    if (instance->encoder[Volume].encoder_push_action) {
      if (instance->encoder[Volume].encoder_push_counter >= STORE_DEFAULT_ATTENUATION_TIME) {
        /* store current attenuation as default value */
        instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
        instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
      } else {
        /* no short press function for now */
      }
      /* reset after operation */
      instance->encoder[Volume].encoder_push_counter = instance->encoder[Volume].encoder_push_action = 0;
    }

    /* Encoder 2 channel */
    if (instance->encoder[Channel].encoder_push_action) {
      /* reset after operation */
      instance->encoder[Volume].encoder_push_counter = instance->encoder[Volume].encoder_push_action = 0;
    }
  } else {
    if (instance->encoder[Combined].encoder_push_action) {
      if (instance->encoder[Combined].encoder_push_counter >= STORE_DEFAULT_ATTENUATION_TIME) {
        /* store current attenuation as default value */
        instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
        instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
      } else {
        /* switch control mode */
        if (instance->control == Volume) {
          instance->control = Channel;
        } else {
          instance->control = Volume;
        }
        /* for debugging switching between attenuation and channel */
#if 0
        LED_Toggle();
#endif
        /* reset rotary encoder vars */
        instance->encoder[Combined].direction = DIR_NONE;
        instance->encoder[Combined].encoder_count[instance->control] = 0;
      }

      /* reset after operation */
      instance->encoder[Combined].encoder_push_counter = instance->encoder[Combined].encoder_push_action = 0;
    }
  }
}

static void timer_callback_process_single(void) {
  uint8_t encoder_direction = encoder1_read(&instance.encoder[Combined].rotary_encoder_state);
  if (encoder_direction != DIR_NONE) {
    /* detect direction, if changed, reset rotary encoder vars */
    if (instance.encoder[Combined].direction != encoder_direction) {
      instance.encoder[Combined].encoder_count[instance.control] = 0;
    }
    instance.encoder[Combined].direction = encoder_direction;

    if (encoder_direction == DIR_CW) {
      instance.encoder[Combined].encoder_count[instance.control]++;
    } else if (encoder_direction == DIR_CCW) {
      instance.encoder[Combined].encoder_count[instance.control]--;
    }

    if (instance.control == Volume) {
      /**
       * attenuation works inverse as it is a attenuator
       * 0   : 0dB attenuation
       * 255 : 127dB attenuation
       */
      int value = instance.attenuation;

      if (instance.encoder[Combined].encoder_count[instance.control] >= ROTARY_MULTI_ATTENUATION) {
        value--;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      } else if (instance.encoder[Combined].encoder_count[instance.control] <= -ROTARY_MULTI_ATTENUATION) {
        value++;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      }

      /* for attenuation stop on max or min */
      if (value > ROTARY_MAX_ATTENUATION) {
        instance.attenuation = ROTARY_MAX_ATTENUATION;
      } else if (value < ROTARY_MIN_ATTENUATION) {
        instance.attenuation = 0;
      } else {
        instance.attenuation = value;
      }
    } else {
      int value = instance.channel;

      if (instance.encoder[Combined].encoder_count[instance.control] >= ROTARY_MULTI_CHANNEL) {
        value++;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      } else if (instance.encoder[Combined].encoder_count[instance.control] <= -ROTARY_MULTI_CHANNEL) {
        value--;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      }

      /* channel is rotary continous */
      if (value > ROTARY_MAX_CHANNEL) {
        instance.channel = 0;
      } else if (value < ROTARY_MIN_CHANNEL) {
        instance.channel = ROTARY_MAX_CHANNEL;
      } else {
        instance.channel = value;
      }
    }
  }

  if (instance.encoder[Combined].encoder_push_action != 1) {
    /* no push action pending */
    uint8_t encoder_switch_level = ENC1_SWITCH_GetValue();
    if (encoder_switch_level == 0) {
      instance.encoder[Combined].encoder_push_counter = (++instance.encoder[Combined].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
    } else {
      if (instance.encoder[Combined].encoder_push_counter >= 1) {
        /* flag push action to be processed */
        instance.encoder[Combined].encoder_push_action = 1;
      }
      instance.encoder[Combined].encoder_push_debounce_counter = 0;
    }
  }
}


void rotary_encoder_timer_callback(void) {
    /* use to measure irq call time */
#if 0
    LED_D5_Toggle();
#endif

  /* single encoder for both attenuation and channel */
  timer_callback_process_single();
/* use for measure irq execution time (81us) */

#if 0
    LED_D5_Toggle();
#endif
}

