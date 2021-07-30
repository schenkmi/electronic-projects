/*--------------------------------------------------------------------
  
  Title       : Rotary Encoder Interface
  Filename    : encoder.c 

----------------------------------------------------------------------*/

#include <pic.h>

/*--- Global encoder count ---*/

volatile signed int encoder_count;

/*--- Encoder lookup table ---*/

const signed char table[] = {0,-1,+1,0,+1,0,0,-1,-1,0,0,+1,0,+1,-1,0};

/*--- Initialise Encoder ---*/

void init_encoder(void)
  {
  ANSELH &= 0xfc;   /* RB2 and RB3 as digital I/O */
  IOCB = 0x0c;      /* Interrupt on change enabled for RB2, RB3 */

  encoder_count = 0;

  RBIF = 0;
  RBIE = 1;         /* Interrupt on change enable */
  }
 
/*--- Encoder function ---*/

void encoder_click(void)
  {
  static unsigned char previous = 0;
  unsigned char temp;

  temp = 5;

  while(temp--){ /* debounce */
    ;
    }

  temp = PORTB;     /* Read port */
  temp >>= 2;       /* Shift input to bit positions 1, 0 */
  temp &= 0x03;     /* Mask out bits */ 
  previous <<= 2;   /* shift the previous data left two places */ 
  previous |= temp; /* OR in the two new bits */

  encoder_count += table[(previous & 0x0f)];  /* Index into table */
  }

/*--- End of File ---*/