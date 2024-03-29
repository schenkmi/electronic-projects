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

// get/set SEL aliases
#define SEL_TRIS                 TRISAbits.TRISA2
#define SEL_LAT                  LATAbits.LATA2
#define SEL_PORT                 PORTAbits.RA2
#define SEL_WPU                  WPUAbits.WPUA2
#define SEL_OD                   ODCONAbits.ODCA2
#define SEL_ANS                  ANSELAbits.ANSA2
#define SEL_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define SEL_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define SEL_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define SEL_GetValue()           PORTAbits.RA2
#define SEL_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define SEL_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define SEL_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define SEL_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define SEL_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define SEL_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define SEL_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define SEL_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

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
#define RESET_TRIS                 TRISCbits.TRISC3
#define RESET_LAT                  LATCbits.LATC3
#define RESET_PORT                 PORTCbits.RC3
#define RESET_WPU                  WPUCbits.WPUC3
#define RESET_OD                   ODCONCbits.ODCC3
#define RESET_ANS                  ANSELCbits.ANSC3
#define RESET_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define RESET_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define RESET_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define RESET_GetValue()           PORTCbits.RC3
#define RESET_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define RESET_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define RESET_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define RESET_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define RESET_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define RESET_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define RESET_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define RESET_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set ENC1CHANA aliases
#define ENC1CHANA_TRIS                 TRISCbits.TRISC6
#define ENC1CHANA_LAT                  LATCbits.LATC6
#define ENC1CHANA_PORT                 PORTCbits.RC6
#define ENC1CHANA_WPU                  WPUCbits.WPUC6
#define ENC1CHANA_OD                   ODCONCbits.ODCC6
#define ENC1CHANA_ANS                  ANSELCbits.ANSC6
#define ENC1CHANA_SetHigh()            do { LATCbits.LATC6 = 1; } while(0)
#define ENC1CHANA_SetLow()             do { LATCbits.LATC6 = 0; } while(0)
#define ENC1CHANA_Toggle()             do { LATCbits.LATC6 = ~LATCbits.LATC6; } while(0)
#define ENC1CHANA_GetValue()           PORTCbits.RC6
#define ENC1CHANA_SetDigitalInput()    do { TRISCbits.TRISC6 = 1; } while(0)
#define ENC1CHANA_SetDigitalOutput()   do { TRISCbits.TRISC6 = 0; } while(0)
#define ENC1CHANA_SetPullup()          do { WPUCbits.WPUC6 = 1; } while(0)
#define ENC1CHANA_ResetPullup()        do { WPUCbits.WPUC6 = 0; } while(0)
#define ENC1CHANA_SetPushPull()        do { ODCONCbits.ODCC6 = 0; } while(0)
#define ENC1CHANA_SetOpenDrain()       do { ODCONCbits.ODCC6 = 1; } while(0)
#define ENC1CHANA_SetAnalogMode()      do { ANSELCbits.ANSC6 = 1; } while(0)
#define ENC1CHANA_SetDigitalMode()     do { ANSELCbits.ANSC6 = 0; } while(0)

// get/set ENC1CHANB aliases
#define ENC1CHANB_TRIS                 TRISCbits.TRISC7
#define ENC1CHANB_LAT                  LATCbits.LATC7
#define ENC1CHANB_PORT                 PORTCbits.RC7
#define ENC1CHANB_WPU                  WPUCbits.WPUC7
#define ENC1CHANB_OD                   ODCONCbits.ODCC7
#define ENC1CHANB_ANS                  ANSELCbits.ANSC7
#define ENC1CHANB_SetHigh()            do { LATCbits.LATC7 = 1; } while(0)
#define ENC1CHANB_SetLow()             do { LATCbits.LATC7 = 0; } while(0)
#define ENC1CHANB_Toggle()             do { LATCbits.LATC7 = ~LATCbits.LATC7; } while(0)
#define ENC1CHANB_GetValue()           PORTCbits.RC7
#define ENC1CHANB_SetDigitalInput()    do { TRISCbits.TRISC7 = 1; } while(0)
#define ENC1CHANB_SetDigitalOutput()   do { TRISCbits.TRISC7 = 0; } while(0)
#define ENC1CHANB_SetPullup()          do { WPUCbits.WPUC7 = 1; } while(0)
#define ENC1CHANB_ResetPullup()        do { WPUCbits.WPUC7 = 0; } while(0)
#define ENC1CHANB_SetPushPull()        do { ODCONCbits.ODCC7 = 0; } while(0)
#define ENC1CHANB_SetOpenDrain()       do { ODCONCbits.ODCC7 = 1; } while(0)
#define ENC1CHANB_SetAnalogMode()      do { ANSELCbits.ANSC7 = 1; } while(0)
#define ENC1CHANB_SetDigitalMode()     do { ANSELCbits.ANSC7 = 0; } while(0)

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


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF6 pin functionality
 * @Example
    IOCCF6_ISR();
 */
void IOCCF6_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF6 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF6 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF6_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF6 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF6_SetInterruptHandler() method.
    This handler is called every time the IOCCF6 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(IOCCF6_InterruptHandler);

*/
extern void (*IOCCF6_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF6 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF6_SetInterruptHandler() method.
    This handler is called every time the IOCCF6 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF6_SetInterruptHandler(IOCCF6_DefaultInterruptHandler);

*/
void IOCCF6_DefaultInterruptHandler(void);


/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handler for the IOCCF7 pin functionality
 * @Example
    IOCCF7_ISR();
 */
void IOCCF7_ISR(void);

/**
  @Summary
    Interrupt Handler Setter for IOCCF7 pin interrupt-on-change functionality

  @Description
    Allows selecting an interrupt handler for IOCCF7 at application runtime
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    InterruptHandler function pointer.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(MyInterruptHandler);

*/
void IOCCF7_SetInterruptHandler(void (* InterruptHandler)(void));

/**
  @Summary
    Dynamic Interrupt Handler for IOCCF7 pin

  @Description
    This is a dynamic interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed and allows any function to be registered at runtime.
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_InterruptHandler);

*/
extern void (*IOCCF7_InterruptHandler)(void);

/**
  @Summary
    Default Interrupt Handler for IOCCF7 pin

  @Description
    This is a predefined interrupt handler to be used together with the IOCCF7_SetInterruptHandler() method.
    This handler is called every time the IOCCF7 ISR is executed. 
    
  @Preconditions
    Pin Manager intializer called

  @Returns
    None.

  @Param
    None.

  @Example
    PIN_MANAGER_Initialize();
    IOCCF7_SetInterruptHandler(IOCCF7_DefaultInterruptHandler);

*/
void IOCCF7_DefaultInterruptHandler(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/