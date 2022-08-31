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
#define CHAN_SEL_MASK   0x0f

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
    /* mute output */
     PORTC &= ~MUTE_OFF_BIT;

    __delay_ms(100);

    /* clear and set new channel */
    PORTC &= ~CHAN_SEL_MASK;
    PORTC |= ((1 << input) & CHAN_SEL_MASK);
    
    __delay_ms(100);
    
    /* unmute outputs */
    PORTC |= MUTE_OFF_BIT;
}



//  Direction values returned by read() method 
/**
 \def DIR_NONE
  read() return value - No complete step/movement
 */
#define DIR_NONE  0x00
/**
 \def DIR_CW
 read() return value - Clockwise step/movement
 */
#define DIR_CW    0x10
/**
 \def DIR_CCW
 read() return value - Counter-clockwise step/movement
 */
#define DIR_CCW   0x20  



/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */
#define R_START 0x0

#if 0 /*ENABLE_HALF_STEP*/
// Use the half-step state table (emits a code at 00 and 11)
#define R_CCW_BEGIN   0x1
#define R_CW_BEGIN    0x2
#define R_START_M     0x3
#define R_CW_BEGIN_M  0x4
#define R_CCW_BEGIN_M 0x5

const unsigned char ttable[][4] = 
{
  // 00                  01              10            11
  {R_START_M,           R_CW_BEGIN,     R_CCW_BEGIN,  R_START},           // R_START (00)
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},           // R_CCW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},           // R_CW_BEGIN
  {R_START_M,           R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},           // R_START_M (11)
  {R_START_M,           R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},  // R_CW_BEGIN_M 
  {R_START_M,           R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW}  // R_CCW_BEGIN_M
};
#else
// Use the full-step state table (emits a code at 00 only)
#define R_CW_FINAL   0x1
#define R_CW_BEGIN   0x2
#define R_CW_NEXT    0x3
#define R_CCW_BEGIN  0x4
#define R_CCW_FINAL  0x5
#define R_CCW_NEXT   0x6

const unsigned char ttable[][4] = 
{
  // 00         01           10           11
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},           // R_START
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},  // R_CW_FINAL
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},           // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},           // R_CW_NEXT
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},           // R_CCW_BEGIN
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW}, // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START}            // R_CCW_NEXT
};
#endif

uint8_t _state = 0;     // latest state for the encoder

uint8_t encoder_read(void) 
// Grab state of input pins, determine new state from the pins 
// and state table, and return the emit bits (ie the generated event).
{
    
        /* read CHANA and CHANB, CW => up, CCW => down */
    uint8_t pinstate = (uint8_t)((ENCCHANA_GetValue() << 1) | ENCCHANB_GetValue());
    
    

  
  _state = ttable[_state & 0xf][pinstate]; 
  
#if ENABLE_SPEED
  // handle the encoder velocity calc
  if (_state & 0x30) _count++;
  if (millis() - _timeLast >= _period)
  {
    _spd = _count * (1000/_period);
    _timeLast = millis();
    _count = 0;
  }
#endif

  return (_state & 0x30);
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
    //IOCBF6_SetInterruptHandler(encoder_click);
    //IOCBF7_SetInterruptHandler(encoder_click);

    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    selected = init();

    set_input(selected);
    last_selected = selected;

    uint8_t ret;
    
    
    while (1) {
        __delay_ms(10);
        ret = encoder_read();
        if (ret == DIR_CW) {
            selected++;
            
        } else if (ret == DIR_CCW) {
            selected--;
        }
        
        if (selected < 0) {
            selected = 0;
        } else if (selected > 3) {
            selected = 0;
        }
        
        
        
        //selected = get_chan_sel();
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
