/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.31 and above
        MPLAB 	          :  MPLAB X 5.45	
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

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

/**
  Section: Included Files
*/

#include <xc.h>

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set RB4 procedures
#define RB4_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define RB4_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define RB4_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define RB4_GetValue()              PORTBbits.RB4
#define RB4_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define RB4_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define RB4_SetPullup()             do { WPUBbits.WPUB4 = 1; } while(0)
#define RB4_ResetPullup()           do { WPUBbits.WPUB4 = 0; } while(0)
#define RB4_SetAnalogMode()         do { ANSELBbits.ANSB4 = 1; } while(0)
#define RB4_SetDigitalMode()        do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set RB5 procedures
#define RB5_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define RB5_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define RB5_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define RB5_GetValue()              PORTBbits.RB5
#define RB5_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define RB5_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define RB5_SetPullup()             do { WPUBbits.WPUB5 = 1; } while(0)
#define RB5_ResetPullup()           do { WPUBbits.WPUB5 = 0; } while(0)
#define RB5_SetAnalogMode()         do { ANSELBbits.ANSB5 = 1; } while(0)
#define RB5_SetDigitalMode()        do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set RB6 procedures
#define RB6_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define RB6_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define RB6_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define RB6_GetValue()              PORTBbits.RB6
#define RB6_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define RB6_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define RB6_SetPullup()             do { WPUBbits.WPUB6 = 1; } while(0)
#define RB6_ResetPullup()           do { WPUBbits.WPUB6 = 0; } while(0)
#define RB6_SetAnalogMode()         do { ANSELBbits.ANSB6 = 1; } while(0)
#define RB6_SetDigitalMode()        do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set RB7 procedures
#define RB7_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define RB7_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define RB7_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define RB7_GetValue()              PORTBbits.RB7
#define RB7_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define RB7_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define RB7_SetPullup()             do { WPUBbits.WPUB7 = 1; } while(0)
#define RB7_ResetPullup()           do { WPUBbits.WPUB7 = 0; } while(0)
#define RB7_SetAnalogMode()         do { ANSELBbits.ANSB7 = 1; } while(0)
#define RB7_SetDigitalMode()        do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set LED_D5 aliases
#define LED_D5_TRIS                 TRISCbits.TRISC0
#define LED_D5_LAT                  LATCbits.LATC0
#define LED_D5_PORT                 PORTCbits.RC0
#define LED_D5_WPU                  WPUCbits.WPUC0
#define LED_D5_OD                   ODCONCbits.ODCC0
#define LED_D5_ANS                  ANSELCbits.ANSC0
#define LED_D5_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LED_D5_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LED_D5_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LED_D5_GetValue()           PORTCbits.RC0
#define LED_D5_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LED_D5_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define LED_D5_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define LED_D5_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define LED_D5_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define LED_D5_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define LED_D5_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define LED_D5_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set LED_D4 aliases
#define LED_D4_TRIS                 TRISCbits.TRISC1
#define LED_D4_LAT                  LATCbits.LATC1
#define LED_D4_PORT                 PORTCbits.RC1
#define LED_D4_WPU                  WPUCbits.WPUC1
#define LED_D4_OD                   ODCONCbits.ODCC1
#define LED_D4_ANS                  ANSELCbits.ANSC1
#define LED_D4_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED_D4_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED_D4_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED_D4_GetValue()           PORTCbits.RC1
#define LED_D4_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED_D4_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LED_D4_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define LED_D4_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define LED_D4_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define LED_D4_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define LED_D4_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define LED_D4_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set RESET aliases
#define RESET_TRIS                 TRISCbits.TRISC2
#define RESET_LAT                  LATCbits.LATC2
#define RESET_PORT                 PORTCbits.RC2
#define RESET_WPU                  WPUCbits.WPUC2
#define RESET_OD                   ODCONCbits.ODCC2
#define RESET_ANS                  ANSELCbits.ANSC2
#define RESET_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define RESET_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define RESET_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define RESET_GetValue()           PORTCbits.RC2
#define RESET_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define RESET_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define RESET_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define RESET_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define RESET_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define RESET_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define RESET_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define RESET_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/