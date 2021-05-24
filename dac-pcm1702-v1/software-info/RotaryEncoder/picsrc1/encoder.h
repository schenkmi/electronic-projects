/*--------------------------------------------------------------------
   
  Title       : Header file for encoder.c 
  Filename    : encoder.h 
   
----------------------------------------------------------------------*/

#ifndef ENCODER_H
#define ENCODER_H

/*--- Global encoder count ---*/

extern volatile int encoder_count;

/*--- Function prototype ---*/

void init_encoder(void);
void encoder_click(void);

#endif

/*--- End of File ---*/

