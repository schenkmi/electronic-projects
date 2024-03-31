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
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.8
        Device            :  PIC16F18446
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 2.36 and above
        MPLAB 	          :  MPLAB X 6.00	
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

// get/set ENC1_SWITCH aliases
#define ENC1_SWITCH_TRIS                 TRISCbits.TRISC4
#define ENC1_SWITCH_LAT                  LATCbits.LATC4
#define ENC1_SWITCH_PORT                 PORTCbits.RC4
#define ENC1_SWITCH_WPU                  WPUCbits.WPUC4
#define ENC1_SWITCH_OD                   ODCONCbits.ODCC4
#define ENC1_SWITCH_ANS                  ANSELCbits.ANSC4
#define ENC1_SWITCH_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define ENC1_SWITCH_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define ENC1_SWITCH_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define ENC1_SWITCH_GetValue()           PORTCbits.RC4
#define ENC1_SWITCH_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define ENC1_SWITCH_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define ENC1_SWITCH_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define ENC1_SWITCH_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define ENC1_SWITCH_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define ENC1_SWITCH_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define ENC1_SWITCH_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define ENC1_SWITCH_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set ENC1_CHANA aliases
#define ENC1_CHANA_TRIS                 TRISCbits.TRISC6
#define ENC1_CHANA_LAT                  LATCbits.LATC6
#define ENC1_CHANA_PORT                 PORTCbits.RC6
#define ENC1_CHANA_WPU                  WPUCbits.WPUC6
#define ENC1_CHANA_OD                   ODCONCbits.ODCC6
#define ENC1_CHANA_ANS                  ANSELCbits.ANSC6
#define ENC1_CHANA_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define ENC1_CHANA_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define ENC1_CHANA_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define ENC1_CHANA_GetValue()           PORTCbits.RC6
#define ENC1_CHANA_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define ENC1_CHANA_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define ENC1_CHANA_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define ENC1_CHANA_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define ENC1_CHANA_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define ENC1_CHANA_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define ENC1_CHANA_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define ENC1_CHANA_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set ENC1_CHANB aliases
#define ENC1_CHANB_TRIS                 TRISCbits.TRISC7
#define ENC1_CHANB_LAT                  LATCbits.LATC7
#define ENC1_CHANB_PORT                 PORTCbits.RC7
#define ENC1_CHANB_WPU                  WPUCbits.WPUC7
#define ENC1_CHANB_OD                   ODCONCbits.ODCC7
#define ENC1_CHANB_ANS                  ANSELCbits.ANSC7
#define ENC1_CHANB_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define ENC1_CHANB_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define ENC1_CHANB_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define ENC1_CHANB_GetValue()           PORTCbits.RC7
#define ENC1_CHANB_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define ENC1_CHANB_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define ENC1_CHANB_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define ENC1_CHANB_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define ENC1_CHANB_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define ENC1_CHANB_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define ENC1_CHANB_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define ENC1_CHANB_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

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