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

enum Control { Volume = 1, Channel = 0 };

volatile int channel = 0;
volatile uint8_t volume = 0xff;


static uint8_t init(void)
{
    PORTB &= ~0x0f;
    LED = 1;

    /* one channel after the others */
    for (int cnt = 0; cnt < 4; cnt++) {
        uint8_t in = ((1 << cnt) & 0xff);
        PORTB |= in;
        __delay_ms(500);
        PORTB &= ~in;
    }

    /* read last used channel */
    channel = eeprom_read(EEPROM_ADR_CHANNEL);

    return (uint8_t)channel;
}


void push_button(void)
{
    /* start always with volume control */
    static enum Control control = Volume;

    if (control == Volume) {
        control = Channel;
    } else {
        control = Volume;
    }
}

const int8_t table[] = { 0, -1, +1, 0, +1, 0, 0, -1, -1, 0, 0, +1, 0, +1, -1, 0 };

void encoder_click(void)
{
    static uint8_t enc_val = 0;
    static int encoder_count = 0;
    int tmp_channel = channel;

    /* read CHANA and CHANB, CW => up, CCW => down */
    uint8_t curr_enc_val = (uint8_t)((ENCCHANA_GetValue() << 1) | ENCCHANB_GetValue());
    enc_val = (uint8_t)((enc_val << 2) | curr_enc_val);
    encoder_count += table[enc_val & 0x0f];

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
}

static uint8_t get_chan_sel(void)
{
    return (uint8_t)channel;
}

void set_input(uint8_t input)
{
    /* clear and set new channel */
    PORTB &= ~CHAN_SEL_MASK;

    __delay_ms(100);

    PORTB |= ((1 << input) & CHAN_SEL_MASK);
}

/**
 * Main application
 */
int main(void)
{
    uint8_t selected = 0xff;
    uint8_t last_selected = 0xff;
    
    SYSTEM_Initialize();

    /* install irq handlers */
    RC0_SetInterruptHandler(encoder_click);
    RC1_SetInterruptHandler(encoder_click);
    RC2_SetInterruptHandler(push_button);

    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    selected = init();

    set_input(selected);
    last_selected = selected;

    while (1) {
        __delay_ms(20);
        selected = get_chan_sel();
        if (selected != last_selected) {
            set_input(selected);
            /* store current selected channel */
            eeprom_write(EEPROM_ADR_CHANNEL, selected);
            last_selected = selected;
        }
    }
}
