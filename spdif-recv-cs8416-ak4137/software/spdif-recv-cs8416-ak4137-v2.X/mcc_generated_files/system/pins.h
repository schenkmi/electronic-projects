/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
? [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA0 aliases
#define OBIT0_TRIS                 TRISAbits.TRISA0
#define OBIT0_LAT                  LATAbits.LATA0
#define OBIT0_PORT                 PORTAbits.RA0
#define OBIT0_WPU                  WPUAbits.WPUA0
#define OBIT0_OD                   ODCONAbits.ODCA0
#define OBIT0_ANS                  ANSELAbits.ANSA0
#define OBIT0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define OBIT0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define OBIT0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define OBIT0_GetValue()           PORTAbits.RA0
#define OBIT0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define OBIT0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define OBIT0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define OBIT0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define OBIT0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define OBIT0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define OBIT0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define OBIT0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define OBIT1_TRIS                 TRISAbits.TRISA1
#define OBIT1_LAT                  LATAbits.LATA1
#define OBIT1_PORT                 PORTAbits.RA1
#define OBIT1_WPU                  WPUAbits.WPUA1
#define OBIT1_OD                   ODCONAbits.ODCA1
#define OBIT1_ANS                  ANSELAbits.ANSA1
#define OBIT1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define OBIT1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define OBIT1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define OBIT1_GetValue()           PORTAbits.RA1
#define OBIT1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define OBIT1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define OBIT1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define OBIT1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define OBIT1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define OBIT1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define OBIT1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define OBIT1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define ODIF0_TRIS                 TRISAbits.TRISA2
#define ODIF0_LAT                  LATAbits.LATA2
#define ODIF0_PORT                 PORTAbits.RA2
#define ODIF0_WPU                  WPUAbits.WPUA2
#define ODIF0_OD                   ODCONAbits.ODCA2
#define ODIF0_ANS                  ANSELAbits.ANSA2
#define ODIF0_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ODIF0_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ODIF0_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ODIF0_GetValue()           PORTAbits.RA2
#define ODIF0_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ODIF0_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ODIF0_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define ODIF0_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define ODIF0_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define ODIF0_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define ODIF0_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define ODIF0_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA3 aliases
#define ODIF1_TRIS                 TRISAbits.TRISA3
#define ODIF1_LAT                  LATAbits.LATA3
#define ODIF1_PORT                 PORTAbits.RA3
#define ODIF1_WPU                  WPUAbits.WPUA3
#define ODIF1_OD                   ODCONAbits.ODCA3
#define ODIF1_ANS                  ANSELAbits.ANSA3
#define ODIF1_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define ODIF1_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define ODIF1_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define ODIF1_GetValue()           PORTAbits.RA3
#define ODIF1_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define ODIF1_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define ODIF1_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define ODIF1_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define ODIF1_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define ODIF1_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define ODIF1_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define ODIF1_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)
// get/set IO_RA4 aliases
#define SRCEN_TRIS                 TRISAbits.TRISA4
#define SRCEN_LAT                  LATAbits.LATA4
#define SRCEN_PORT                 PORTAbits.RA4
#define SRCEN_WPU                  WPUAbits.WPUA4
#define SRCEN_OD                   ODCONAbits.ODCA4
#define SRCEN_ANS                  ANSELAbits.ANSA4
#define SRCEN_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define SRCEN_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define SRCEN_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define SRCEN_GetValue()           PORTAbits.RA4
#define SRCEN_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define SRCEN_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define SRCEN_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define SRCEN_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define SRCEN_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define SRCEN_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define SRCEN_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define SRCEN_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define LED_D3_TRIS                 TRISAbits.TRISA5
#define LED_D3_LAT                  LATAbits.LATA5
#define LED_D3_PORT                 PORTAbits.RA5
#define LED_D3_WPU                  WPUAbits.WPUA5
#define LED_D3_OD                   ODCONAbits.ODCA5
#define LED_D3_ANS                  ANSELAbits.ANSA5
#define LED_D3_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_D3_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_D3_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_D3_GetValue()           PORTAbits.RA5
#define LED_D3_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_D3_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_D3_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LED_D3_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LED_D3_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define LED_D3_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define LED_D3_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define LED_D3_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
// get/set IO_RA6 aliases
#define LED_D4_TRIS                 TRISAbits.TRISA6
#define LED_D4_LAT                  LATAbits.LATA6
#define LED_D4_PORT                 PORTAbits.RA6
#define LED_D4_WPU                  WPUAbits.WPUA6
#define LED_D4_OD                   ODCONAbits.ODCA6
#define LED_D4_ANS                  ANSELAbits.ANSA6
#define LED_D4_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define LED_D4_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define LED_D4_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define LED_D4_GetValue()           PORTAbits.RA6
#define LED_D4_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define LED_D4_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define LED_D4_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define LED_D4_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define LED_D4_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define LED_D4_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define LED_D4_SetAnalogMode()      do { ANSELAbits.ANSA6 = 1; } while(0)
#define LED_D4_SetDigitalMode()     do { ANSELAbits.ANSA6 = 0; } while(0)
// get/set IO_RA7 aliases
#define LED_D5_TRIS                 TRISAbits.TRISA7
#define LED_D5_LAT                  LATAbits.LATA7
#define LED_D5_PORT                 PORTAbits.RA7
#define LED_D5_WPU                  WPUAbits.WPUA7
#define LED_D5_OD                   ODCONAbits.ODCA7
#define LED_D5_ANS                  ANSELAbits.ANSA7
#define LED_D5_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LED_D5_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LED_D5_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LED_D5_GetValue()           PORTAbits.RA7
#define LED_D5_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LED_D5_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define LED_D5_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define LED_D5_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define LED_D5_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define LED_D5_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define LED_D5_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define LED_D5_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)
// get/set IO_RB0 aliases
#define CM0_TRIS                 TRISBbits.TRISB0
#define CM0_LAT                  LATBbits.LATB0
#define CM0_PORT                 PORTBbits.RB0
#define CM0_WPU                  WPUBbits.WPUB0
#define CM0_OD                   ODCONBbits.ODCB0
#define CM0_ANS                  ANSELBbits.ANSB0
#define CM0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define CM0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define CM0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define CM0_GetValue()           PORTBbits.RB0
#define CM0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define CM0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define CM0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define CM0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define CM0_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define CM0_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define CM0_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define CM0_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)
// get/set IO_RB1 aliases
#define CM1_TRIS                 TRISBbits.TRISB1
#define CM1_LAT                  LATBbits.LATB1
#define CM1_PORT                 PORTBbits.RB1
#define CM1_WPU                  WPUBbits.WPUB1
#define CM1_OD                   ODCONBbits.ODCB1
#define CM1_ANS                  ANSELBbits.ANSB1
#define CM1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define CM1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define CM1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define CM1_GetValue()           PORTBbits.RB1
#define CM1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define CM1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define CM1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define CM1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define CM1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define CM1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define CM1_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define CM1_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)
// get/set IO_RB2 aliases
#define CM2_TRIS                 TRISBbits.TRISB2
#define CM2_LAT                  LATBbits.LATB2
#define CM2_PORT                 PORTBbits.RB2
#define CM2_WPU                  WPUBbits.WPUB2
#define CM2_OD                   ODCONBbits.ODCB2
#define CM2_ANS                  ANSELBbits.ANSB2
#define CM2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define CM2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define CM2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define CM2_GetValue()           PORTBbits.RB2
#define CM2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define CM2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define CM2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define CM2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define CM2_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define CM2_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define CM2_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define CM2_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)
// get/set IO_RB3 aliases
#define CM3_TRIS                 TRISBbits.TRISB3
#define CM3_LAT                  LATBbits.LATB3
#define CM3_PORT                 PORTBbits.RB3
#define CM3_WPU                  WPUBbits.WPUB3
#define CM3_OD                   ODCONBbits.ODCB3
#define CM3_ANS                  ANSELBbits.ANSB3
#define CM3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define CM3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define CM3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define CM3_GetValue()           PORTBbits.RB3
#define CM3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define CM3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define CM3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define CM3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define CM3_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define CM3_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define CM3_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define CM3_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)
// get/set IO_RB4 aliases
#define DITHER_TRIS                 TRISBbits.TRISB4
#define DITHER_LAT                  LATBbits.LATB4
#define DITHER_PORT                 PORTBbits.RB4
#define DITHER_WPU                  WPUBbits.WPUB4
#define DITHER_OD                   ODCONBbits.ODCB4
#define DITHER_ANS                  ANSELBbits.ANSB4
#define DITHER_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define DITHER_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define DITHER_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define DITHER_GetValue()           PORTBbits.RB4
#define DITHER_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define DITHER_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define DITHER_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define DITHER_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define DITHER_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define DITHER_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define DITHER_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define DITHER_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)
// get/set IO_RB5 aliases
#define RESET_TRIS                 TRISBbits.TRISB5
#define RESET_LAT                  LATBbits.LATB5
#define RESET_PORT                 PORTBbits.RB5
#define RESET_WPU                  WPUBbits.WPUB5
#define RESET_OD                   ODCONBbits.ODCB5
#define RESET_ANS                  ANSELBbits.ANSB5
#define RESET_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RESET_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RESET_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RESET_GetValue()           PORTBbits.RB5
#define RESET_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RESET_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RESET_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define RESET_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define RESET_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define RESET_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define RESET_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define RESET_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)
// get/set IO_RC0 aliases
#define ENC1_CHANA_TRIS                 TRISCbits.TRISC0
#define ENC1_CHANA_LAT                  LATCbits.LATC0
#define ENC1_CHANA_PORT                 PORTCbits.RC0
#define ENC1_CHANA_WPU                  WPUCbits.WPUC0
#define ENC1_CHANA_OD                   ODCONCbits.ODCC0
#define ENC1_CHANA_ANS                  ANSELCbits.ANSC0
#define ENC1_CHANA_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define ENC1_CHANA_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define ENC1_CHANA_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define ENC1_CHANA_GetValue()           PORTCbits.RC0
#define ENC1_CHANA_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define ENC1_CHANA_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define ENC1_CHANA_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define ENC1_CHANA_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define ENC1_CHANA_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define ENC1_CHANA_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define ENC1_CHANA_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define ENC1_CHANA_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)
// get/set IO_RC1 aliases
#define ENC1_CHANB_TRIS                 TRISCbits.TRISC1
#define ENC1_CHANB_LAT                  LATCbits.LATC1
#define ENC1_CHANB_PORT                 PORTCbits.RC1
#define ENC1_CHANB_WPU                  WPUCbits.WPUC1
#define ENC1_CHANB_OD                   ODCONCbits.ODCC1
#define ENC1_CHANB_ANS                  ANSELCbits.ANSC1
#define ENC1_CHANB_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define ENC1_CHANB_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define ENC1_CHANB_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define ENC1_CHANB_GetValue()           PORTCbits.RC1
#define ENC1_CHANB_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define ENC1_CHANB_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define ENC1_CHANB_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define ENC1_CHANB_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define ENC1_CHANB_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define ENC1_CHANB_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define ENC1_CHANB_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define ENC1_CHANB_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)
// get/set IO_RC2 aliases
#define ENC1_SWITCH_TRIS                 TRISCbits.TRISC2
#define ENC1_SWITCH_LAT                  LATCbits.LATC2
#define ENC1_SWITCH_PORT                 PORTCbits.RC2
#define ENC1_SWITCH_WPU                  WPUCbits.WPUC2
#define ENC1_SWITCH_OD                   ODCONCbits.ODCC2
#define ENC1_SWITCH_ANS                  ANSELCbits.ANSC2
#define ENC1_SWITCH_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ENC1_SWITCH_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ENC1_SWITCH_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ENC1_SWITCH_GetValue()           PORTCbits.RC2
#define ENC1_SWITCH_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ENC1_SWITCH_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ENC1_SWITCH_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define ENC1_SWITCH_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define ENC1_SWITCH_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define ENC1_SWITCH_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define ENC1_SWITCH_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define ENC1_SWITCH_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
// get/set IO_RC6 aliases
#define IO_RC6_TRIS                 TRISCbits.TRISC6
#define IO_RC6_LAT                  LATCbits.LATC6
#define IO_RC6_PORT                 PORTCbits.RC6
#define IO_RC6_WPU                  WPUCbits.WPUC6
#define IO_RC6_OD                   ODCONCbits.ODCC6
#define IO_RC6_ANS                  ANSELCbits.ANSC6
#define IO_RC6_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define IO_RC6_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define IO_RC6_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define IO_RC6_GetValue()           PORTCbits.RC6
#define IO_RC6_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define IO_RC6_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define IO_RC6_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define IO_RC6_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define IO_RC6_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define IO_RC6_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define IO_RC6_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define IO_RC6_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)
// get/set IO_RC7 aliases
#define IO_RC7_TRIS                 TRISCbits.TRISC7
#define IO_RC7_LAT                  LATCbits.LATC7
#define IO_RC7_PORT                 PORTCbits.RC7
#define IO_RC7_WPU                  WPUCbits.WPUC7
#define IO_RC7_OD                   ODCONCbits.ODCC7
#define IO_RC7_ANS                  ANSELCbits.ANSC7
#define IO_RC7_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define IO_RC7_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define IO_RC7_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define IO_RC7_GetValue()           PORTCbits.RC7
#define IO_RC7_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define IO_RC7_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define IO_RC7_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define IO_RC7_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define IO_RC7_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define IO_RC7_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define IO_RC7_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define IO_RC7_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/