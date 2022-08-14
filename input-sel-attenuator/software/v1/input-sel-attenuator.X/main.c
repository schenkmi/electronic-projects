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


enum Control { Volume = 1, Channel = 0 };

volatile int channel = 0;

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
    
}

void encoder_click(void)
{

}

/*
    Main application
*/

int main(void)
{
    SYSTEM_Initialize();

    // If using interrupts in PIC18 High/Low Priority Mode you need to enable the Global High and Low Interrupts
    // If using interrupts in PIC Mid-Range Compatibility Mode you need to enable the Global and Peripheral Interrupts
    // Use the following macros to:

    /* install irq handlers */
    RC0_SetInterruptHandler(encoder_click);
    RC1_SetInterruptHandler(encoder_click);
    RC2_SetInterruptHandler(push_button);

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();


    while(1)
    {
    }
}
