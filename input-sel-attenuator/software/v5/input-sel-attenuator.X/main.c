/**
 * PIC16F18056 based input channel selection + attenuator
 *
 * Copyright (c) 2022-2024, Michael Schenk
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

 /**
  * Save hex
  * cd /work/electronic-projects/input-sel-attenuator/software/v4
  * cp ./input-sel-attenuator.X/dist/default/production/input-sel-attenuator.X.production.hex hex
  */

/**
 * History
 * V1.5     2024.06.01 Add delay between SYSTEM_Initialize and factory reset
 * V1.4     2024.05.26 New MCC, factory reset
 * V1.3     2023.12.16 Improve usability
 * V1.2     2023.12.13 Set attenuator to maximum in init()
 * V1.1     2022.10.30 Implement default attenuation which can be set by pressing
 *                     encoder button for > 3 seconds
 */

/**
 * On start the default attenuation for each channel will be read and set.
 * If default attenuation was never set the maximum attenuation will be used.
 *
 * The default attenuation for the current channel can be set by pressing
 * attenuation for more than 3 seconds.
 *
 * On channel change the current attenuation of this channel will be set and
 * the channel will be stored as default channel.
 */

#include "mcc_generated_files/system/system.h"
#include "rotary_encoder.h"
#include "irmp/irmp.h"

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
#define RELAIS_SETUP_TIME                 1 /* 1ms */

#define ROTARY_PUSH_DEBOUNCE             20 /* 20 ms on a 1ms timer IRQ */
#define STORE_DEFAULT_ATTENUATION_TIME ((3 /* seconds */ * 1000) / ROTARY_PUSH_DEBOUNCE) /* 3 seconds till storing default attenuation */

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(ROTARY_MAX_ATTENUATION /* channel 0 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 1 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 2 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 3 attenuation initial */,
              ROTARY_MIN_CHANNEL     /* channel selection initial     */,
              0xff, 0xff, 0xff);

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

volatile Instance_t instance = {
  .mode = Dual, .channel = -1, .last_channel = -1,
  .attenuation = -1, .last_attenuation = -1,
  .eeprom_save_status_counter = -1,
  .channel_attenuation = {
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
  },
  .control =  Volume,
  .encoder = {
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0,
      .encoder_push_debounce_counter = 0, .encoder_push_counter = 0, .encoder_push_action = 0  },
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0,
      .encoder_push_debounce_counter = 0, .encoder_push_counter = 0, .encoder_push_action = 0  },
  },
};

static void init(volatile Instance_t* instance)
{
  LED_SetHigh();

  /* mute output */
   PORTB &= ~CHAN_SEL_MASK;
  __delay_ms(RELAIS_SETUP_TIME);

  /* max possible attenuation on attenuation */
  PORTA = ((PORTA & ~ROTARY_MAX_ATTENUATION) | ROTARY_MAX_ATTENUATION);

  /* one channel after the others */
  for (int cnt = 0; cnt <= ROTARY_MAX_CHANNEL; cnt++) {
    uint8_t in = ((1 << cnt) & 0xff);
    PORTB |= in;
    __delay_ms(500);
    PORTB &= ~in;
  }

#if 0 /* test code */
  PORTB = 0x01;
  /* increase attenuation by 0.5dB steps */
  for (int test = ROTARY_MAX_ATTENUATION; test < 0 ; test--) {
    PORTA = (unsigned char)test;
    __delay_ms(100);
  }
#endif

  /* read last used channel, channels attenuation will be handler inside process_channel() */
  instance->channel = eeprom_read(EEPROM_ADDR_CHANNEL);

  /* read default attenuation for each channel and assign to channel attenuation */
  for (uint8_t cnt = 0; cnt <= ROTARY_MAX_CHANNEL; cnt++) {
    instance->channel_attenuation[cnt].attenuation = instance->channel_attenuation[cnt].default_attenuation = eeprom_read(cnt);
  }
}

/* channel selection relay are on RB0...RB3 */
static void process_channel(volatile Instance_t* instance)
{
  if (instance->channel != instance->last_channel)  {
    if (instance->last_channel != -1) {
      /* store current used attenuation on channel */
      instance->channel_attenuation[instance->last_channel].attenuation = instance->attenuation;
    }

    /* mute output */
     PORTB &= ~CHAN_SEL_MASK;
    __delay_ms(RELAIS_SETUP_TIME);

    /* always start with last attenuation used for this channel */
    instance->last_attenuation = instance->attenuation = instance->channel_attenuation[instance->channel].attenuation;
    PORTA = ((PORTA & ~ROTARY_MAX_ATTENUATION) | ((unsigned char)instance->attenuation & ROTARY_MAX_ATTENUATION));

    /* clear and set new channel */
    PORTB = ((PORTB & ~CHAN_SEL_MASK) | ((1 << instance->channel) & CHAN_SEL_MASK));
    __delay_ms(RELAIS_SETUP_TIME);

    instance->last_channel = instance->channel;
    instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
  }
}

/* attenuator relay are on RA0...RA5 */
static void process_attenuation(volatile Instance_t* instance) {
  if (instance->attenuation != instance->last_attenuation) {
    unsigned char attenuation = ((unsigned char) instance->attenuation & ROTARY_MAX_ATTENUATION);

    if ((PORTA & ROTARY_MAX_ATTENUATION) != attenuation) {
      /* something needs to be changed */
#if 1 /* improved setting algo, with direction in mind */
      if (instance->encoder[Volume].direction == DIR_CW) { /* clockwise, attenuation increase */
        for (int cnt = 0; cnt < ROTARY_ATTENUATION_BITS; cnt++) {
          uint8_t bit = ((1 << cnt) & 0xff);

          if ((PORTA & bit) != (attenuation & bit)) {
            /* port bit needs to be changed */
            if (attenuation & bit) {
              PORTA |= bit;
            } else {
              PORTA &= ~bit;
            }
            /* changed relay, wait a bit */
            __delay_ms(RELAIS_SETUP_TIME);
          }
        }
      } else { /* counter clockwise, attenuation decrease */
        for (int cnt = (ROTARY_ATTENUATION_BITS - 1); cnt >= 0; cnt--) {
          uint8_t bit = ((1 << cnt) & 0xff);

          if ((PORTA & bit) != (attenuation & bit)) {
            /* port bit needs to be changed */
            if (attenuation & bit) {
              PORTA |= bit;
            } else {
              PORTA &= ~bit;
            }
            /* changed relay, wait a bit */
            __delay_ms(RELAIS_SETUP_TIME);
          }
        }
      }
#else
      /* mute output */
       PORTB &= ~CHAN_SEL_MASK;
      __delay_ms(RELAIS_SETUP_TIME);

      PORTA = ((PORTA & ~ROTARY_MAX_ATTENUATION) | ((unsigned char)instance->attenuation & ROTARY_MAX_ATTENUATION));
      __delay_ms(RELAIS_SETUP_TIME);
#endif
      instance->last_attenuation = instance->attenuation;
    }
  }
}

static void eeprom_save_status(volatile Instance_t* instance) {
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

static void process_encoder_button(volatile Instance_t* instance) {
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

  if (instance.encoder[Volume].encoder_push_action != 1) {
    /* no push action pending */
    uint8_t encoder_switch_level = ENC1SWITCH_GetValue();
    if (encoder_switch_level == 0) {
      instance.encoder[Volume].encoder_push_counter =
          (++instance.encoder[Volume].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
    } else {
      if (instance.encoder[Volume].encoder_push_counter >= 1) {
        /* flag push action to be processed */
        instance.encoder[Volume].encoder_push_action = 1;
      }
      instance.encoder[Volume].encoder_push_debounce_counter = 0;
    }
  }

  if (instance.encoder[Channel].encoder_push_action != 1) {
    /* no push action pending */
    uint8_t encoder_switch_level = ENC2SWITCH_GetValue();
    if (encoder_switch_level == 0) {
      instance.encoder[Channel].encoder_push_counter =
          (++instance.encoder[Channel].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
    } else {
      if (instance.encoder[Channel].encoder_push_counter >= 1) {
        /* flag push action to be processed */
        instance.encoder[Channel].encoder_push_action = 1;
      }
      instance.encoder[Channel].encoder_push_debounce_counter = 0;
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
void encoder_timer_callback(void)
{
/* use to measure irq call time */
#if 0
  LED_Toggle();
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
  LED_Toggle();
#endif
}

/* every 66us (15.151kHz) */
void ir_timer_callback(void)
{
/* use to measure irq call time */
#if 0
  LED_Toggle();
#endif
  irmp_ISR ();
#if 0
  LED_Toggle();
#endif
}

/* Factory reset */
static void factory_reset() {
    if (ENC2SWITCH_GetValue() == 0) {
        while(ENC2SWITCH_GetValue() == 0) {
            __delay_ms(100);  
        }

        for (int cnt = 0; cnt < 10; cnt++) {
            /* LED on */
            LED_Toggle();
             __delay_ms(500);  
        }

        eeprom_write(0x00, ROTARY_MAX_ATTENUATION);
        eeprom_write(0x01, ROTARY_MAX_ATTENUATION);
        eeprom_write(0x02, ROTARY_MAX_ATTENUATION);
        eeprom_write(0x03, ROTARY_MAX_ATTENUATION);
        eeprom_write(0x04, ROTARY_MIN_CHANNEL);
    }
}

/**
 * Main application
 */
int main(void)
{
  SYSTEM_Initialize();

   __delay_ms(STARTUP_WAIT);  
   
  /* weak pull-up so safe to call without connected rotary board */
  factory_reset();

  /* install irq handlers */
  Timer0_OverflowCallbackRegister(encoder_timer_callback);
  Timer2_OverflowCallbackRegister(ir_timer_callback);

  /* Enable the Global Interrupts */
  INTERRUPT_GlobalInterruptEnable();

  /* Enable the Peripheral Interrupts */
  INTERRUPT_PeripheralInterruptEnable();
  
  init(&instance);
  
  while (1) {
    process_channel(&instance);
    process_attenuation(&instance);
    process_encoder_button(&instance);
    eeprom_save_status(&instance);
    __delay_ms(MAIN_LOOP_WAIT);
  }
}