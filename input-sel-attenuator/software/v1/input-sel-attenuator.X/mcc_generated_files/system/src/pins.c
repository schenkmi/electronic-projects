/**
 * Generated Driver File
 * 
 * @file pins.c
 * 
 * @ingroup  pinsdriver
 * 
 * @brief This is generated driver implementation for pins. 
 *        This file provides implementations for pin APIs for all pins selected in the GUI.
 *
 * @version Driver Version 3.0.0
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

#include "../pins.h"

void (*RC0_InterruptHandler)(void);
void (*RC1_InterruptHandler)(void);

void PIN_MANAGER_Initialize(void)
{
   /**
    LATx registers
    */
    LATA = 0x0;
    LATB = 0x0;
    LATC = 0x18;
    LATE = 0x0;

    /**
    TRISx registers
    */
    TRISA = 0x0;
    TRISB = 0xC0;
    TRISC = 0xFF;
    TRISE = 0x8;

    /**
    ANSELx registers
    */
    ANSELA = 0x0;
    ANSELB = 0xC0;
    ANSELC = 0xE0;

    /**
    WPUx registers
    */
    WPUA = 0x0;
    WPUB = 0x0;
    WPUC = 0x0;
    WPUE = 0x0;
  

    /**
    APFCONx registers
    */

    /**
    ODx registers
    */
   
    ODCONA = 0x0;
    ODCONB = 0x0;
    ODCONC = 0x0;
    /**
    SLRCONx registers
    */
    SLRCONA = 0xFF;
    SLRCONB = 0xFF;
    SLRCONC = 0xFF;
    /**
    INLVLx registers
    */
    INLVLA = 0xFF;
    INLVLB = 0xFF;
    INLVLC = 0xFF;
    INLVLE = 0x8;

    /**
    PPS registers
    */
    SSP1CLKPPS = 0x13;  //RC3->MSSP1:SCL1;
    RC3PPS = 0x15;  //RC3->MSSP1:SCL1;
    SSP1DATPPS = 0x14;  //RC4->MSSP1:SDA1;
    RC4PPS = 0x16;  //RC4->MSSP1:SDA1;

   /**
    IOCx registers 
    */
    IOCAP = 0x0;
    IOCAN = 0x0;
    IOCAF = 0x0;
    IOCBP = 0x0;
    IOCBN = 0x0;
    IOCBF = 0x0;
    IOCCP = 0x3;
    IOCCN = 0x3;
    IOCCF = 0x0;
    IOCEP = 0x0;
    IOCEN = 0x0;
    IOCEF = 0x0;

    RC0_SetInterruptHandler(RC0_DefaultInterruptHandler);
    RC1_SetInterruptHandler(RC1_DefaultInterruptHandler);

    // Enable PIE0bits.IOCIE interrupt 
    PIE0bits.IOCIE = 1; 
}
  
void PIN_MANAGER_IOC(void)
{
    // interrupt on change for pin RC0}
    if(IOCCFbits.IOCCF0 == 1)
    {
        RC0_ISR();  
    }
    // interrupt on change for pin RC1}
    if(IOCCFbits.IOCCF1 == 1)
    {
        RC1_ISR();  
    }
}
   
/**
   RC0 Interrupt Service Routine
*/
void RC0_ISR(void) {

    // Add custom IOCCF0 code

    // Call the interrupt handler for the callback registered at runtime
    if(RC0_InterruptHandler)
    {
        RC0_InterruptHandler();
    }
    IOCCFbits.IOCCF0 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF0 at application runtime
*/
void RC0_SetInterruptHandler(void (* InterruptHandler)(void)){
    RC0_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF0
*/
void RC0_DefaultInterruptHandler(void){
    // add your RC0 interrupt custom code
    // or set custom function using RC0_SetInterruptHandler()
}
   
/**
   RC1 Interrupt Service Routine
*/
void RC1_ISR(void) {

    // Add custom IOCCF1 code

    // Call the interrupt handler for the callback registered at runtime
    if(RC1_InterruptHandler)
    {
        RC1_InterruptHandler();
    }
    IOCCFbits.IOCCF1 = 0;
}

/**
  Allows selecting an interrupt handler for IOCCF1 at application runtime
*/
void RC1_SetInterruptHandler(void (* InterruptHandler)(void)){
    RC1_InterruptHandler = InterruptHandler;
}

/**
  Default interrupt handler for IOCCF1
*/
void RC1_DefaultInterruptHandler(void){
    // add your RC1 interrupt custom code
    // or set custom function using RC1_SetInterruptHandler()
}
/**
 End of File
*/