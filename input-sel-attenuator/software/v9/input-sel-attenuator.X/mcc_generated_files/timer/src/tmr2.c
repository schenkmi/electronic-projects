/**
 * TMR2 Generated Driver File
 *
 * @file tmr2.c
 * 
 * @ingroup  tmr2
 * 
 * @brief Driver implementation for the TMR2 module.
 *
 * @version Driver Version 4.0.1
 *
 * @version Package Version 5.1.2
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

/**
  Section: Included Files
*/

#include <xc.h>
#include "../tmr2.h"

static void (*TMR2_PeriodMatchCallback)(void);
static void TMR2_DefaultPeriodMatchCallback(void);

/**
  Section: TMR2 APIs
*/

void TMR2_Initialize(void)
{
    T2CLKCON = (uint8_t)((1 << _T2CLKCON_T2CS_POSN));  // T2CS FOSC/4

    T2HLT = (uint8_t)((0 << _T2HLT_T2MODE_POSN)   // T2MODE Software control
        | (0 << _T2HLT_CSYNC_POSN)   // CSYNC Not Synchronized
        | (0 << _T2HLT_CPOL_POSN)   // CPOL Rising Edge
        | (0 << _T2HLT_T2PSYNC_POSN));  // T2PSYNC Not Synchronized

    T2RST = (uint8_t)((0 << _T2RST_T2RSEL_POSN));  // T2RSEL T2CKIPPS pin

    T2PR = (uint8_t)0x20;    // Period 0.000066s; Timer Prescaled Frequency 500000Hz; Count 32; Postscaler 1:1; 

    T2TMR = (uint8_t)0x0;

    TMR2_PeriodMatchCallback = TMR2_DefaultPeriodMatchCallback;
    
    PIR1bits.TMR2IF = 0U;   
    PIE1bits.TMR2IE = 1U;

    T2CON = (uint8_t)((4 << _T2CON_T2CKPS_POSN)   // T2CKPS 1:16
        | (1 << _T2CON_TMR2ON_POSN)   // TMR2ON on
        | (0 << _T2CON_T2OUTPS_POSN));  // T2OUTPS 1:1
}

void TMR2_Deinitialize(void)
{
    T2CONbits.TMR2ON = 0U;
    
    PIR1bits.TMR2IF = 0U;	   
    PIE1bits.TMR2IE = 0U;		
    
    T2CON = (uint8_t)0x0;
    T2CLKCON = (uint8_t)0x0;
    T2HLT = (uint8_t)0x0;
    T2RST =(uint8_t) 0x0;
    T2PR = (uint8_t)0xFF;
    T2TMR = (uint8_t)0x0;
}

void TMR2_Start(void)
{   
    T2CONbits.TMR2ON = 1U;
}

void TMR2_Stop(void)
{   
    T2CONbits.TMR2ON = 0U;
}

void TMR2_ModeSet(TMR2_HLT_MODE mode)
{  
    T2HLTbits.T2MODE = (uint8_t)mode;
}

void TMR2_ExtResetSourceSet(TMR2_HLT_EXT_RESET_SOURCE reset)
{   
    T2RSTbits.T2RSEL = (uint8_t)reset;
}

uint8_t TMR2_CounterGet(void)
{
    return T2TMR;
}

void TMR2_CounterSet(uint8_t count)
{  
    T2TMR = count;
}

void TMR2_PeriodSet(uint8_t periodVal)
{
    T2PR = periodVal;
}

uint8_t TMR2_PeriodGet(void)
{
    return T2PR;
}

uint8_t TMR2_MaxCountGet(void)
{
    return TMR2_MAX_COUNT;
}

void TMR2_TMRInterruptEnable(void)
{
    PIE1bits.TMR2IE = 1U;
}

void TMR2_TMRInterruptDisable(void)
{
    PIE1bits.TMR2IE = 0U;
}

void TMR2_ISR(void)
{
    // The ticker is set to 1 -> The callback function gets called every time this ISR executes.
    if(NULL != TMR2_PeriodMatchCallback)
    {
        TMR2_PeriodMatchCallback();
    }
   PIR1bits.TMR2IF = 0U;
}

void TMR2_PeriodMatchCallbackRegister(void (* callbackHandler)(void))
{
   TMR2_PeriodMatchCallback = callbackHandler;
}

static void TMR2_DefaultPeriodMatchCallback(void)
{
    // Default callback function
}


