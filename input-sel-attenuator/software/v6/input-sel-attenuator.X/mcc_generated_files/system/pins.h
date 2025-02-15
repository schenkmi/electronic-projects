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
? [2025] Microchip Technology Inc. and its subsidiaries.

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
#define ATT0_TRIS                 TRISAbits.TRISA0
#define ATT0_LAT                  LATAbits.LATA0
#define ATT0_PORT                 PORTAbits.RA0
#define ATT0_WPU                  WPUAbits.WPUA0
#define ATT0_OD                   ODCONAbits.ODCA0
#define ATT0_ANS                  ANSELAbits.ANSA0
#define ATT0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define ATT0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define ATT0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define ATT0_GetValue()           PORTAbits.RA0
#define ATT0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define ATT0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define ATT0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define ATT0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define ATT0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define ATT0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define ATT0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define ATT0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)
// get/set IO_RA1 aliases
#define ATT1_TRIS                 TRISAbits.TRISA1
#define ATT1_LAT                  LATAbits.LATA1
#define ATT1_PORT                 PORTAbits.RA1
#define ATT1_WPU                  WPUAbits.WPUA1
#define ATT1_OD                   ODCONAbits.ODCA1
#define ATT1_ANS                  ANSELAbits.ANSA1
#define ATT1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define ATT1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define ATT1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define ATT1_GetValue()           PORTAbits.RA1
#define ATT1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define ATT1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define ATT1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define ATT1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define ATT1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define ATT1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define ATT1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define ATT1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)
// get/set IO_RA2 aliases
#define ATT2_TRIS                 TRISAbits.TRISA2
#define ATT2_LAT                  LATAbits.LATA2
#define ATT2_PORT                 PORTAbits.RA2
#define ATT2_WPU                  WPUAbits.WPUA2
#define ATT2_OD                   ODCONAbits.ODCA2
#define ATT2_ANS                  ANSELAbits.ANSA2
#define ATT2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define ATT2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define ATT2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define ATT2_GetValue()           PORTAbits.RA2
#define ATT2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define ATT2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define ATT2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define ATT2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define ATT2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define ATT2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define ATT2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define ATT2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA3 aliases
#define ATT3_TRIS                 TRISAbits.TRISA3
#define ATT3_LAT                  LATAbits.LATA3
#define ATT3_PORT                 PORTAbits.RA3
#define ATT3_WPU                  WPUAbits.WPUA3
#define ATT3_OD                   ODCONAbits.ODCA3
#define ATT3_ANS                  ANSELAbits.ANSA3
#define ATT3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define ATT3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define ATT3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define ATT3_GetValue()           PORTAbits.RA3
#define ATT3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define ATT3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define ATT3_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define ATT3_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define ATT3_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define ATT3_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define ATT3_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define ATT3_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)
// get/set IO_RA4 aliases
#define ATT4_TRIS                 TRISAbits.TRISA4
#define ATT4_LAT                  LATAbits.LATA4
#define ATT4_PORT                 PORTAbits.RA4
#define ATT4_WPU                  WPUAbits.WPUA4
#define ATT4_OD                   ODCONAbits.ODCA4
#define ATT4_ANS                  ANSELAbits.ANSA4
#define ATT4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define ATT4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define ATT4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define ATT4_GetValue()           PORTAbits.RA4
#define ATT4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define ATT4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define ATT4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define ATT4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define ATT4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define ATT4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define ATT4_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define ATT4_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define ATT5_TRIS                 TRISAbits.TRISA5
#define ATT5_LAT                  LATAbits.LATA5
#define ATT5_PORT                 PORTAbits.RA5
#define ATT5_WPU                  WPUAbits.WPUA5
#define ATT5_OD                   ODCONAbits.ODCA5
#define ATT5_ANS                  ANSELAbits.ANSA5
#define ATT5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define ATT5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define ATT5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define ATT5_GetValue()           PORTAbits.RA5
#define ATT5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define ATT5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define ATT5_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define ATT5_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define ATT5_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define ATT5_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define ATT5_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define ATT5_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
// get/set IO_RA6 aliases
#define ATT6_TRIS                 TRISAbits.TRISA6
#define ATT6_LAT                  LATAbits.LATA6
#define ATT6_PORT                 PORTAbits.RA6
#define ATT6_WPU                  WPUAbits.WPUA6
#define ATT6_OD                   ODCONAbits.ODCA6
#define ATT6_ANS                  ANSELAbits.ANSA6
#define ATT6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define ATT6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define ATT6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define ATT6_GetValue()           PORTAbits.RA6
#define ATT6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define ATT6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define ATT6_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define ATT6_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define ATT6_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define ATT6_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define ATT6_SetAnalogMode()      do { ANSELAbits.ANSA6 = 1; } while(0)
#define ATT6_SetDigitalMode()     do { ANSELAbits.ANSA6 = 0; } while(0)
// get/set IO_RA7 aliases
#define ATT7_TRIS                 TRISAbits.TRISA7
#define ATT7_LAT                  LATAbits.LATA7
#define ATT7_PORT                 PORTAbits.RA7
#define ATT7_WPU                  WPUAbits.WPUA7
#define ATT7_OD                   ODCONAbits.ODCA7
#define ATT7_ANS                  ANSELAbits.ANSA7
#define ATT7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define ATT7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define ATT7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define ATT7_GetValue()           PORTAbits.RA7
#define ATT7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define ATT7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define ATT7_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define ATT7_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define ATT7_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define ATT7_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define ATT7_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define ATT7_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)
// get/set IO_RB0 aliases
#define INPSEL0_TRIS                 TRISBbits.TRISB0
#define INPSEL0_LAT                  LATBbits.LATB0
#define INPSEL0_PORT                 PORTBbits.RB0
#define INPSEL0_WPU                  WPUBbits.WPUB0
#define INPSEL0_OD                   ODCONBbits.ODCB0
#define INPSEL0_ANS                  ANSELBbits.ANSB0
#define INPSEL0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define INPSEL0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define INPSEL0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define INPSEL0_GetValue()           PORTBbits.RB0
#define INPSEL0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define INPSEL0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define INPSEL0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define INPSEL0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define INPSEL0_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define INPSEL0_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define INPSEL0_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define INPSEL0_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)
// get/set IO_RB1 aliases
#define INPSEL1_TRIS                 TRISBbits.TRISB1
#define INPSEL1_LAT                  LATBbits.LATB1
#define INPSEL1_PORT                 PORTBbits.RB1
#define INPSEL1_WPU                  WPUBbits.WPUB1
#define INPSEL1_OD                   ODCONBbits.ODCB1
#define INPSEL1_ANS                  ANSELBbits.ANSB1
#define INPSEL1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define INPSEL1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define INPSEL1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define INPSEL1_GetValue()           PORTBbits.RB1
#define INPSEL1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define INPSEL1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define INPSEL1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define INPSEL1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define INPSEL1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define INPSEL1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define INPSEL1_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define INPSEL1_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)
// get/set IO_RB2 aliases
#define INPSEL2_TRIS                 TRISBbits.TRISB2
#define INPSEL2_LAT                  LATBbits.LATB2
#define INPSEL2_PORT                 PORTBbits.RB2
#define INPSEL2_WPU                  WPUBbits.WPUB2
#define INPSEL2_OD                   ODCONBbits.ODCB2
#define INPSEL2_ANS                  ANSELBbits.ANSB2
#define INPSEL2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define INPSEL2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define INPSEL2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define INPSEL2_GetValue()           PORTBbits.RB2
#define INPSEL2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define INPSEL2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define INPSEL2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define INPSEL2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define INPSEL2_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define INPSEL2_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define INPSEL2_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define INPSEL2_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)
// get/set IO_RB3 aliases
#define INPSEL3_TRIS                 TRISBbits.TRISB3
#define INPSEL3_LAT                  LATBbits.LATB3
#define INPSEL3_PORT                 PORTBbits.RB3
#define INPSEL3_WPU                  WPUBbits.WPUB3
#define INPSEL3_OD                   ODCONBbits.ODCB3
#define INPSEL3_ANS                  ANSELBbits.ANSB3
#define INPSEL3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define INPSEL3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define INPSEL3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define INPSEL3_GetValue()           PORTBbits.RB3
#define INPSEL3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define INPSEL3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define INPSEL3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define INPSEL3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define INPSEL3_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define INPSEL3_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define INPSEL3_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define INPSEL3_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)
// get/set IO_RB4 aliases
#define IRIN_TRIS                 TRISBbits.TRISB4
#define IRIN_LAT                  LATBbits.LATB4
#define IRIN_PORT                 PORTBbits.RB4
#define IRIN_WPU                  WPUBbits.WPUB4
#define IRIN_OD                   ODCONBbits.ODCB4
#define IRIN_ANS                  ANSELBbits.ANSB4
#define IRIN_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IRIN_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IRIN_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IRIN_GetValue()           PORTBbits.RB4
#define IRIN_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IRIN_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IRIN_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IRIN_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IRIN_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IRIN_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IRIN_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IRIN_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)
// get/set IO_RB5 aliases
#define LED_TRIS                 TRISBbits.TRISB5
#define LED_LAT                  LATBbits.LATB5
#define LED_PORT                 PORTBbits.RB5
#define LED_WPU                  WPUBbits.WPUB5
#define LED_OD                   ODCONBbits.ODCB5
#define LED_ANS                  ANSELBbits.ANSB5
#define LED_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define LED_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define LED_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define LED_GetValue()           PORTBbits.RB5
#define LED_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define LED_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define LED_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define LED_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define LED_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define LED_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define LED_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define LED_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)
// get/set IO_RC0 aliases
#define ENC1CHANA_TRIS                 TRISCbits.TRISC0
#define ENC1CHANA_LAT                  LATCbits.LATC0
#define ENC1CHANA_PORT                 PORTCbits.RC0
#define ENC1CHANA_WPU                  WPUCbits.WPUC0
#define ENC1CHANA_OD                   ODCONCbits.ODCC0
#define ENC1CHANA_ANS                  ANSELCbits.ANSC0
#define ENC1CHANA_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define ENC1CHANA_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define ENC1CHANA_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define ENC1CHANA_GetValue()           PORTCbits.RC0
#define ENC1CHANA_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define ENC1CHANA_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define ENC1CHANA_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define ENC1CHANA_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define ENC1CHANA_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define ENC1CHANA_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define ENC1CHANA_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define ENC1CHANA_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)
// get/set IO_RC1 aliases
#define ENC1CHANB_TRIS                 TRISCbits.TRISC1
#define ENC1CHANB_LAT                  LATCbits.LATC1
#define ENC1CHANB_PORT                 PORTCbits.RC1
#define ENC1CHANB_WPU                  WPUCbits.WPUC1
#define ENC1CHANB_OD                   ODCONCbits.ODCC1
#define ENC1CHANB_ANS                  ANSELCbits.ANSC1
#define ENC1CHANB_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define ENC1CHANB_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define ENC1CHANB_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define ENC1CHANB_GetValue()           PORTCbits.RC1
#define ENC1CHANB_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define ENC1CHANB_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define ENC1CHANB_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define ENC1CHANB_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define ENC1CHANB_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define ENC1CHANB_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define ENC1CHANB_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define ENC1CHANB_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)
// get/set IO_RC2 aliases
#define ENC1SWITCH_TRIS                 TRISCbits.TRISC2
#define ENC1SWITCH_LAT                  LATCbits.LATC2
#define ENC1SWITCH_PORT                 PORTCbits.RC2
#define ENC1SWITCH_WPU                  WPUCbits.WPUC2
#define ENC1SWITCH_OD                   ODCONCbits.ODCC2
#define ENC1SWITCH_ANS                  ANSELCbits.ANSC2
#define ENC1SWITCH_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define ENC1SWITCH_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define ENC1SWITCH_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define ENC1SWITCH_GetValue()           PORTCbits.RC2
#define ENC1SWITCH_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define ENC1SWITCH_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define ENC1SWITCH_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define ENC1SWITCH_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define ENC1SWITCH_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define ENC1SWITCH_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define ENC1SWITCH_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define ENC1SWITCH_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
// get/set IO_RC5 aliases
#define ENC2CHANA_TRIS                 TRISCbits.TRISC5
#define ENC2CHANA_LAT                  LATCbits.LATC5
#define ENC2CHANA_PORT                 PORTCbits.RC5
#define ENC2CHANA_WPU                  WPUCbits.WPUC5
#define ENC2CHANA_OD                   ODCONCbits.ODCC5
#define ENC2CHANA_ANS                  ANSELCbits.ANSC5
#define ENC2CHANA_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define ENC2CHANA_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define ENC2CHANA_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define ENC2CHANA_GetValue()           PORTCbits.RC5
#define ENC2CHANA_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define ENC2CHANA_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define ENC2CHANA_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define ENC2CHANA_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define ENC2CHANA_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define ENC2CHANA_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define ENC2CHANA_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define ENC2CHANA_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)
// get/set IO_RC6 aliases
#define ENC2CHANB_TRIS                 TRISCbits.TRISC6
#define ENC2CHANB_LAT                  LATCbits.LATC6
#define ENC2CHANB_PORT                 PORTCbits.RC6
#define ENC2CHANB_WPU                  WPUCbits.WPUC6
#define ENC2CHANB_OD                   ODCONCbits.ODCC6
#define ENC2CHANB_ANS                  ANSELCbits.ANSC6
#define ENC2CHANB_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define ENC2CHANB_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define ENC2CHANB_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define ENC2CHANB_GetValue()           PORTCbits.RC6
#define ENC2CHANB_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define ENC2CHANB_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define ENC2CHANB_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define ENC2CHANB_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define ENC2CHANB_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define ENC2CHANB_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define ENC2CHANB_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define ENC2CHANB_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)
// get/set IO_RC7 aliases
#define ENC2SWITCH_TRIS                 TRISCbits.TRISC7
#define ENC2SWITCH_LAT                  LATCbits.LATC7
#define ENC2SWITCH_PORT                 PORTCbits.RC7
#define ENC2SWITCH_WPU                  WPUCbits.WPUC7
#define ENC2SWITCH_OD                   ODCONCbits.ODCC7
#define ENC2SWITCH_ANS                  ANSELCbits.ANSC7
#define ENC2SWITCH_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define ENC2SWITCH_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define ENC2SWITCH_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define ENC2SWITCH_GetValue()           PORTCbits.RC7
#define ENC2SWITCH_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define ENC2SWITCH_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define ENC2SWITCH_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define ENC2SWITCH_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define ENC2SWITCH_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define ENC2SWITCH_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define ENC2SWITCH_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define ENC2SWITCH_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)
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