/**
 * PIC16F18056 based input channel selection + attenuator
 *
 * Copyright (c) 2022-2022, Michael Schenk
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
  * cd ~/Documents/GitHub/electronic-projects/input-sel-attenuator/software/v2
  * cp input-sel-attenuator.X/dist/default/production/input-sel-attenuator.X.production.hex hex
  */

/**
 * History
 * V1.1     2022.10.30 Implement default volume which can be set by pressing
 *                     encoder button for > 3 seconds
 */


#include "mcc_generated_files/system/system.h"
#include "rotary_encoder.h"

#define EEPROM_ADDR_CHANNEL          0x04 /* EEPROM address of current channel */
#define EEPROM_ADDR_DEFAULT_VOLUME   0x05 /* EEPROM address to store the default volume after a channel switch */

#define MUTE_OFF_BIT                 0x10
#define CHAN_SEL_MASK                0x0f

#define ROTARY_MIN_CHANNEL              0 /* minimum channel */
#define ROTARY_MAX_CHANNEL              3 /* maximum channel */
#define ROTARY_MULTI_CHANNEL            3 /* on 12PPR this gaves 3 clicks */

#define ROTARY_VOLUME_BITS              6 /* 6 bits */
#define ROTARY_MIN_VOLUME               0 /* minimum attenuation */
#define ROTARY_MAX_VOLUME               ((1 << ROTARY_VOLUME_BITS) - 1) /* (0x3f) maximum attenuation */
#define ROTARY_MULTI_VOLUME             1 /* on 12PPR this gaves 1 clicks */

#define MAIN_LOOP_WAIT                  1 /* 1ms */
#define EEPROM_SAVE_STATUS_VALUE     1000 /* 1 seconds on a 1ms loop */
#define RELAIS_SETUP_TIME               1 /* 1ms */

#define ROTARY_PUSH_DEBOUNCE            20 /* 20 ms on a 1ms timer IRQ */
#define STORE_DEFAULT_VOLUME_TIME       ((3 /* seconds */ * 1000) / ROTARY_PUSH_DEBOUNCE)

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(ROTARY_MAX_VOLUME /* channel 0 volume initial */,
              ROTARY_MAX_VOLUME /* channel 1 volume initial */,
              ROTARY_MAX_VOLUME /* channel 2 volume initial */,
              ROTARY_MAX_VOLUME /* channel 3 volume initial */,
              0x00 /* channel selection initial */,
              ROTARY_MAX_VOLUME, 
              0xff, 0xff);

enum Control { Volume = 0, Channel = 1};

typedef struct {
    int channel;
    int last_channel;
    int volume;
    int last_volume;
    int default_volume;
    /* irq changed */
    volatile enum Control control;
    uint8_t  direction;
    int encoder_count[2 /* Volume & Channel */];
    /* eeprom store */
    int eeprom_save_status_counter;
    /* rotary encoder state */
    uint8_t rotary_encoder_state;
    /* encoder push button */
    int encoder_push_debounce_counter;
    int encoder_push_counter;
    int encoder_push_action;
} Instance_t;

volatile Instance_t instance = { .channel = -1, .last_channel = -1,
                                 .volume = -1, .last_volume = -1,
                                 .default_volume = ROTARY_MAX_VOLUME,
                                 .control = Volume, .direction = DIR_NONE,
                                 .encoder_count = { 0,0 }, .eeprom_save_status_counter = -1,
                                 .rotary_encoder_state = 0, .encoder_push_debounce_counter = 0, 
                                 .encoder_push_counter = 0, .encoder_push_action = 0 };

static void init(volatile Instance_t* instance)
{
    LED_SetHigh();

    /* mute output */
     PORTB &= ~MUTE_OFF_BIT;
    __delay_ms(RELAIS_SETUP_TIME);

    /* one channel after the others */
    for (int cnt = 0; cnt < 4; cnt++) {
        uint8_t in = ((1 << cnt) & 0xff);
        PORTB |= in;
        __delay_ms(500);
        PORTB &= ~in;
    }

#if 0 /* test code */
    PORTB = 0x01;
    /* increase volume by 0.5dB steps */
    for (int test = 255; test < 0 ; test--) {
        PORTA = (unsigned char)test;
        __delay_ms(100);
    }
#endif

    /* read last used channel, channels volume will be handler inside process_channel() */
    instance->channel = eeprom_read(EEPROM_ADDR_CHANNEL);
    
    /* read default volume */
    instance->default_volume = eeprom_read(EEPROM_ADDR_DEFAULT_VOLUME);
}

/* channel selection relais are on RB0...RB3 */
static void process_channel(volatile Instance_t* instance)
{
    if (instance->channel != instance->last_channel)  {
        /* mute output */
         PORTB &= ~MUTE_OFF_BIT;
        __delay_ms(RELAIS_SETUP_TIME);

        /* always start with max attenuation after a channel switch */
        //instance->volume = eeprom_read((unsigned char)instance->channel);
        //instance->last_volume = instance->volume = ROTARY_MAX_VOLUME;
        instance->last_volume = instance->volume = instance->default_volume;

        PORTA = ((PORTA & ~ROTARY_MAX_VOLUME) | ((unsigned char)instance->volume & ROTARY_MAX_VOLUME));

        /* clear and set new channel */
        PORTB = ((PORTB & ~CHAN_SEL_MASK) | ((1 << instance->channel) & CHAN_SEL_MASK));

        __delay_ms(RELAIS_SETUP_TIME);

        /* unmute outputs */
        PORTB |= MUTE_OFF_BIT;

        instance->last_channel = instance->channel;
        instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
    }
}

/* attenuator relaise are on RA0...RA5 */
static void process_volume(volatile Instance_t* instance)
{
    if (instance->volume != instance->last_volume)  {
        unsigned char volume = ((unsigned char)instance->volume & ROTARY_MAX_VOLUME);

        if ((PORTA & ROTARY_MAX_VOLUME) != volume) {
            /* something needs to be changed */
#if 1 /* improved setting algo, with direction in mind */
            if (instance->direction == DIR_CW) { /* clockwise, volume increase */
                for (int cnt = 0; cnt < ROTARY_VOLUME_BITS; cnt++) {
                    uint8_t bit = ((1 << cnt) & 0xff);

                    if ((PORTA & bit) != (volume & bit)) {
                        /* port bit needs to be changed */
                        if (volume & bit) {
                           PORTA |= bit;
                        } else {
                            PORTA &= ~bit ;
                        }
                        /* changed relay, wait a bit */
                        __delay_ms(1);
                    }
                }
            } else { /* counter clockwise, volume decrease */
                for (int cnt = (ROTARY_VOLUME_BITS - 1); cnt >= 0; cnt--) {
                    uint8_t bit = ((1 << cnt) & 0xff);

                    if ((PORTA & bit) != (volume & bit)) {
                        /* port bit needs to be changed */
                        if (volume & bit) {
                           PORTA |= bit;
                        } else {
                            PORTA &= ~bit ;
                        }
                        /* changed relay, wait a bit */
                        __delay_ms(1);
                    }
                }
            }
#else
            /* mute output */
             PORTB &= ~MUTE_OFF_BIT;
            __delay_ms(RELAIS_SETUP_TIME);

            PORTA = ((PORTA & ~ROTARY_MAX_VOLUME) | ((unsigned char)instance->volume & ROTARY_MAX_VOLUME));
            __delay_ms(RELAIS_SETUP_TIME);

            /* unmute outputs */
            PORTB |= MUTE_OFF_BIT;
#endif
            instance->last_volume = instance->volume;
            instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
        }
    }
}

static void eeprom_save_status(volatile Instance_t* instance)
{
    if (instance->eeprom_save_status_counter != -1) {
        if (--instance->eeprom_save_status_counter == 0) {
            if (eeprom_read(EEPROM_ADDR_CHANNEL) != (unsigned char)instance->channel) {
                /* store current selected channel */
                eeprom_write(EEPROM_ADDR_CHANNEL, (unsigned char)instance->channel);
            }
            if (eeprom_read((unsigned char)instance->channel) != (unsigned char)instance->volume) {
                /* store current volume of channel */
                eeprom_write((unsigned char)instance->channel, (unsigned char)instance->volume);
            }
            if (eeprom_read(EEPROM_ADDR_DEFAULT_VOLUME) != (unsigned char)instance->default_volume) {
                /* store current default volume which is applied after a channel switch */
                eeprom_write(EEPROM_ADDR_DEFAULT_VOLUME, (unsigned char)instance->default_volume);
            }
            instance->eeprom_save_status_counter = -1;
        }
    }
}

static void process_encoder_button(volatile Instance_t* instance)
{
    if (instance->encoder_push_action) {
        if (instance->encoder_push_counter >= STORE_DEFAULT_VOLUME_TIME) {
            /* store current volume as default value */
            instance->default_volume = instance->volume;
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
            instance->direction = DIR_NONE;
            instance->encoder_count[instance->control] = 0;  
        }
        
        /* reset after operation */
        instance->encoder_push_counter = instance->encoder_push_action = 0;
    } 
}

/* uses 10us time, measured with LED_Toggle();*/
void timer_callback(void)
{
/* use to measure irq call time */
#if 0
    LED_Toggle();
#endif
    uint8_t encoder_direction = encoder_read(&instance.rotary_encoder_state);
    if (encoder_direction != DIR_NONE) {
        /* detect direction, if changed, reset rotary encoder vars */
        if (instance.direction != encoder_direction) {
            instance.encoder_count[instance.control] = 0;
        }
        instance.direction = encoder_direction;

        if (encoder_direction == DIR_CW) {
            instance.encoder_count[instance.control]++;
        } else if (encoder_direction == DIR_CCW) {
            instance.encoder_count[instance.control]--;
        }

        if (instance.control == Volume)  {
            /**
             * volume works inverse as it is a attenuator
             * 0   : 0dB attenuation
             * 255 : 127dB attenuation
             */
            int value = instance.volume;

            if (instance.encoder_count[instance.control] >= ROTARY_MULTI_VOLUME) {
                value--;
                instance.encoder_count[instance.control] = 0;
            }
            else if (instance.encoder_count[instance.control] <= -ROTARY_MULTI_VOLUME) {
                value++;
                instance.encoder_count[instance.control] = 0;
            }

            /* for volume stop on max or min */
            if (value > ROTARY_MAX_VOLUME) {
                instance.volume = ROTARY_MAX_VOLUME;
            } else if (value < ROTARY_MIN_VOLUME) {
                instance.volume = 0;
            } else {
                instance.volume = value;
            }
        } else {
            int value = instance.channel;

            if (instance.encoder_count[instance.control] >= ROTARY_MULTI_CHANNEL) {
                value++;
                instance.encoder_count[instance.control] = 0;
            }
            else if (instance.encoder_count[instance.control] <= -ROTARY_MULTI_CHANNEL) {
                value--;
                instance.encoder_count[instance.control] = 0;
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

    if (instance.encoder_push_action != 1) {
        /* no push action pending */
        uint8_t encoder_switch_level = ENCSWITCH_GetValue();
        if (encoder_switch_level == 0) {
            instance.encoder_push_counter = (++instance.encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
        } else {
            if (instance.encoder_push_counter >= 1) {
                /* flag push action to be processed */
                instance.encoder_push_action = 1;
            }
            instance.encoder_push_debounce_counter = 0;
        }
    }

/* use for measure irq execution time (10us) */
#if 0
    LED_Toggle();
#endif
}

/**
 * Main application
 */
int main(void)
{
    SYSTEM_Initialize();

    init(&instance);

    /* install irq handlers */
    Timer0_OverflowCallbackRegister(timer_callback);

    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    while (1) {
        process_channel(&instance);
        process_volume(&instance);
        process_encoder_button(&instance);
        eeprom_save_status(&instance);
        __delay_ms(MAIN_LOOP_WAIT);
    }
}
