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
? [2026] Microchip Technology Inc. and its subsidiaries.

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

// get/set IO_RA5 aliases
#define LED_RA5_TRIS                 TRISAbits.TRISA5
#define LED_RA5_LAT                  LATAbits.LATA5
#define LED_RA5_PORT                 PORTAbits.RA5
#define LED_RA5_WPU                  WPUAbits.WPUA5
#define LED_RA5_OD                   ODCONAbits.ODCA5
#define LED_RA5_ANS                  ANSELAbits.ANSA5
#define LED_RA5_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define LED_RA5_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define LED_RA5_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define LED_RA5_GetValue()           PORTAbits.RA5
#define LED_RA5_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define LED_RA5_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define LED_RA5_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define LED_RA5_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define LED_RA5_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define LED_RA5_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define LED_RA5_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define LED_RA5_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
// get/set IO_RA6 aliases
#define LED_RA6_TRIS                 TRISAbits.TRISA6
#define LED_RA6_LAT                  LATAbits.LATA6
#define LED_RA6_PORT                 PORTAbits.RA6
#define LED_RA6_WPU                  WPUAbits.WPUA6
#define LED_RA6_OD                   ODCONAbits.ODCA6
#define LED_RA6_ANS                  ANSELAbits.ANSA6
#define LED_RA6_SetHigh()            do { LATAbits.LATA6 = 1; } while(0)
#define LED_RA6_SetLow()             do { LATAbits.LATA6 = 0; } while(0)
#define LED_RA6_Toggle()             do { LATAbits.LATA6 = ~LATAbits.LATA6; } while(0)
#define LED_RA6_GetValue()           PORTAbits.RA6
#define LED_RA6_SetDigitalInput()    do { TRISAbits.TRISA6 = 1; } while(0)
#define LED_RA6_SetDigitalOutput()   do { TRISAbits.TRISA6 = 0; } while(0)
#define LED_RA6_SetPullup()          do { WPUAbits.WPUA6 = 1; } while(0)
#define LED_RA6_ResetPullup()        do { WPUAbits.WPUA6 = 0; } while(0)
#define LED_RA6_SetPushPull()        do { ODCONAbits.ODCA6 = 0; } while(0)
#define LED_RA6_SetOpenDrain()       do { ODCONAbits.ODCA6 = 1; } while(0)
#define LED_RA6_SetAnalogMode()      do { ANSELAbits.ANSA6 = 1; } while(0)
#define LED_RA6_SetDigitalMode()     do { ANSELAbits.ANSA6 = 0; } while(0)
// get/set IO_RA7 aliases
#define LED_RA7_TRIS                 TRISAbits.TRISA7
#define LED_RA7_LAT                  LATAbits.LATA7
#define LED_RA7_PORT                 PORTAbits.RA7
#define LED_RA7_WPU                  WPUAbits.WPUA7
#define LED_RA7_OD                   ODCONAbits.ODCA7
#define LED_RA7_ANS                  ANSELAbits.ANSA7
#define LED_RA7_SetHigh()            do { LATAbits.LATA7 = 1; } while(0)
#define LED_RA7_SetLow()             do { LATAbits.LATA7 = 0; } while(0)
#define LED_RA7_Toggle()             do { LATAbits.LATA7 = ~LATAbits.LATA7; } while(0)
#define LED_RA7_GetValue()           PORTAbits.RA7
#define LED_RA7_SetDigitalInput()    do { TRISAbits.TRISA7 = 1; } while(0)
#define LED_RA7_SetDigitalOutput()   do { TRISAbits.TRISA7 = 0; } while(0)
#define LED_RA7_SetPullup()          do { WPUAbits.WPUA7 = 1; } while(0)
#define LED_RA7_ResetPullup()        do { WPUAbits.WPUA7 = 0; } while(0)
#define LED_RA7_SetPushPull()        do { ODCONAbits.ODCA7 = 0; } while(0)
#define LED_RA7_SetOpenDrain()       do { ODCONAbits.ODCA7 = 1; } while(0)
#define LED_RA7_SetAnalogMode()      do { ANSELAbits.ANSA7 = 1; } while(0)
#define LED_RA7_SetDigitalMode()     do { ANSELAbits.ANSA7 = 0; } while(0)
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