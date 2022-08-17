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
  * cd ~/Documents/GitHub/electronic-projects/input-sel/software/v2b-rotary
  * cp input-sel.X/dist/default/production/input-sel.X.production.hex hex
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

#define MUTE_OFF_BIT    0x10
#define CHAN_SEL_MASK   0x0f

#define __ROTARY_CONTINUOUS__
#define ROTARY_MIN       0 /* minimum channel */
#define ROTARY_MAX       3 /* maximum channel */
#define ROTARY_MULTI     6 /* on 12PPR this gaves 3 clicks */



#define ROTARY_MIN_VOLUME       0 /* minimum channel */
#define ROTARY_MAX_VOLUME       255 /* maximum channel */
#define ROTARY_MULTI_VOLUME     2 /* on 12PPR this gaves 1 clicks */


enum Control { Volume = 0, Channel = 1, Last = 2 };

enum Direction  { Undefined = 0, Down = 1, Up = 2 };

typedef struct {

    int selected;
    int last_selected;
    int volume;
    int last_volume;



    /* irq changed */
    volatile enum Control control;
    volatile enum Direction direction;

    volatile int rotary_counter[2];
    //volatile int volume_counter;

    uint8_t encoder_value[2 /* Volume & Channel */];// = { 0, 0 };
    int encoder_count[2];// = { 0, 0 };

} Instance_t;

volatile Instance_t instance = {  .selected = -1, .last_selected = -1, .volume = -1, .last_volume = -1,
    .control = Volume, .direction = Undefined, .rotary_counter = {0,0 },
.encoder_value = {0,0 },  .encoder_count = {0,0 } };


//volatile int channel = 0;
//volatile int volume = 0;


static void init(volatile Instance_t* instance)
{
//control = { .control = Volume, .selected = 0xff, .last_selected = 0xff };

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

    /* read last used channel */
    instance->selected = eeprom_read(EEPROM_ADR_CHANNEL);

    //instance.rotary_counter[0] = instance->selected;


    instance->volume = eeprom_read((unsigned char)instance->selected);
    //instance.rotary_counter[1] = instance->volume;
}


void push_button(void)
{
    if (instance.control == Volume) {
        instance.control = Channel;
    } else {
        instance.control = Volume;
    }

    //instance.rotary_counter = 0;

    instance.encoder_value[0] = 0;
    instance.encoder_value[1] = 0;
    instance.encoder_count[0] = 0;
    instance.encoder_count[1] = 0;
}

const int8_t table[] = { 0, -1, +1, 0, +1, 0, 0, -1, -1, 0, 0, +1, 0, +1, -1, 0 };

void encoder_click(void)
{
    //static uint8_t enc_val[2] = { 0, 0 };
    //static int encoder_count[2] = { 0, 0 };





    //int tmp_channel = channel;


    /* read CHANA and CHANB, CW => up, CCW => down */
    uint8_t curr_enc_val = (uint8_t)((ENCCHANA_GetValue() << 1) | ENCCHANB_GetValue());
    instance.encoder_value[instance.control] = (uint8_t)((instance.encoder_value[instance.control] << 2) | curr_enc_val);

    /* TODO: detect direction, if changes reset the encoder_count to 0 */

    if (table[instance.encoder_value[instance.control] & 0x0f] == -1 ){

}


    instance.encoder_count[instance.control] += table[instance.encoder_value[instance.control] & 0x0f];

    if (instance.control == Volume)  {
        int value = instance.volume;


        if (instance.encoder_count[instance.control] >= ROTARY_MULTI_VOLUME) {
            value++;
            instance.encoder_count[instance.control] = 0;
        }
        else if (instance.encoder_count[instance.control] <= -ROTARY_MULTI_VOLUME) {
            value--;
            instance.encoder_count[instance.control] = 0;
        }

        if (value > ROTARY_MAX_VOLUME) {
            instance.volume = ROTARY_MAX_VOLUME;
        } else if (value < ROTARY_MIN_VOLUME) {
            instance.volume = 0;
        } else {
            instance.volume = value;
        }


    } else {
        //int tmp = instance.rotary_counter[instance.control];
    }
#if 0
    if (encoder_count >= ROTARY_MULTI) {
        tmp_channel++;
        encoder_count = 0;
    }
    else if (encoder_count <= -ROTARY_MULTI) {
        tmp_channel--;
        encoder_count = 0;
    }



#ifdef __ROTARY_CONTINUOUS__
    if (tmp_channel > ROTARY_MAX) {
        channel = 0;
    } else if (tmp_channel < ROTARY_MIN) {
        channel = ROTARY_MAX;
    } else {
        channel = tmp_channel;
    }
#else
    if (tmp_channel > ROTARY_MAX) {
        channel = ROTARY_MAX;
    } else if (tmp_channel < ROTARY_MIN) {
        channel = 0;
    } else {
        channel = tmp_channel;
    }
#endif
#endif
}

#if 0
static uint8_t get_chan_sel(void)
{
    return (uint8_t)instance.rotary_counter[0];
    //return 0;
}
#endif

void set_volume(volatile Instance_t* instance)
{

}

void set_input(volatile Instance_t* instance)
{
    /* clear and set new channel */
    PORTB &= ~CHAN_SEL_MASK;

    /* mute, read volume and apply */
    instance->volume = eeprom_read((unsigned char)instance->selected);
    instance->last_volume = instance->volume;

    if (PORTA != (unsigned char)instance->volume) {
        PORTA = (unsigned char)instance->volume;
    }

    __delay_ms(100);

    PORTB |= ((1 << instance->selected) & CHAN_SEL_MASK);

    if (instance->last_selected != -1) {
        /* store current selected channel */
        eeprom_write(EEPROM_ADR_CHANNEL, (unsigned char)instance->selected);
    }

    instance->last_selected = instance->selected;
}






/**
 * Main application
 */
int main(void)
{
    //uint8_t selected = 0xff;
    //uint8_t last_selected = 0xff;

    SYSTEM_Initialize();

    /* install irq handlers */
    RC0_SetInterruptHandler(encoder_click);
    RC1_SetInterruptHandler(encoder_click);
    RC2_SetInterruptHandler(push_button);

    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    init(&instance);
    set_input(&instance);
    //last_selected = selected;

    while (1) {
        __delay_ms(20);

        //instance.selected = get_chan_sel();

        if (instance.selected != instance.last_selected)  {
            set_input(&instance);
            /* store current selected channel */
            //eeprom_write(EEPROM_ADR_CHANNEL, control.selected);
        }

        if (instance.volume != instance.last_volume)  {
            set_volume(&instance);
        }

        #if 0
        selected = get_chan_sel();
        if (selected != last_selected) {
            set_input(selected);
            /* store current selected channel */
            eeprom_write(EEPROM_ADR_CHANNEL, selected);
            last_selected = selected;
        }
        #endif
    }
}
