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
  * cd ~/Documents/GitHub/electronic-projects/input-sel-attenuator/software/v1
  * cp input-sel-attenuator.X/dist/default/production/input-sel-attenuator.X.production.hex hex
  */

#include "mcc_generated_files/system/system.h"

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(0xff /* channel 0 volume initial */,
              0xff /* channel 1 volume initial */,
              0xff /* channel 2 volume initial */,
              0xff /* channel 3 volume initial */,
              0x00 /* channel selection initial */,
              0xff, 0xff, 0xff);

/* EEPROM address of current channel */
#define EEPROM_ADR_CHANNEL 0x04

#define SELIN1  PORTBbits.RB0
#define SELIN2  PORTBbits.RB1
#define SELIN3  PORTBbits.RB2
#define SELIN4  PORTBbits.RB3
#define LED     PORTBbits.RB4

//#define MUTE_OFF_BIT    0x10
#define CHAN_SEL_MASK   0x0f


#define ROTARY_MIN_CHANNEL       0 /* minimum channel */
#define ROTARY_MAX_CHANNEL       3 /* maximum channel */
#define ROTARY_MULTI_CHANNEL     6 /* on 12PPR this gaves 3 clicks */

#define ROTARY_MIN_VOLUME             0 /* minimum channel */
#define ROTARY_MAX_VOLUME           255 /* maximum channel */
#define ROTARY_MULTI_VOLUME           2 /* on 12PPR this gaves 1 clicks */

#define MAIN_LOOP_WAIT               20 /* 20ms */
#define EEPROM_SAVE_STATUS_VALUE    250 /* 5 seconds on a 20ms loop */

enum Control { Volume = 0, Channel = 1};

enum Direction  { Undefined = 0, CCW = 1 /* counter clock wise */, CW = 2 /* clock wise */ };

typedef struct {

    //int selected;
    int channel;

    //int last_selected;
    int last_channel;



    int volume;
    int last_volume;



    /* irq changed */
    volatile enum Control control;
    volatile enum Direction direction;

    volatile int rotary_counter[2];
    //volatile int volume_counter;

    uint8_t encoder_value[2 /* Volume & Channel */];// = { 0, 0 };
    int encoder_count[2 /* Volume & Channel */];// = { 0, 0 };


    /* eeprom store */
    int eeprom_save_status_counter;

} Instance_t;

volatile Instance_t instance = { .channel = -1, .last_channel = -1,
                                 .volume = -1, .last_volume = -1,
                                 .control = Volume, .direction = Undefined,
                                 .rotary_counter = { 0, 0 }, .encoder_value = { 0,0 },
                                 .encoder_count = { 0,0 }, .eeprom_save_status_counter = -1 };

static void init(volatile Instance_t* instance)
{
    PORTA = 0xff; /* max attenuation */
    PORTB &= ~CHAN_SEL_MASK;
    LED = 1;

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
    instance->channel = eeprom_read(EEPROM_ADR_CHANNEL);

    instance->direction = Undefined;
}

void push_button(void)
{
    if (instance.control == Volume) {
        instance.control = Channel;
    } else {
        instance.control = Volume;
    }

    /* reset rotary encoder vars */
    instance.direction = Undefined;
    instance.encoder_value[instance.control] = 0;
    instance.encoder_count[instance.control] = 0;
}

const int8_t table[] = { 0, -1, +1, 0, +1, 0, 0, -1, -1, 0, 0, +1, 0, +1, -1, 0 };

void encoder_click(void)
{
    /* read CHANA and CHANB, CW => up, CCW => down */
    uint8_t curr_enc_val = (uint8_t)((ENCCHANA_GetValue() << 1) | ENCCHANB_GetValue());
    instance.encoder_value[instance.control] = (uint8_t)((instance.encoder_value[instance.control] << 2) | curr_enc_val);

    /* detect direction, if changed, reset rotary encoder vars */
    if (instance.direction == Undefined) {
        if (table[instance.encoder_value[instance.control] & 0x0f] == -1) {
            instance.direction = CCW;
        } else if (table[instance.encoder_value[instance.control] & 0x0f] == +1) {
            instance.direction = CW;
        }
    } else if ((instance.direction == CCW) && (table[instance.encoder_value[instance.control] & 0x0f] == +1)) {
        /* change from down to up, reset */
        instance.direction = CW;
        instance.encoder_count[instance.control] = 0;
    } else if ((instance.direction == CW) && (table[instance.encoder_value[instance.control] & 0x0f] == -1)) {
        /* change from up to down, reset */
        instance.direction = CCW;
        instance.encoder_count[instance.control] = 0;
    }

    instance.encoder_count[instance.control] += table[instance.encoder_value[instance.control] & 0x0f];

    if (instance.control == Volume)  {
        /**
         * volume works inverse as it is a attenuator
         * 0   : 0dB attenuation
         * 255 : 127dB attenuation
         */
        int value = instance.volume;

        if (instance.encoder_count[instance.control] >= ROTARY_MULTI_VOLUME) {
            //value--;
              value -=  4;
            instance.encoder_count[instance.control] = 0;
        }
        else if (instance.encoder_count[instance.control] <= -ROTARY_MULTI_VOLUME) {
            //value++;
            value += 4;
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

/* channel selection relais are on RB0...RB3 */
static void process_channel(volatile Instance_t* instance)
{
    if (instance->channel != instance->last_channel)  {
        /* clear all channels (mute) */
        PORTB &= ~CHAN_SEL_MASK;

        /* read stored volume from new channel and apply */
        instance->volume = eeprom_read((unsigned char)instance->channel);
        instance->last_volume = instance->volume;

        if (PORTA != (unsigned char)instance->volume) {
            PORTA = (unsigned char)instance->volume;
        }

        __delay_ms(100);

        /* set new channel */
        PORTB |= ((1 << instance->channel) & CHAN_SEL_MASK);

        instance->last_channel = instance->channel;
        instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
    }
}

/* attenuator relaise are on RA0...RA7 */
static void process_volume(volatile Instance_t* instance)
{
    if (instance->volume != instance->last_volume)  {
        if (PORTA != (unsigned char)instance->volume) {
           // PORTA = PORTA | 0x80;
            
            //__delay_ms(10);
            
            //if ()
            PORTA = 0xff;
            for (int cnt = 7; cnt >= 0; cnt--) {
            //for (int cnt = 0; cnt < 8; cnt++) {    
                __delay_ms(10);
                uint8_t in = ((1 << cnt) & 0xff);
                if ((unsigned char)instance->volume & in) {
                    PORTA |= in;
                }
                else {
                    PORTA &= ~in;
                }
            }
   
            
        
            
            instance->last_volume = instance->volume;
            instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
        }
    }
}

static void eeprom_save_status(volatile Instance_t* instance)
{
    if (instance->eeprom_save_status_counter != -1) {
        if (--instance->eeprom_save_status_counter == 0) {
            if (eeprom_read(EEPROM_ADR_CHANNEL) != (unsigned char)instance->channel) {
                /* store current selected channel */
                eeprom_write(EEPROM_ADR_CHANNEL, (unsigned char)instance->channel);
            }
            if (eeprom_read((unsigned char)instance->channel) != (unsigned char)instance->volume) {
                /* store current volume of channel */
                eeprom_write((unsigned char)instance->channel, (unsigned char)instance->volume);
            }

            instance->eeprom_save_status_counter = -1;
        }
    }
}

/**
 * Main application
 */
int main(void)
{
    SYSTEM_Initialize();

    init(&instance);

    /* install irq handlers */
    RC0_SetInterruptHandler(encoder_click);
    RC1_SetInterruptHandler(encoder_click);
    //RC2_SetInterruptHandler(push_button);

    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    while (1) {
        process_channel(&instance);
        process_volume(&instance);
      // eeprom_save_status(&instance);

        __delay_ms(MAIN_LOOP_WAIT);
    }
}
