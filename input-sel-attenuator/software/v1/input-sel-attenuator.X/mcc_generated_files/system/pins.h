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
© [2022] Microchip Technology Inc. and its subsidiaries.

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
#define IO_ATT0_TRIS                 TRISAbits.TRISA0
#define IO_ATT0_LAT                  LATAbits.LATA0
#define IO_ATT0_PORT                 PORTAbits.RA0
#define IO_ATT0_WPU                  WPUAbits.WPUA0
#define IO_ATT0_OD                   ODCONAbits.ODCA0
#define IO_ATT0_ANS                  ANSELAbits.ANSA0
#define IO_ATT0_SetHigh()            do { LATAbits.LATA0 = 1; } while(0)
#define IO_ATT0_SetLow()             do { LATAbits.LATA0 = 0; } while(0)
#define IO_ATT0_Toggle()             do { LATAbits.LATA0 = ~LATAbits.LATA0; } while(0)
#define IO_ATT0_GetValue()           PORTAbits.RA0
#define IO_ATT0_SetDigitalInput()    do { TRISAbits.TRISA0 = 1; } while(0)
#define IO_ATT0_SetDigitalOutput()   do { TRISAbits.TRISA0 = 0; } while(0)
#define IO_ATT0_SetPullup()          do { WPUAbits.WPUA0 = 1; } while(0)
#define IO_ATT0_ResetPullup()        do { WPUAbits.WPUA0 = 0; } while(0)
#define IO_ATT0_SetPushPull()        do { ODCONAbits.ODCA0 = 0; } while(0)
#define IO_ATT0_SetOpenDrain()       do { ODCONAbits.ODCA0 = 1; } while(0)
#define IO_ATT0_SetAnalogMode()      do { ANSELAbits.ANSA0 = 1; } while(0)
#define IO_ATT0_SetDigitalMode()     do { ANSELAbits.ANSA0 = 0; } while(0)

// get/set IO_RA1 aliases
#define IO_ATT1_TRIS                 TRISAbits.TRISA1
#define IO_ATT1_LAT                  LATAbits.LATA1
#define IO_ATT1_PORT                 PORTAbits.RA1
#define IO_ATT1_WPU                  WPUAbits.WPUA1
#define IO_ATT1_OD                   ODCONAbits.ODCA1
#define IO_ATT1_ANS                  ANSELAbits.ANSA1
#define IO_ATT1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define IO_ATT1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define IO_ATT1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define IO_ATT1_GetValue()           PORTAbits.RA1
#define IO_ATT1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define IO_ATT1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define IO_ATT1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define IO_ATT1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define IO_ATT1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define IO_ATT1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define IO_ATT1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define IO_ATT1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set IO_RA2 aliases
#define IO_ATT2_TRIS                 TRISAbits.TRISA2
#define IO_ATT2_LAT                  LATAbits.LATA2
#define IO_ATT2_PORT                 PORTAbits.RA2
#define IO_ATT2_WPU                  WPUAbits.WPUA2
#define IO_ATT2_OD                   ODCONAbits.ODCA2
#define IO_ATT2_ANS                  ANSELAbits.ANSA2
#define IO_ATT2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define IO_ATT2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define IO_ATT2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define IO_ATT2_GetValue()           PORTAbits.RA2
#define IO_ATT2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define IO_ATT2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define IO_ATT2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define IO_ATT2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define IO_ATT2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define IO_ATT2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define IO_ATT2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define IO_ATT2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_RA3 aliases
#define IO_ATT3_TRIS                 TRISAbits.TRISA3
#define IO_ATT3_LAT                  LATAbits.LATA3
#define IO_ATT3_PORT                 PORTAbits.RA3
#define IO_ATT3_WPU                  WPUAbits.WPUA3
#define IO_ATT3_OD                   ODCONAbits.ODCA3
#define IO_ATT3_ANS                  ANSELAbits.ANSA3
#define IO_ATT3_SetHigh()            do { LATAbits.LATA3 = 1; } while(0)
#define IO_ATT3_SetLow()             do { LATAbits.LATA3 = 0; } while(0)
#define IO_ATT3_Toggle()             do { LATAbits.LATA3 = ~LATAbits.LATA3; } while(0)
#define IO_ATT3_GetValue()           PORTAbits.RA3
#define IO_ATT3_SetDigitalInput()    do { TRISAbits.TRISA3 = 1; } while(0)
#define IO_ATT3_SetDigitalOutput()   do { TRISAbits.TRISA3 = 0; } while(0)
#define IO_ATT3_SetPullup()          do { WPUAbits.WPUA3 = 1; } while(0)
#define IO_ATT3_ResetPullup()        do { WPUAbits.WPUA3 = 0; } while(0)
#define IO_ATT3_SetPushPull()        do { ODCONAbits.ODCA3 = 0; } while(0)
#define IO_ATT3_SetOpenDrain()       do { ODCONAbits.ODCA3 = 1; } while(0)
#define IO_ATT3_SetAnalogMode()      do { ANSELAbits.ANSA3 = 1; } while(0)
#define IO_ATT3_SetDigitalMode()     do { ANSELAbits.ANSA3 = 0; } while(0)

// get/set IO_RA4 aliases
#define IO_ATT4_TRIS                 TRISAbits.TRISA4
#define IO_ATT4_LAT                  LATAbits.LATA4
#define IO_ATT4_PORT                 PORTAbits.RA4
#define IO_ATT4_WPU                  WPUAbits.WPUA4
#define IO_ATT4_OD                   ODCONAbits.ODCA4
#define IO_ATT4_ANS                  ANSELAbits.ANSA4
#define IO_ATT4_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define IO_ATT4_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define IO_ATT4_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define IO_ATT4_GetValue()           PORTAbits.RA4
#define IO_ATT4_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define IO_ATT4_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define IO_ATT4_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define IO_ATT4_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define IO_ATT4_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define IO_ATT4_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define IO_ATT4_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define IO_ATT4_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)

// get/set IO_RA5 aliases
#define IO_ATT5_TRIS                 TRISAbits.TRISA5
#define IO_ATT5_LAT                  LATAbits.LATA5
#define IO_ATT5_PORT                 PORTAbits.RA5
#define IO_ATT5_WPU                  WPUAbits.WPUA5
#define IO_ATT5_OD                   ODCONAbits.ODCA5
#define IO_ATT5_ANS                  ANSELAbits.ANSA5
#define IO_ATT5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define IO_ATT5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define IO_ATT5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define IO_ATT5_GetValue()           PORTAbits.RA5
#define IO_ATT5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define IO_ATT5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define IO_ATT5_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define IO_ATT5_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define IO_ATT5_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define IO_ATT5_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define IO_ATT5_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define IO_ATT5_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)

// get/set IO_RA6 aliases
#define IO_ATT6_TRIS                 TRISAbits.TRISA6
#define IO_ATT6_LAT                  LATAbits.LATA6
#define IO_ATT6_PORT                 PORTAbits.RA6
#define IO_ATT6_WPU                  WPUAbits.WPUA6
#define IO_ATT6_OD                   ODCONAbits.ODCA6
#define IO_ATT6_ANS                  ANSELAbits.ANSA6
#define IO_ATT6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define IO_ATT6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define IO_ATT6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define IO_ATT6_GetValue()           PORTAbits.RA6
#define IO_ATT6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define IO_ATT6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define IO_ATT6_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define IO_ATT6_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define IO_ATT6_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define IO_ATT6_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define IO_ATT6_SetAnalogMode()      do { ANSELAbits.ANSA6 = 1; } while(0)
#define IO_ATT6_SetDigitalMode()     do { ANSELAbits.ANSA6 = 0; } while(0)

// get/set IO_RA7 aliases
#define IO_ATT7_TRIS                 TRISAbits.TRISA7
#define IO_ATT7_LAT                  LATAbits.LATA7
#define IO_ATT7_PORT                 PORTAbits.RA7
#define IO_ATT7_WPU                  WPUAbits.WPUA7
#define IO_ATT7_OD                   ODCONAbits.ODCA7
#define IO_ATT7_ANS                  ANSELAbits.ANSA7
#define IO_ATT7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define IO_ATT7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define IO_ATT7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define IO_ATT7_GetValue()           PORTAbits.RA7
#define IO_ATT7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define IO_ATT7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define IO_ATT7_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define IO_ATT7_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define IO_ATT7_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define IO_ATT7_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define IO_ATT7_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define IO_ATT7_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)

// get/set IO_RB0 aliases
#define IO_INPSEL0_TRIS                 TRISBbits.TRISB0
#define IO_INPSEL0_LAT                  LATBbits.LATB0
#define IO_INPSEL0_PORT                 PORTBbits.RB0
#define IO_INPSEL0_WPU                  WPUBbits.WPUB0
#define IO_INPSEL0_OD                   ODCONBbits.ODCB0
#define IO_INPSEL0_ANS                  ANSELBbits.ANSB0
#define IO_INPSEL0_SetHigh()            do { LATBbits.LATB0 = 1; } while(0)
#define IO_INPSEL0_SetLow()             do { LATBbits.LATB0 = 0; } while(0)
#define IO_INPSEL0_Toggle()             do { LATBbits.LATB0 = ~LATBbits.LATB0; } while(0)
#define IO_INPSEL0_GetValue()           PORTBbits.RB0
#define IO_INPSEL0_SetDigitalInput()    do { TRISBbits.TRISB0 = 1; } while(0)
#define IO_INPSEL0_SetDigitalOutput()   do { TRISBbits.TRISB0 = 0; } while(0)
#define IO_INPSEL0_SetPullup()          do { WPUBbits.WPUB0 = 1; } while(0)
#define IO_INPSEL0_ResetPullup()        do { WPUBbits.WPUB0 = 0; } while(0)
#define IO_INPSEL0_SetPushPull()        do { ODCONBbits.ODCB0 = 0; } while(0)
#define IO_INPSEL0_SetOpenDrain()       do { ODCONBbits.ODCB0 = 1; } while(0)
#define IO_INPSEL0_SetAnalogMode()      do { ANSELBbits.ANSB0 = 1; } while(0)
#define IO_INPSEL0_SetDigitalMode()     do { ANSELBbits.ANSB0 = 0; } while(0)

// get/set IO_RB1 aliases
#define IO_INPSEL1_TRIS                 TRISBbits.TRISB1
#define IO_INPSEL1_LAT                  LATBbits.LATB1
#define IO_INPSEL1_PORT                 PORTBbits.RB1
#define IO_INPSEL1_WPU                  WPUBbits.WPUB1
#define IO_INPSEL1_OD                   ODCONBbits.ODCB1
#define IO_INPSEL1_ANS                  ANSELBbits.ANSB1
#define IO_INPSEL1_SetHigh()            do { LATBbits.LATB1 = 1; } while(0)
#define IO_INPSEL1_SetLow()             do { LATBbits.LATB1 = 0; } while(0)
#define IO_INPSEL1_Toggle()             do { LATBbits.LATB1 = ~LATBbits.LATB1; } while(0)
#define IO_INPSEL1_GetValue()           PORTBbits.RB1
#define IO_INPSEL1_SetDigitalInput()    do { TRISBbits.TRISB1 = 1; } while(0)
#define IO_INPSEL1_SetDigitalOutput()   do { TRISBbits.TRISB1 = 0; } while(0)
#define IO_INPSEL1_SetPullup()          do { WPUBbits.WPUB1 = 1; } while(0)
#define IO_INPSEL1_ResetPullup()        do { WPUBbits.WPUB1 = 0; } while(0)
#define IO_INPSEL1_SetPushPull()        do { ODCONBbits.ODCB1 = 0; } while(0)
#define IO_INPSEL1_SetOpenDrain()       do { ODCONBbits.ODCB1 = 1; } while(0)
#define IO_INPSEL1_SetAnalogMode()      do { ANSELBbits.ANSB1 = 1; } while(0)
#define IO_INPSEL1_SetDigitalMode()     do { ANSELBbits.ANSB1 = 0; } while(0)

// get/set IO_RB2 aliases
#define IO_INPSEL2_TRIS                 TRISBbits.TRISB2
#define IO_INPSEL2_LAT                  LATBbits.LATB2
#define IO_INPSEL2_PORT                 PORTBbits.RB2
#define IO_INPSEL2_WPU                  WPUBbits.WPUB2
#define IO_INPSEL2_OD                   ODCONBbits.ODCB2
#define IO_INPSEL2_ANS                  ANSELBbits.ANSB2
#define IO_INPSEL2_SetHigh()            do { LATBbits.LATB2 = 1; } while(0)
#define IO_INPSEL2_SetLow()             do { LATBbits.LATB2 = 0; } while(0)
#define IO_INPSEL2_Toggle()             do { LATBbits.LATB2 = ~LATBbits.LATB2; } while(0)
#define IO_INPSEL2_GetValue()           PORTBbits.RB2
#define IO_INPSEL2_SetDigitalInput()    do { TRISBbits.TRISB2 = 1; } while(0)
#define IO_INPSEL2_SetDigitalOutput()   do { TRISBbits.TRISB2 = 0; } while(0)
#define IO_INPSEL2_SetPullup()          do { WPUBbits.WPUB2 = 1; } while(0)
#define IO_INPSEL2_ResetPullup()        do { WPUBbits.WPUB2 = 0; } while(0)
#define IO_INPSEL2_SetPushPull()        do { ODCONBbits.ODCB2 = 0; } while(0)
#define IO_INPSEL2_SetOpenDrain()       do { ODCONBbits.ODCB2 = 1; } while(0)
#define IO_INPSEL2_SetAnalogMode()      do { ANSELBbits.ANSB2 = 1; } while(0)
#define IO_INPSEL2_SetDigitalMode()     do { ANSELBbits.ANSB2 = 0; } while(0)

// get/set IO_RB3 aliases
#define IO_INPSEL3_TRIS                 TRISBbits.TRISB3
#define IO_INPSEL3_LAT                  LATBbits.LATB3
#define IO_INPSEL3_PORT                 PORTBbits.RB3
#define IO_INPSEL3_WPU                  WPUBbits.WPUB3
#define IO_INPSEL3_OD                   ODCONBbits.ODCB3
#define IO_INPSEL3_ANS                  ANSELBbits.ANSB3
#define IO_INPSEL3_SetHigh()            do { LATBbits.LATB3 = 1; } while(0)
#define IO_INPSEL3_SetLow()             do { LATBbits.LATB3 = 0; } while(0)
#define IO_INPSEL3_Toggle()             do { LATBbits.LATB3 = ~LATBbits.LATB3; } while(0)
#define IO_INPSEL3_GetValue()           PORTBbits.RB3
#define IO_INPSEL3_SetDigitalInput()    do { TRISBbits.TRISB3 = 1; } while(0)
#define IO_INPSEL3_SetDigitalOutput()   do { TRISBbits.TRISB3 = 0; } while(0)
#define IO_INPSEL3_SetPullup()          do { WPUBbits.WPUB3 = 1; } while(0)
#define IO_INPSEL3_ResetPullup()        do { WPUBbits.WPUB3 = 0; } while(0)
#define IO_INPSEL3_SetPushPull()        do { ODCONBbits.ODCB3 = 0; } while(0)
#define IO_INPSEL3_SetOpenDrain()       do { ODCONBbits.ODCB3 = 1; } while(0)
#define IO_INPSEL3_SetAnalogMode()      do { ANSELBbits.ANSB3 = 1; } while(0)
#define IO_INPSEL3_SetDigitalMode()     do { ANSELBbits.ANSB3 = 0; } while(0)

// get/set IO_RB4 aliases
#define IO_MUTE_TRIS                 TRISBbits.TRISB4
#define IO_MUTE_LAT                  LATBbits.LATB4
#define IO_MUTE_PORT                 PORTBbits.RB4
#define IO_MUTE_WPU                  WPUBbits.WPUB4
#define IO_MUTE_OD                   ODCONBbits.ODCB4
#define IO_MUTE_ANS                  ANSELBbits.ANSB4
#define IO_MUTE_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define IO_MUTE_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define IO_MUTE_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define IO_MUTE_GetValue()           PORTBbits.RB4
#define IO_MUTE_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define IO_MUTE_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define IO_MUTE_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define IO_MUTE_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define IO_MUTE_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define IO_MUTE_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define IO_MUTE_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define IO_MUTE_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set IO_RC0 aliases
#define IO_ENCCHANA_TRIS                 TRISCbits.TRISC0
#define IO_ENCCHANA_LAT                  LATCbits.LATC0
#define IO_ENCCHANA_PORT                 PORTCbits.RC0
#define IO_ENCCHANA_WPU                  WPUCbits.WPUC0
#define IO_ENCCHANA_OD                   ODCONCbits.ODCC0
#define IO_ENCCHANA_ANS                  ANSELCbits.ANSC0
#define IO_ENCCHANA_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define IO_ENCCHANA_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define IO_ENCCHANA_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define IO_ENCCHANA_GetValue()           PORTCbits.RC0
#define IO_ENCCHANA_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define IO_ENCCHANA_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define IO_ENCCHANA_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define IO_ENCCHANA_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define IO_ENCCHANA_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define IO_ENCCHANA_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define IO_ENCCHANA_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define IO_ENCCHANA_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set IO_RC1 aliases
#define IO_ENCCHANB_TRIS                 TRISCbits.TRISC1
#define IO_ENCCHANB_LAT                  LATCbits.LATC1
#define IO_ENCCHANB_PORT                 PORTCbits.RC1
#define IO_ENCCHANB_WPU                  WPUCbits.WPUC1
#define IO_ENCCHANB_OD                   ODCONCbits.ODCC1
#define IO_ENCCHANB_ANS                  ANSELCbits.ANSC1
#define IO_ENCCHANB_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define IO_ENCCHANB_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define IO_ENCCHANB_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define IO_ENCCHANB_GetValue()           PORTCbits.RC1
#define IO_ENCCHANB_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define IO_ENCCHANB_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define IO_ENCCHANB_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define IO_ENCCHANB_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define IO_ENCCHANB_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define IO_ENCCHANB_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define IO_ENCCHANB_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define IO_ENCCHANB_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set IO_RC2 aliases
#define IO_ENCPUSH_TRIS                 TRISCbits.TRISC2
#define IO_ENCPUSH_LAT                  LATCbits.LATC2
#define IO_ENCPUSH_PORT                 PORTCbits.RC2
#define IO_ENCPUSH_WPU                  WPUCbits.WPUC2
#define IO_ENCPUSH_OD                   ODCONCbits.ODCC2
#define IO_ENCPUSH_ANS                  ANSELCbits.ANSC2
#define IO_ENCPUSH_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define IO_ENCPUSH_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define IO_ENCPUSH_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define IO_ENCPUSH_GetValue()           PORTCbits.RC2
#define IO_ENCPUSH_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define IO_ENCPUSH_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define IO_ENCPUSH_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define IO_ENCPUSH_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define IO_ENCPUSH_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define IO_ENCPUSH_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define IO_ENCPUSH_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define IO_ENCPUSH_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set IO_RC3 aliases
#define IO_SCL1_TRIS                 TRISCbits.TRISC3
#define IO_SCL1_LAT                  LATCbits.LATC3
#define IO_SCL1_PORT                 PORTCbits.RC3
#define IO_SCL1_WPU                  WPUCbits.WPUC3
#define IO_SCL1_OD                   ODCONCbits.ODCC3
#define IO_SCL1_ANS                  ANSELCbits.ANSC3
#define IO_SCL1_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define IO_SCL1_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define IO_SCL1_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define IO_SCL1_GetValue()           PORTCbits.RC3
#define IO_SCL1_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define IO_SCL1_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define IO_SCL1_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define IO_SCL1_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define IO_SCL1_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define IO_SCL1_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define IO_SCL1_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define IO_SCL1_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set IO_RC4 aliases
#define IO_SCA1_TRIS                 TRISCbits.TRISC4
#define IO_SCA1_LAT                  LATCbits.LATC4
#define IO_SCA1_PORT                 PORTCbits.RC4
#define IO_SCA1_WPU                  WPUCbits.WPUC4
#define IO_SCA1_OD                   ODCONCbits.ODCC4
#define IO_SCA1_ANS                  ANSELCbits.ANSC4
#define IO_SCA1_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define IO_SCA1_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define IO_SCA1_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define IO_SCA1_GetValue()           PORTCbits.RC4
#define IO_SCA1_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define IO_SCA1_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define IO_SCA1_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define IO_SCA1_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define IO_SCA1_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define IO_SCA1_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define IO_SCA1_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define IO_SCA1_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

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

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the RC0 pin functionality
 * @param none
 * @return none
 */
void RC0_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for RC0 pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for RC0 at application runtime.
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void RC0_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for RC0 pin.
 *        This is a dynamic interrupt handler to be used together with the RC0_SetInterruptHandler() method.
 *        This handler is called every time the RC0 ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*RC0_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for RC0 pin. 
 *        This is a predefined interrupt handler to be used together with the RC0_SetInterruptHandler() method.
 *        This handler is called every time the RC0 ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void RC0_DefaultInterruptHandler(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handler for the RC1 pin functionality
 * @param none
 * @return none
 */
void RC1_ISR(void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt Handler Setter for RC1 pin interrupt-on-change functionality.
 *        Allows selecting an interrupt handler for RC1 at application runtime.
 * @pre Pins intializer called
 * @param InterruptHandler function pointer.
 * @return none
 */
void RC1_SetInterruptHandler(void (* InterruptHandler)(void));

/**
 * @ingroup  pinsdriver
 * @brief Dynamic Interrupt Handler for RC1 pin.
 *        This is a dynamic interrupt handler to be used together with the RC1_SetInterruptHandler() method.
 *        This handler is called every time the RC1 ISR is executed and allows any function to be registered at runtime.
 * @pre Pins intializer called
 * @param none
 * @return none
 */
extern void (*RC1_InterruptHandler)(void);

/**
 * @ingroup  pinsdriver
 * @brief Default Interrupt Handler for RC1 pin. 
 *        This is a predefined interrupt handler to be used together with the RC1_SetInterruptHandler() method.
 *        This handler is called every time the RC1 ISR is executed. 
 * @pre Pins intializer called
 * @param none
 * @return none
 */
void RC1_DefaultInterruptHandler(void);


#endif // PINS_H
/**
 End of File
*/