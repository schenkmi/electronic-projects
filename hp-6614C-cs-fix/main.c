/*
 * File:   main.c
 * Author: schenk
 *
 * Created on 14. Oktober 2020, 19:50
 */

// PIC10F202 (no irq for timer :-))
// GP2/T0CKI/COUT/FOSC4 Clock input to TMR0

#include <xc.h>

#define _XTAL_FREQ 4000000  // 4MHZ crystal

#pragma config WDTE=OFF,MCLRE=OFF,CP=OFF

#define CLK_IN   GPIObits.GP1
#define NCS_OUT  GPIObits.GP0
#define LED_OUT  GPIObits.GP2

#define __USE_TIMER__

/* Setup function*/
void setup(void)
{
#ifdef __USE_TIMER__
    TRIS = 0b00000010;      // GP0 Output, GP1 Input, GP2 Output
    
    // see https://ww1.microchip.com/downloads/en/DeviceDoc/40001239F.pdf page 16
   
    // bit 7 /GPWU Enable Wake-up on Pin Change bit (GP0, GP1, GP3) => 1: disable
    // bit 6 /GPPU Enable Weak Pull-ups bit (GP0, GP1, GP3) => 1: disable
    // bit 5 T0CS Timer0 Clock Source Select bi =>  1: Transition on T0CKI pin (overrides TRIS on the T0CKI pin)
    // bit 4 T0SE Timer0 Source Edge Select bit => 1:  Increment on high-to-low transition on the T0CKI pin
    // bit 3 PSA Prescaler Assignment bit => 1:  Prescaler assigned to the WDT
    // bit 2-0 PS<2:0>: Prescaler Rate Select bits => 111: 1 : 128
    OPTION = 0b11111111;
    TMR0 = 0;
#else
    // see https://ww1.microchip.com/downloads/en/DeviceDoc/40001239F.pdf page 16
    
    // bit 7 /GPWU Enable Wake-up on Pin Change bit (GP0, GP1, GP3) => 1: disable
    // bit 6 /GPPU Enable Weak Pull-ups bit (GP0, GP1, GP3) => 1: disable
    // bit 5 T0CS Timer0 Clock Source Select bi =>  0: Transition on internal instruction cycle clock, FOSC/4
    // bit 4 T0SE Timer0 Source Edge Select bit => 1:  Increment on high-to-low transition on the T0CKI pin
    // bit 3 PSA Prescaler Assignment bit => 1:  Prescaler assigned to the WDT
    // bit 2-0 PS<2:0>: Prescaler Rate Select bits => 111: 1 : 128
    OPTION = 0b11011111;
    TRIS = 0b00000010;      // GP0 Output, GP1 Input, GP2 Output
#endif
    NCS_OUT = 0;            // /CS low
}

void detect_clk(void)
{
#ifdef __USE_TIMER__
    TMR0 = 0;
    while (TMR0 == 0) {
        __nop();
    }
    
    __delay_us(50);
#else
    unsigned char cnt = 0;
    while (cnt < 24) {
        while(CLK_IN == 0) {
           __nop();
        }
        while(CLK_IN == 1) {
           __nop();
           // WA because clock is faster than CPU speed :-)
           __delay_us(50);
           return;
        }
        cnt++;
    }
#endif
}

#if 0
/* wait till we have 100ms low signal on clock line */
void start_monitor_cond()
{
    unsigned char cnt = 100;
    
    __delay_ms(10);

    NCS_OUT = 1; // /CS to high
    __delay_us(50);
    NCS_OUT = 0; // /CS to low for next round

#ifdef __USE_TIMER__
    TMR0 = 0;
    
    while (cnt) {
         __delay_ms(1);
        if (TMR0 == 0) {
            cnt--;
        }
        else {
            cnt = 100;
            TMR0 = 0;
        }
    }
#else
    while(cnt) {
        if (CLK_IN == 0) {
            cnt--;
        }
        else {
            cnt = 100;
        }
        __delay_ms(1);
    }
#endif
}
#endif

#if 0
void blink()
{
    while (1) {
        LED_OUT = 0;
        __delay_ms(250);
        LED_OUT = 1;
        __delay_ms(250);
    }
}
#endif

void main(void)
{ 
    setup();
    
    // startup of HP 6614C is slow 
    __delay_ms(200);
    
    // simulate a DAC setup
    NCS_OUT = 1; // /CS to high
    __delay_us(50);
    NCS_OUT = 0; // /CS to low
        
    //blink();
    while(1) {
        detect_clk();
        
        NCS_OUT = 1; // /CS to high
         __delay_us(50);
        NCS_OUT = 0; // /CS to low for next round
    }
}