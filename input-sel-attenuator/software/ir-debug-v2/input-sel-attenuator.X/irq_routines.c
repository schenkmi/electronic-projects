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

#include "definitions.h"

static void timer_callback_process_dual(void) {
  /* encoder1 used for attenuation */
  uint8_t encoder_direction = encoder1_read(&instance.encoder[Volume].rotary_encoder_state);
  if (encoder_direction != DIR_NONE) {
    /* detect direction, if changed, reset rotary encoder vars */
    if (instance.encoder[Volume].direction != encoder_direction) {
      instance.encoder[Volume].encoder_count[0] = 0;
    }
    instance.encoder[Volume].direction = encoder_direction;

    if (encoder_direction == DIR_CW) {
      instance.encoder[Volume].encoder_count[0]++;
    } else if (encoder_direction == DIR_CCW) {
      instance.encoder[Volume].encoder_count[0]--;
    }

    /**
     * attenuation works inverse as it is a attenuator
     * 0   : 0dB attenuation
     * 255 : 127dB attenuation
     */
    int value = instance.attenuation;

    if (instance.encoder[Volume].encoder_count[0] >= ROTARY_MULTI_ATTENUATION) {
      value--;
      instance.encoder[Volume].encoder_count[0] = 0;
    } else if (instance.encoder[Volume].encoder_count[0] <= -ROTARY_MULTI_ATTENUATION) {
      value++;
      instance.encoder[Volume].encoder_count[0] = 0;
    }

    /* for attenuation stop on max or min */
    if (value > ROTARY_MAX_ATTENUATION) {
      instance.attenuation = ROTARY_MAX_ATTENUATION;
    } else if (value < ROTARY_MIN_ATTENUATION) {
      instance.attenuation = 0;
    } else {
      instance.attenuation = value;
    }
  }

  /* encoder2 used for channel */
  encoder_direction = encoder2_read(&instance.encoder[Channel].rotary_encoder_state);
  if (encoder_direction != DIR_NONE) {
    /* detect direction, if changed, reset rotary encoder vars */
    if (instance.encoder[Channel].direction != encoder_direction) {
      instance.encoder[Channel].encoder_count[0] = 0;
    }
    instance.encoder[Channel].direction = encoder_direction;

    if (encoder_direction == DIR_CW) {
      instance.encoder[Channel].encoder_count[0]++;
    } else if (encoder_direction == DIR_CCW) {
      instance.encoder[Channel].encoder_count[0]--;
    }

    int value = instance.channel;

    if (instance.encoder[Channel].encoder_count[0] >= ROTARY_MULTI_CHANNEL) {
      value++;
      instance.encoder[Channel].encoder_count[0] = 0;
    } else if (instance.encoder[Channel].encoder_count[0] <= -ROTARY_MULTI_CHANNEL) {
      value--;
      instance.encoder[Channel].encoder_count[0] = 0;
    }

    /* channel is rotary continuous */
    if (value > ROTARY_MAX_CHANNEL) {
      instance.channel = 0;
    } else if (value < ROTARY_MIN_CHANNEL) {
      instance.channel = ROTARY_MAX_CHANNEL;
    } else {
      instance.channel = value;
    }
  }

  /* push button logic */
  instance.ms_counter++;
  
  if (ENC1SWITCH_GetValue() == 0) {
    /* Button pressed */
    if (!instance.button[Volume].button_pressed) {
      instance.button[Volume].press_time = instance.ms_counter;
      instance.button[Volume].button_pressed = true;
    }
  } else { 
    /* Button released */
    if (instance.button[Volume].button_pressed) {
      uint16_t duration = instance.ms_counter - instance.button[Volume].press_time;
      instance.button[Volume].button_pressed = false;
   
      if (duration >= ROTARY_PUSH_DEBOUNCE_TIME) {
        instance.button[Volume].release_time = instance.ms_counter;

        if (duration >= ROTARY_PUSH_LONG_PRESS_TIME) {
          instance.button[Volume].press = LongPress; 
          instance.button[Volume].click_count = 0;
          instance.button[Volume].waiting_for_double = false;
        } else {
            /* Short press */
            instance.button[Volume].click_count++;
            instance.button[Volume].waiting_for_double = true;
        }
      }
    }
  }

  
  
  /* Check for double click timeout */
  if (instance.button[Volume].waiting_for_double && (instance.ms_counter - instance.button[Volume].release_time > ROTARY_PUSH_DOUBLE_CLICK_TIME)) {
    if (instance.button[Volume].click_count == 1) {
      /* Single click */
      instance.button[Volume].press = SinglePress;
    } else if (instance.button[Volume].click_count == 2) {
      /* Double click */
      instance.button[Volume].press = DoublePress;
    }
    instance.button[Volume].click_count = 0;
    instance.button[Volume].waiting_for_double = false;
  }
  
  
  
  if (ENC2SWITCH_GetValue() == 0) {
    /* Button pressed */
    if (!instance.button[Channel].button_pressed) {
      instance.button[Channel].press_time = instance.ms_counter;
      instance.button[Channel].button_pressed = true;
    }
  } else { 
    /* Button released */
    if (instance.button[Channel].button_pressed) {
      uint16_t duration = instance.ms_counter - instance.button[Channel].press_time;
      instance.button[Channel].button_pressed = false;
   
      if (duration >= ROTARY_PUSH_DEBOUNCE_TIME) {
        instance.button[Channel].release_time = instance.ms_counter;

        if (duration >= ROTARY_PUSH_LONG_PRESS_TIME) {
          instance.button[Channel].press = LongPress; 
          instance.button[Channel].click_count = 0;
          instance.button[Channel].waiting_for_double = false;
        } else {
            /* Short press */
            instance.button[Channel].click_count++;
            instance.button[Channel].waiting_for_double = true;
        }
      }
    }
  }
  
    /* Check for double click timeout */
  if (instance.button[Channel].waiting_for_double && (instance.ms_counter - instance.button[Channel].release_time > ROTARY_PUSH_DOUBLE_CLICK_TIME)) {
    if (instance.button[Channel].click_count == 1) {
      /* Single click */
      instance.button[Channel].press = SinglePress;
    } else if (instance.button[Channel].click_count == 2) {
      /* Double click */
      instance.button[Channel].press = DoublePress;
    }
    instance.button[Channel].click_count = 0;
    instance.button[Channel].waiting_for_double = false;
  }
  
  
//  if (instance.encoder[Volume].encoder_push_action != 1) {
//    /* no push action pending */
//    uint8_t encoder_switch_level = ENC1SWITCH_GetValue();
//    if (encoder_switch_level == 0) {
//      instance.encoder[Volume].encoder_push_counter =
//          (++instance.encoder[Volume].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
//    } else {
//      if (instance.encoder[Volume].encoder_push_counter >= 1) {
//        /* flag push action to be processed */
//        instance.encoder[Volume].encoder_push_action = 1;
//      }
//      instance.encoder[Volume].encoder_push_debounce_counter = 0;
//    }
//  }

//  if (instance.encoder[Channel].encoder_push_action != 1) {
//    /* no push action pending */
//    uint8_t encoder_switch_level = ENC2SWITCH_GetValue();
//    if (encoder_switch_level == 0) {
//      instance.encoder[Channel].encoder_push_counter =
//          (++instance.encoder[Channel].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
//    } else {
//      if (instance.encoder[Channel].encoder_push_counter >= 1) {
//        /* flag push action to be processed */
//        instance.encoder[Channel].encoder_push_action = 1;
//      }
//      instance.encoder[Channel].encoder_push_debounce_counter = 0;
//    }
//  }
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
    uint8_t encoder_switch_level = ENC1SWITCH_GetValue();
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

/* uses 10us time, measured with LED_Toggle();*/
void encoder_timer_callback(void) {
/* use to measure irq call time */
#if 0
  led_toggel();
#endif
  if (instance.mode == Dual) {
    /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    timer_callback_process_dual();
  } else {
    /* single encoder for both attenuation and channel */
    timer_callback_process_single();
  }
/* use for measure irq execution time (10us) */
#if 0
  led_toggel();
#endif
}

/* every 66us (15.151kHz) */
void ir_timer_callback(void) {
/* use to measure irq call time */
#if 0
  led_toggel();
#endif
  irmp_ISR();
#if 0
  led_toggel();
#endif
}
