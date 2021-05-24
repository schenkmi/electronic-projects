/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.6
        Device            :  PIC16F18446
        Driver Version    :  2.00
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#include "mcc_generated_files/mcc.h"

#define SELIN1 PORTCbits.RC0
#define SELIN2 PORTCbits.RC1
#define SELIN3 PORTCbits.RC2
#define SELIN4 PORTCbits.RC3
#define MUTEOUT PORTCbits.RC4

#define MUTE_OFF_BIT    0x10

#define LED PORTAbits.RA4

volatile signed int encoder_count;


static void eeprom_example(void)
{
    volatile uint8_t value = 0x09;
    uint8_t address = 0xE5;
    eeprom_write(address, value);     // Writing value 0x9 to EEPROM address 0xE5        
    value = eeprom_read (address);    // Reading the value from address 0xE5
}

static int get_chan_sel(void)
{
    int ret = -1;
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

#if 0
const signed char table[] = {0,-1,+1,0,+1,0,0,-1,-1,0,0,+1,0,+1,-1,0};
#else
const signed char table[] = {0,0,0,0,0,0,0,-1,0,0,0,+1,0,0,0,0};
#endif


// 1011 => + 1
// 0111 => - 1

void encoder_click(void)
  {
#if 0
    static unsigned char previous = 0;
  uint8_t tmp;

  tmp = 5;

  while(tmp--){ /* debounce */
    ;
    }

  

  tmp = (uint8_t)((RCHANB_GetValue() << 1) | RCHANA_GetValue());
   
  
  previous <<= 2;   /* shift the previous data left two places */ 
  previous |= tmp; /* OR in the two new bits */

  encoder_count += table[(previous & 0x0f)];  /* Index into table */
  
  if (encoder_count > 3) {
    //encoder_count = 0; 
    encoder_count = 3; 
  }
  else if (encoder_count < 0) {
     //encoder_count = 3; 
     encoder_count = 0; 
  }
  
#else
     static unsigned char previous = 0;
  uint8_t tmp;

  tmp = 5;

  while(tmp--){ /* debounce */
    ;
    }

  


  tmp = (uint8_t)((RCHANB_GetValue() << 1) | RCHANA_GetValue());
    previous <<= 2;   /* shift the previous data left two places */ 
  previous |= tmp; /* OR in the two new bits */
  
  encoder_count += table[(previous & 0x0f)];  /* Index into table */
  
#if 0
  if (tmp == 0x2) {
      encoder_count++;
  }
  else if (tmp == 0x1) {
      
      encoder_count--;
  }
#endif

  if (encoder_count > 3) {
    //encoder_count = 0; 
    encoder_count = 3; 
  }
  else if (encoder_count < 0) {
     //encoder_count = 3; 
     encoder_count = 0; 
  }
  
  
  
#endif
  }


/*
                         Main application
 */
void main(void)
{
    int selected = -1;
    int last_selected = -1; 
    int last_encoder_count = -1;
    // initialize the device
    SYSTEM_Initialize();

    encoder_count = 0;
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
    
    init();
    
    while (1) {
        
#if 1
        __delay_ms(20);
        if (encoder_count != last_encoder_count) {
            PORTC &= ~((1 << last_encoder_count) & 0xff);
            PORTC |= (((1 << encoder_count) & 0xff) | MUTE_OFF_BIT);
            last_encoder_count = encoder_count;
        }   
#else
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
#endif
    }
}
/**
 End of File
*/