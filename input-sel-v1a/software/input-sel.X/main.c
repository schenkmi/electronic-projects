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

static uint8_t get_chan_sel(void)
{
    uint8_t input = (~(PORTB >> 4)) & 0x0f;
    
    switch (input) {
        case 0x01:
            input = 1;
            break;
        case 0x02:
            input = 2;
            break;
        case 0x04:
            input = 3;
            break;
        case 0x08:
            input = 4;
            break;
        default:
            input = 1;
            break;
    }
    
    return input;
}

void init(void)
{
    for (int cnt = 0; cnt < 20; cnt++) {
        __delay_ms(500);
    }
    
    PORTC = 0;
    
    for (int cnt = 0; cnt < 4; cnt++) {
        uint8_t in = ((1 << cnt) & 0xff);
        
        PORTC |= in;
        __delay_ms(1000);
        PORTC &= ~in;
    }
    

}




/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

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
    
    init();
    
    uint8_t selected = get_chan_sel();
    
    if (selected == 0) {
        selected = 1;
    }
   
    uint8_t last_selected = selected;
    
    PORTC |= (((1 << selected) & 0xff) | 0x10);
     
    
        /* unmute output */
    MUTEOUT = 1;

    while (1) {
        
        __delay_ms(100);
        
        
        
        selected = get_chan_sel();
        if (selected != last_selected) {
            PORTC &= ~((1 << last_selected) & 0xff);
            PORTC |= (((1 << selected) & 0xff) | 0x10);
            last_selected = selected;
        }
        

    }
}
/**
 End of File
*/