/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * irmpextlog.c - external logging
 *
 * If you cannot use the internal UART logging routine, adapt the
 * source below for your application. The following implementation
 * is an example for a PIC 18F2550 with USB interface.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
#include "irmp.h"

#if IRMP_EXT_LOGGING == 1

#include <stdio.h>



#include "irmpextlog.h"
//#include "system/usb/usb.h"

#include "../mcc_generated_files/uart/eusart1.h"


#define bit_set(var,bitnr)      ((var) |= 1 << (bitnr))         // set single bit in byte
#define loglen                  50                              // byte length for saving the data from irmp.c
                                                                // check your USB settings for max length of USB interface used for this FW!
static unsigned char            logdata[loglen];                // array for saveing the data from irmp.c
static unsigned char            logindex = 3;                   // start index of logdata
static char                     bitindex = 7;                   // bit position in current byte
static unsigned int             bitcount;

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * Initialize external logging
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
initextlog (void)                                               // reset all data to default, only during init
{
    unsigned char i;

    for (i = 0; i < loglen; i++)
    {
        logdata[i] = 0;
    }

    bitcount = 0;
    logindex = 3;
    bitindex = 7;
}

/*---------------------------------------------------------------------------------------------------------------------------------------------------
 * Send logging data via device (e.g. USB on PIC)
 *---------------------------------------------------------------------------------------------------------------------------------------------------
 */
void
sendextlog (unsigned char data)
{
//unsigned char a = data;
//const char* hexDigitTable = "0123456789abcdef";
//char asciiDigit0 = hexDigitTable[a & 0x0f];
//char asciiDigit1 = hexDigitTable[(a & 0xf0) >> 4];
//    
//    EUSART1_Write(asciiDigit0);
//    EUSART1_Write(asciiDigit1);
    
    if (data) {
        EUSART1_Write('1');
    } else {
        EUSART1_Write('0');
    }
    
    return;
    
    //printf("GUGUGUS\n");
    if (logindex == loglen || data == '\n')                     // buffer full or \n  -->  send to application
    {
        //if (mUSBUSARTIsTxTrfReady())                            // check USB, if ready send
        {
            logdata[0] = 0x01;                                  // indicator for logging, depends on your application
            logdata[1] = logindex;                              // save how much bytes are send from irmp.c
            logdata[2] = 0;                                     // set \n Index to 0;  0=buffer full;  0xA=\n received

            if (data == '\n')
            {
                logdata[2] = data;                              // \n --> save \n=0xA in to check in app that \n was received
            }

           // mUSBUSARTTxRam((unsigned char *) &logdata, loglen); // send all Data to main Seoftware
            
            for (int i = 0; i < loglen; i++) {
               // printf("0x02x\n", logdata[i]);
                
                EUSART1_Write(logdata[i]);
            }
            

            logindex = 3;                                       // reset index
            bitindex = 7;                                       // reset bit position
            logdata[logindex] = 0;                              // reset value of new logindex to 0
        }
    }
    else
    {
        bitcount++;

        if (data == '1')
        {
            bit_set(logdata[logindex], bitindex);               // all logdata[logindex] on start = 0 --> only 1 must be set
        }

        bitindex--;                                             // decrease bitposition, wirte from left to right

        if (bitindex == -1)                                     // byte complete Bit 7->0 --> next one
        {
            bitindex = 7;
            logindex++;

            if (logindex < loglen)
            {
                logdata[logindex] = 0;                          // set next byte to 0
            }
        }
    }
}

#endif //IRMP_EXT_LOGGING

#if defined(PIC_C18)
static void
dummy (void)
{
  // Only to avoid C18 compiler error
}
#endif
