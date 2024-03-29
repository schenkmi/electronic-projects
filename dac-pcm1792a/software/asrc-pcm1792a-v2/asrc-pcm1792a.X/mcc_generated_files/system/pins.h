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
© [2024] Microchip Technology Inc. and its subsidiaries.

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

// get/set IO_RA2 aliases
#define BITSEL_TRIS                 TRISAbits.TRISA2
#define BITSEL_LAT                  LATAbits.LATA2
#define BITSEL_PORT                 PORTAbits.RA2
#define BITSEL_WPU                  WPUAbits.WPUA2
#define BITSEL_OD                   ODCONAbits.ODCA2
#define BITSEL_ANS                  ANSELAbits.ANSA2
#define BITSEL_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define BITSEL_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define BITSEL_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define BITSEL_GetValue()           PORTAbits.RA2
#define BITSEL_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define BITSEL_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define BITSEL_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define BITSEL_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define BITSEL_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define BITSEL_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define BITSEL_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define BITSEL_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set IO_RB4 aliases
#define SDA_TRIS                 TRISBbits.TRISB4
#define SDA_LAT                  LATBbits.LATB4
#define SDA_PORT                 PORTBbits.RB4
#define SDA_WPU                  WPUBbits.WPUB4
#define SDA_OD                   ODCONBbits.ODCB4
#define SDA_ANS                  ANSELBbits.ANSB4
#define SDA_SetHigh()            do { LATBbits.LATB4 = 1; } while(0)
#define SDA_SetLow()             do { LATBbits.LATB4 = 0; } while(0)
#define SDA_Toggle()             do { LATBbits.LATB4 = ~LATBbits.LATB4; } while(0)
#define SDA_GetValue()           PORTBbits.RB4
#define SDA_SetDigitalInput()    do { TRISBbits.TRISB4 = 1; } while(0)
#define SDA_SetDigitalOutput()   do { TRISBbits.TRISB4 = 0; } while(0)
#define SDA_SetPullup()          do { WPUBbits.WPUB4 = 1; } while(0)
#define SDA_ResetPullup()        do { WPUBbits.WPUB4 = 0; } while(0)
#define SDA_SetPushPull()        do { ODCONBbits.ODCB4 = 0; } while(0)
#define SDA_SetOpenDrain()       do { ODCONBbits.ODCB4 = 1; } while(0)
#define SDA_SetAnalogMode()      do { ANSELBbits.ANSB4 = 1; } while(0)
#define SDA_SetDigitalMode()     do { ANSELBbits.ANSB4 = 0; } while(0)

// get/set IO_RB5 aliases
#define SDA2_TRIS                 TRISBbits.TRISB5
#define SDA2_LAT                  LATBbits.LATB5
#define SDA2_PORT                 PORTBbits.RB5
#define SDA2_WPU                  WPUBbits.WPUB5
#define SDA2_OD                   ODCONBbits.ODCB5
#define SDA2_ANS                  ANSELBbits.ANSB5
#define SDA2_SetHigh()            do { LATBbits.LATB5 = 1; } while(0)
#define SDA2_SetLow()             do { LATBbits.LATB5 = 0; } while(0)
#define SDA2_Toggle()             do { LATBbits.LATB5 = ~LATBbits.LATB5; } while(0)
#define SDA2_GetValue()           PORTBbits.RB5
#define SDA2_SetDigitalInput()    do { TRISBbits.TRISB5 = 1; } while(0)
#define SDA2_SetDigitalOutput()   do { TRISBbits.TRISB5 = 0; } while(0)
#define SDA2_SetPullup()          do { WPUBbits.WPUB5 = 1; } while(0)
#define SDA2_ResetPullup()        do { WPUBbits.WPUB5 = 0; } while(0)
#define SDA2_SetPushPull()        do { ODCONBbits.ODCB5 = 0; } while(0)
#define SDA2_SetOpenDrain()       do { ODCONBbits.ODCB5 = 1; } while(0)
#define SDA2_SetAnalogMode()      do { ANSELBbits.ANSB5 = 1; } while(0)
#define SDA2_SetDigitalMode()     do { ANSELBbits.ANSB5 = 0; } while(0)

// get/set IO_RB6 aliases
#define SCL_TRIS                 TRISBbits.TRISB6
#define SCL_LAT                  LATBbits.LATB6
#define SCL_PORT                 PORTBbits.RB6
#define SCL_WPU                  WPUBbits.WPUB6
#define SCL_OD                   ODCONBbits.ODCB6
#define SCL_ANS                  ANSELBbits.ANSB6
#define SCL_SetHigh()            do { LATBbits.LATB6 = 1; } while(0)
#define SCL_SetLow()             do { LATBbits.LATB6 = 0; } while(0)
#define SCL_Toggle()             do { LATBbits.LATB6 = ~LATBbits.LATB6; } while(0)
#define SCL_GetValue()           PORTBbits.RB6
#define SCL_SetDigitalInput()    do { TRISBbits.TRISB6 = 1; } while(0)
#define SCL_SetDigitalOutput()   do { TRISBbits.TRISB6 = 0; } while(0)
#define SCL_SetPullup()          do { WPUBbits.WPUB6 = 1; } while(0)
#define SCL_ResetPullup()        do { WPUBbits.WPUB6 = 0; } while(0)
#define SCL_SetPushPull()        do { ODCONBbits.ODCB6 = 0; } while(0)
#define SCL_SetOpenDrain()       do { ODCONBbits.ODCB6 = 1; } while(0)
#define SCL_SetAnalogMode()      do { ANSELBbits.ANSB6 = 1; } while(0)
#define SCL_SetDigitalMode()     do { ANSELBbits.ANSB6 = 0; } while(0)

// get/set IO_RB7 aliases
#define SCL2_TRIS                 TRISBbits.TRISB7
#define SCL2_LAT                  LATBbits.LATB7
#define SCL2_PORT                 PORTBbits.RB7
#define SCL2_WPU                  WPUBbits.WPUB7
#define SCL2_OD                   ODCONBbits.ODCB7
#define SCL2_ANS                  ANSELBbits.ANSB7
#define SCL2_SetHigh()            do { LATBbits.LATB7 = 1; } while(0)
#define SCL2_SetLow()             do { LATBbits.LATB7 = 0; } while(0)
#define SCL2_Toggle()             do { LATBbits.LATB7 = ~LATBbits.LATB7; } while(0)
#define SCL2_GetValue()           PORTBbits.RB7
#define SCL2_SetDigitalInput()    do { TRISBbits.TRISB7 = 1; } while(0)
#define SCL2_SetDigitalOutput()   do { TRISBbits.TRISB7 = 0; } while(0)
#define SCL2_SetPullup()          do { WPUBbits.WPUB7 = 1; } while(0)
#define SCL2_ResetPullup()        do { WPUBbits.WPUB7 = 0; } while(0)
#define SCL2_SetPushPull()        do { ODCONBbits.ODCB7 = 0; } while(0)
#define SCL2_SetOpenDrain()       do { ODCONBbits.ODCB7 = 1; } while(0)
#define SCL2_SetAnalogMode()      do { ANSELBbits.ANSB7 = 1; } while(0)
#define SCL2_SetDigitalMode()     do { ANSELBbits.ANSB7 = 0; } while(0)

// get/set IO_RC0 aliases
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

// get/set IO_RC1 aliases
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

// get/set IO_RC3 aliases
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

// get/set IO_RC4 aliases
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

// get/set IO_RC6 aliases
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

// get/set IO_RC7 aliases
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