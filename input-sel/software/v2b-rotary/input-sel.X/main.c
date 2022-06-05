/**
 * PIC16F18446 based input channel selection
 *
 * Copyright (c) 2020-2022, Michael Schenk
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

#include "mcc_generated_files/mcc.h"

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(0x00 /* channel 0 initial */, 0xff, 0xff, 0xff,
              0xff, 0xff, 0xff, 0xff);

/* EEPROM address of current channel */
#define EEPROM_ADR_CHANNEL 0x00

#define SELIN1  PORTCbits.RC0
#define SELIN2  PORTCbits.RC1
#define SELIN3  PORTCbits.RC2
#define SELIN4  PORTCbits.RC3
#define MUTEOUT PORTCbits.RC4
#define LED     PORTAbits.RA4

#define MUTE_OFF_BIT    0x10
#define CHAN_SEL_MASK   0x1f

#define __ROTARY_CONTINUOUS__
#define ROTARY_MIN       0 /* minimum channel */
#define ROTARY_MAX       3 /* maximum channel */
#define ROTARY_MULTI     6 /* on 12PPR this gaves 3 clicks */

volatile int channel = 0;

static uint8_t init(void)
{
    PORTC = 0;
    LED = 1;

    /* one channel after the others */
    for (int cnt = 0; cnt < 4; cnt++) {
        uint8_t in = ((1 << cnt) & 0xff);
        PORTC |= in;
        __delay_ms(500);
        PORTC &= ~in;
    }

    /* read last used channel */
    channel = eeprom_read(EEPROM_ADR_CHANNEL);

    return (uint8_t)channel;
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
    /* clear and mute */
    PORTC &= ~CHAN_SEL_MASK;
    __delay_ms(100);
    /* set new input */
    PORTC |= ((1 << input) & CHAN_SEL_MASK);
    __delay_ms(100);
    /* unmute outputs */
    PORTC |= MUTE_OFF_BIT;
}

/**
 * Main application
 */
void main(void)
{
    uint8_t selected = 0xff;
    uint8_t last_selected = 0xff;

    /* initialize the device */
    SYSTEM_Initialize();

    /* install irq handlers */
    IOCBF6_SetInterruptHandler(encoder_click);
    IOCBF7_SetInterruptHandler(encoder_click);

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
/**
 End of File
*/
