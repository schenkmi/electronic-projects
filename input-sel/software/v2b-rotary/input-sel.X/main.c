/**
 * PIC16F18446 based input channel selection
 *
 * Copyright (c) 2020, Michael Schenk
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
 * commercially licensed software with Albis Technologies software
 * and do not wish to distribute the source code for the commercially
 * licensed software under version 2, or (at your option) any later
 * version, of the GNU General Public License (the "GPL") must enter
 * into a commercial license agreement with Albis Technologies Ldt.
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

#include "mcc_generated_files/mcc.h"

#define SELIN1 PORTCbits.RC0
#define SELIN2 PORTCbits.RC1
#define SELIN3 PORTCbits.RC2
#define SELIN4 PORTCbits.RC3
#define MUTEOUT PORTCbits.RC4

#define MUTE_OFF_BIT    0x10

#define LED PORTAbits.RA4


#define __ROTARY_ENCODER__
#ifdef __ROTARY_ENCODER__
#   define __ROTARY_CONTINUOUS__
#   define ROTARY_MIN       0
#   define ROTARY_MAX       3
#   define ROTARY_MULTI     2
#endif

volatile signed int encoder_count;

#if 0
static void eeprom_example(void)
{
    volatile uint8_t value = 0x09;
    uint8_t address = 0xE5;
    eeprom_write(address, value);     // Writing value 0x9 to EEPROM address 0xE5        
    value = eeprom_read (address);    // Reading the value from address 0xE5
}
#endif

static int get_chan_sel(void)
{
    int ret = -1;
    
#ifdef __ROTARY_ENCODER__
    

    if (encoder_count >= 0) {
    ret = encoder_count / ROTARY_MULTI;
    }
#else
    /**
     * PORTB weak pull-up RB7..RB4
     * Input selector ties to GND so we invert the bits here
     */
    uint8_t input = (~(PORTB >> 4)) & 0x0f;
    
    switch (input) {
        case 0x01: /* INPUT 1, RB4 tie to GND */
            ret = 0;
            break;
        case 0x02: /* INPUT 2, RB5 tie to GND */
            ret = 1;
            break;
        case 0x04: /* INPUT 3, RB6 tie to GND */
            ret = 2;
            break;
        case 0x08: /* INPUT 4, RB7 tie to GND */
            ret = 3;
            break;
        default:
            break;
    }
#endif
    return ret;
}

void init(void)
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
}

#ifdef __ROTARY_ENCODER__
const signed char table[] = { 0, -1, +1, 0, +1, 0, 0, -1, -1, 0, 0, +1, 0, +1, -1, 0 };

void encoder_click(void)
{
    static unsigned char previous = 0;
    uint8_t tmp = 5;

    while(tmp--) { /* debounce */ ; }
 
    /* read CHANA and CHANB */
    tmp = (uint8_t)((RCHANB_GetValue() << 1) | RCHANA_GetValue());

    previous <<= 2;     /* shift the previous data left two places */ 
    previous |= tmp;    /* OR in the two new bits */

    encoder_count += table[(previous & 0x0f)];  /* Index into table */
  
#ifdef __ROTARY_CONTINUOUS__
  if (encoder_count >= ((ROTARY_MAX + 1) * ROTARY_MULTI)) {
    encoder_count = (ROTARY_MIN * ROTARY_MULTI); 
  }
  else if (encoder_count <= ((ROTARY_MIN - 1) * ROTARY_MULTI)) {
     encoder_count = (ROTARY_MAX * ROTARY_MULTI); 
  }
#else
  if (encoder_count > (ROTARY_MAX * ROTARY_MULTI)) {
    encoder_count = (ROTARY_MAX * ROTARY_MULTI); 
  }
  else if (encoder_count < (ROTARY_MIN * ROTARY_MULTI)) {
     encoder_count = (ROTARY_MIN * ROTARY_MULTI); 
  }
#endif
}
#endif

/*
                         Main application
 */
void main(void)
{
    int selected = -1;
    int last_selected = -1;
    
    // initialize the device
    SYSTEM_Initialize();
    
    encoder_count = 0;
    
#ifdef __ROTARY_ENCODER__
    IOCBF6_SetInterruptHandler(encoder_click);
    IOCBF7_SetInterruptHandler(encoder_click);
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
#else
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
#endif
    
    init();
    
    while (1) {
        __delay_ms(20);
        selected = get_chan_sel();
        if (selected == -1) {
            continue;
        }
        
        if (selected != last_selected) {
            PORTC &= ~((1 << last_selected) & 0xff);
            PORTC |= (((1 << selected) & 0xff) | MUTE_OFF_BIT);
            last_selected = selected;
        }
    }
}
/**
 End of File
*/