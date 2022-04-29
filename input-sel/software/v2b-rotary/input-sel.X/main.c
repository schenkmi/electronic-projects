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

__EEPROM_DATA(0x00 /* channel 0 initial */, 0xff, 0xff, 0xff,
              0xff, 0xff, 0xff, 0xff); // 0x00..0x07

// EEPROM address of current channel
#define EEPROM_ADR_CHANNEL 0x00

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
#   define ROTARY_MULTI     6
#endif




volatile  int encoder_count = 0;
volatile  int next_up ;
volatile  int next_down ;

volatile int channel = 0;
volatile int tmp_channel = 0;


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


//void encoder_isr() {
//    static int8_t lookup_table[] = {0,-1,1,0,1,0,0,-1,-1,0,0,1,0,1,-1,0};
//    static uint8_t enc_val = 0;
//    
//    enc_val = enc_val << 2;
//    enc_val = enc_val | ((PIND & 0b1100) >> 2)
// 
//    enc_count = enc_count + lookup_table[enc_val & 0b1111];
//}


#ifdef __ROTARY_ENCODER__
const int8_t table[] = { 0, -1, +1, 0, +1, 0, 0, -1, -1, 0, 0, +1, 0, +1, -1, 0 };

void encoder_click(void)
{
    //static unsigned char previous = 0;
    
    static uint8_t enc_val = 0;
    
    //uint8_t tmp = 5;

    //while(tmp--) { /* debounce */ ; }
 
    /* read CHANA and CHANB */
    uint8_t tmp = (uint8_t)((RCHANB_GetValue() << 1) | RCHANA_GetValue());

    
        enc_val = (uint8_t)(enc_val << 2);
    enc_val = enc_val | (tmp);
 
    encoder_count = encoder_count + table[enc_val & 0x0f];
    
    
    //previous <<= 2;     /* shift the previous data left two places */ 
    //previous |= tmp;    /* OR in the two new bits */

   // encoder_count += table[(previous & 0x0f)];  /* Index into table */

    
    if (encoder_count >= next_up) {
     tmp_channel++;
     encoder_count = 0;
     //next_up = encoder_count + ROTARY_MULTI;
     //next_down = encoder_count - ROTARY_MULTI;
     
    }
    else if (encoder_count <= next_down) {
     tmp_channel--;   
     encoder_count = 0;
    }
    
    


#ifdef __ROTARY_CONTINUOUS__
    if (tmp_channel > ROTARY_MAX) {
        tmp_channel = channel = 0;
    } else if (tmp_channel < ROTARY_MIN) {
        tmp_channel = channel = ROTARY_MAX;
    } else {
        channel = tmp_channel;
    }
#else
    if (tmp_channel > ROTARY_MAX) {
        tmp_channel = channel = ROTARY_MAX;
    } else if (tmp_channel < ROTARY_MIN) {
        tmp_channel = channel = 0;
    } else {
        channel = tmp_channel;
    }
    
#endif
    

}
#endif

static uint8_t get_chan_sel(void)
{
    uint8_t ret = 0xff;
    
#ifdef __ROTARY_ENCODER__
    ret = (uint8_t)channel;
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


void set_input(uint8_t input)
{
    PORTC = (((1 << input) & 0xff) | MUTE_OFF_BIT);           
}

/*
                         Main application
 */
void main(void)
{
    uint8_t selected = 0xff;
    uint8_t last_selected = 0xff;
    
    // initialize the device
    SYSTEM_Initialize();
    
    
    encoder_count = 0;
    next_up = encoder_count + ROTARY_MULTI;
    next_down = encoder_count - ROTARY_MULTI;
    
        // read last used channel
  //  selected = eeprom_read(EEPROM_ADR_CHANNEL);
channel = tmp_channel = selected = eeprom_read(EEPROM_ADR_CHANNEL);
    



    
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
    

    
    set_input(selected);
    last_selected = selected;
    
    
    while (1) {
        __delay_ms(20);
        selected = get_chan_sel();
        if (selected == 0xff) {
            continue;
        }
        
        if (selected != last_selected) {
            set_input(selected);
            // store current selected channel
            eeprom_write(EEPROM_ADR_CHANNEL, selected);
            last_selected = selected;
        }
    }
}
/**
 End of File
*/