/*--------------------------------------------------------------------
 
  Title       : Rotary Encoder example using Pic16F883  
  Filename    : main.c 

In this example, the rotary encoder outputs are connected to pins RB2 and RB3 of the Pic16F883.
Rotating the encoder clockwise produced the following sequence at RB2 and RB3:

0 0
1 0
1 1
0 1

Rotating the encoder anti-clockwise produced the following sequence at RB2 and RB3:

0 0
0 1
1 1
1 0

If you combine the current state of the outputs with the previous state of the outputs, 
you get a unique sequence for the clockwise and anticlockwise rotation.

Clockwise:

0 1 0 0  Decimal 4
0 0 1 0  Decimal 2
1 0 1 1  Decimal 11
1 1 0 1  Decimal 13

Anticlockwise:

1 0 0 0  Decimal 8
0 0 0 1  Decimal 1
0 1 1 1  Decimal 7
1 1 1 0  Decimal 14 

These unique values are used to index into a lookup table to increment or decrement the encoder count.
   
--------------------------------------------------------------------*/

#include <pic.h>
#include "encoder.h"

/*--- Configuration fuse setings (2 locations) ---*/

  __CONFIG(INTIO & WDTDIS & PWRTEN & MCLREN & BOREN & IESODIS & FCMDIS & LVPDIS);
  __CONFIG(BORV21 & WP2);
    
/*--- Program entry ---*/

void main(void)
  {
  init_encoder(); 
  GIE = 1U;   /* Global Interrupt Enable */
 
  for(;;){
    ;
    }
  }
    
/*--- Interrupt vector ---*/  
  
static void interrupt int_vector(void)
  { 
  if(RBIF)
    {
    encoder_click();
    RBIF = 0;
    }
  }
   
/*--- End of File ---*/
