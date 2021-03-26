/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.7
        Device            :  PIC16F18446
        Driver Version    :  2.00
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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"

// Page 38 
#define SRC4392_I2C_SLAVE_ADDR              0x70


// SRC4392 control/status registers
#define SRC_REG01	0x01		// power down and reset
#define SRC_REG02	0x02		// global interrupt status
#define SRC_REG03	0x03		// port A control
#define SRC_REG04	0x04		// port A control
#define SRC_REG05	0x05		// port B control
#define SRC_REG06	0x06		// port B control
#define SRC_REG07	0x07		// DIT control
#define SRC_REG08	0x08		// DIT control
#define SRC_REG09	0x09		// DIT control
#define SRC_REG0A	0x0a		// SRC and DIT status
#define SRC_REG0B	0x0b		// SRC and DIT interrupt mask
#define SRC_REG0C	0x0c		// SRC and DIT interrupt mode
#define SRC_REG0D	0x0d		// DIR control
#define SRC_REG0E	0x0e		// DIR control
#define SRC_REG0F	0x0f		// DIR PLL configuration
#define SRC_REG10	0x10		// DIR PLL configuration
#define SRC_REG11	0x11		// DIR PLL configuration
#define SRC_REG12	0x12		// non-PCM audio detection
#define SRC_REG13	0x13		// DIR status
#define SRC_REG14	0x14		// DIR status
#define SRC_REG15	0x15		// DIR status
#define SRC_REG16	0x16		// DIR interrupt mask
#define SRC_REG17	0x17		// DIR interrupt mask
#define SRC_REG18	0x18		// DIR interrupt mode
#define SRC_REG19	0x19		// DIR interrupt mode
#define SRC_REG1A	0x1a		// DIR interrupt mode
#define SRC_REG1B	0x1b		// GP01
#define SRC_REG1C	0x1c		// GP02
#define SRC_REG1D	0x1d		// GP03
#define SRC_REG1E	0x1e		// GP04
#define SRC_REG1F	0x1f		// audio CD Q-channel subcode
#define SRC_REG20	0x20		// audio CD Q-channel subcode
#define SRC_REG21	0x21		// audio CD Q-channel subcode
#define SRC_REG22	0x22		// audio CD Q-channel subcode
#define SRC_REG23	0x23		// audio CD Q-channel subcode
#define SRC_REG24	0x24		// audio CD Q-channel subcode
#define SRC_REG25	0x25		// audio CD Q-channel subcode
#define SRC_REG26	0x26		// audio CD Q-channel subcode
#define SRC_REG27	0x27		// audio CD Q-channel subcode
#define SRC_REG28	0x28		// audio CD Q-channel subcode
#define SRC_REG29	0x29		// PC burst preamble, high byte
#define SRC_REG2A	0x2a		// PC burst preamble, low byte
#define SRC_REG2B	0x2b		// PD burst preamble, high byte
#define SRC_REG2C	0x2c		// PD burst preamble, low byte
#define SRC_REG2D	0x2d		// SRC control
#define SRC_REG2E	0x2e		// SRC control
#define SRC_REG2F	0x2f		// SRC control
#define SRC_REG30	0x30		// SRC control
#define SRC_REG31	0x31		// SRC control
#define SRC_REG32	0x32		// SRC input/output ratio
#define SRC_REG33	0x33		// SRC input/output ratio
#define SRC_REG7F	0x7f		// page selection



// Sample rate enums
#define SAMPLERATE_UNKNOWN	0	// unknown
#define SAMPLERATE_32KHZ	1	// 32.0KHz
#define SAMPLERATE_44KHZ	2	// 44.1KHz
#define SAMPLERATE_48KHZ	3	// 48.0KHz
#define SAMPLERATE_64KHZ	4	// 64.0KHz
#define SAMPLERATE_88KHZ	5	// 88.2KHz
#define SAMPLERATE_96KHZ	6	// 96.0KHz
#define SAMPLERATE_128KHZ	7	// 128.0KHz
#define SAMPLERATE_176KHZ	8	// 176.4KHz
#define SAMPLERATE_192KHZ	9	// 192.0KHz

/*
 * Upsampling enums
 */
#define UPSAMPLE_192KHZ		0	// 192KHz
#define UPSAMPLE_96KHZ		1	// 96KHz

/*
 * DIT routing mode enums
 */
#define DIT_UPSAMPLE		0	// upsample
#define DIT_LOOPOUT		1	// loop-back

/*
 * Digital de-emphasis enums
 */
#define DEEMPH_AUTO		0	// auto
#define DEEMPH_OFF		1	// off


uint8_t		upsample_rate = UPSAMPLE_192KHZ;
uint8_t		dit_mode = DIT_UPSAMPLE;


// input 0,1,2 or 3

#define INPUT_RX1   0
#define INPUT_RX2   1
#define INPUT_RX3   2
#define INPUT_RX4   3
#define MAX_INPUTS  INPUT_RX4

// Read one byte from the SRC4392
uint8_t src4392_read(uint8_t reg)
{
    return I2C1_Read1ByteRegister(SRC4392_I2C_SLAVE_ADDR, reg);   
}


// Write one byte to the SRC4392
void src4392_write(uint8_t reg, uint8_t val)
{
    I2C1_Write1ByteRegister(SRC4392_I2C_SLAVE_ADDR, reg, val);
}

// Set the digital de-emphasis mode
// mode: DEEMPH_AUTO or DEEMPH_OFF
void set_deemphasis(uint8_t mode)
{
	if (mode != DEEMPH_AUTO && mode != DEEMPH_OFF)
		return;		// error checking

	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	if (mode == DEEMPH_AUTO) {
		src4392_write(SRC_REG2E, 0x20);
	}
	else if (mode == DEEMPH_OFF) {
		src4392_write(SRC_REG2E, 0x00);
	}
}

// Set the upsample rate
// rate: UPSAMPLE_192KHZ or UPSAMPLE_96KHZ
void set_upsample(uint8_t rate)
{
	if (rate != UPSAMPLE_192KHZ && rate != UPSAMPLE_96KHZ)
		return;		// error checking

    // mute audio
    
	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	if (rate == UPSAMPLE_192KHZ) {
		// SRC4392 DIT setup:
		// - SRC as the input data source
		// - MCLK as master clock
		// - clock divider 128 to set the output frame rate
		// - block start is an output and valid audio is indicated
		// - c and u data will not be updated
		src4392_write(SRC_REG07, 0x1c);

		// set up for 192KHz output 
		src4392_write(SRC_REG08, 0x08);
		src4392_write(SRC_REG7F, 0x02);
		src4392_write(0x00, 0x80);
		src4392_write(0x01, 0x80);
		src4392_write(0x08, 0x18);
		src4392_write(0x09, 0x18);
		src4392_write(SRC_REG7F, 0x00);
		src4392_write(SRC_REG08, 0x00);

		// SRC4392 Port A setup:
		// - MCLK as clock source
		// - clock divider 128
		src4392_write(SRC_REG04, 0x00);
	}
	else if (rate == UPSAMPLE_96KHZ) {
		// SRC4392 DIT setup:
		// - SRC as the input data source
		// - MCLK as master clock
		// - clock divider 256 to set the output frame rate
		// - block start is an output and valid audio is indicated
		// - c and u data will not be updated
		src4392_write(SRC_REG07, 0x3c);

		// set up for 96KHz output 
		src4392_write(SRC_REG08, 0x08);
		src4392_write(SRC_REG7F, 0x02);
		src4392_write(0x00, 0x80);
		src4392_write(0x01, 0x80);
		src4392_write(0x08, 0x08);
		src4392_write(0x09, 0x08);
		src4392_write(SRC_REG7F, 0x00);
		src4392_write(SRC_REG08, 0x00);

		// SRC4392 Port A setup:
		// - MCLK as clock source
		// - clock divider 256
		src4392_write(SRC_REG04, 0x01);
	}

	// Un-mute audio
}

// Set the DIT (digital output) routing
// input: input number, mode: DIT_LOOPOUT or DIT_UPSAMPLE
void set_dit_mode(uint8_t input, uint8_t mode)
{
	uint8_t	val;

	if ((mode != DIT_UPSAMPLE && mode != DIT_LOOPOUT) ||
	    input > MAX_INPUTS)
		return;		// error checking

	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	if (mode == DIT_UPSAMPLE) {
		if (upsample_rate == UPSAMPLE_192KHZ) {
			// DIT setup
			// - SRC as the input data source
			// - MCLK as master clock
			// - clock divider 128 to set the output frame rate
			// - block start is an output and valid audio
			//   is indicated
			// - c and u data will not be updated
			src4392_write(SRC_REG07, 0x1c);

			// set up for 192KHz output 
			src4392_write(SRC_REG08, 0x08);
			src4392_write(SRC_REG7F, 0x02);
			src4392_write(0x00, 0x80);
			src4392_write(0x01, 0x80);
			src4392_write(0x08, 0x18);
			src4392_write(0x09, 0x18);
			src4392_write(SRC_REG7F, 0x00);
			src4392_write(SRC_REG08, 0x00);
		}
		else if (upsample_rate == UPSAMPLE_96KHZ) {
			// DIT setup
			// - SRC as the input data source
			// - MCLK as master clock
			// - clock divider 256 to set the output frame rate
			// - block start is an output and valid audio
			//   is indicated
			// - c and u data will not be updated
			src4392_write(SRC_REG07, 0x3c);

			// set up for 96KHz output 
			src4392_write(SRC_REG08, 0x08);
			src4392_write(SRC_REG7F, 0x02);
			src4392_write(0x00, 0x80);
			src4392_write(0x01, 0x80);
			src4392_write(0x08, 0x08);
			src4392_write(0x09, 0x08);
			src4392_write(SRC_REG7F, 0x00);
			src4392_write(SRC_REG08, 0x00);
		}
	}
	else if (mode == DIT_LOOPOUT) {
		// set both AES and TX outputs to receive their
		// data via the bypass multiplexor without going
		// through the DIT block.
		val = (input) << 6 | 0x30;       
		src4392_write(SRC_REG08, val);
	}
}


// Set the input
// input: 0..4, mode: DIT_UPSAMPLE or DIT_LOOPOUT
void set_input(uint8_t input, uint8_t mode)
{
	uint8_t	val;

	if ((input > MAX_INPUTS) ||
	    (mode != DIT_UPSAMPLE && mode != DIT_LOOPOUT))
		return;		// error checking

	// Select page 0
	src4392_write(SRC_REG7F, 0x00);

    // - set DIR input source to the appropriate RX port
    // - use MCLK as clock source
    // - audio muted for loss of lock condition
    // - PLL free runs for loss of lock condition
    // - RXCKO output disabled
    val = 0x08 | input;
    src4392_write(SRC_REG0D, val);
    src4392_write(SRC_REG0E, 0x18);

    // set SRC input source to DIR
    src4392_write(SRC_REG2D, 0x02);

	// update DIT mode
	set_dit_mode(input, mode);
}

// Return the enum representing the current sample rate (SAMPLERATE_xxKHZ).
uint8_t get_sample_rate(void)
{
	uint8_t	val0, val1;

	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	val0 = src4392_read(SRC_REG32);
	val1 = src4392_read(SRC_REG33);

	if (upsample_rate == UPSAMPLE_192KHZ) {
		// for output sample rate = 192K
		if ((val0 == 0x07 && val1 == 0xff) ||
		    (val0 == 0x08 && val1 == 0x00)) {
			return SAMPLERATE_192KHZ;
		}
		else if (val0 == 0x07 && val1 == 0x59) {
			return SAMPLERATE_176KHZ;
		}
		else if (val0 == 0x05 && val1 == 0x55) {
			return SAMPLERATE_128KHZ;
		}
		else if ((val0 == 0x03 && val1 == 0xff) ||
			 (val0 == 0x04 && val1 == 0x00)) {
			return SAMPLERATE_96KHZ;
		}
		else if (val0 == 0x03 && val1 == 0xac) {
			return SAMPLERATE_88KHZ;
		}
		else if (val0 == 0x02 && val1 == 0xaa) {
			return SAMPLERATE_64KHZ;
		}
		else if ((val0 == 0x01 && val1 == 0xff) ||
			 (val0 == 0x02 && val1 == 0x00)) {
			return SAMPLERATE_48KHZ;
		}
		else if (val0 == 0x01 && val1 == 0xd6) {
			return SAMPLERATE_44KHZ;
		}
		else if (val0 == 0x01 && val1 == 0x55) {
			return SAMPLERATE_32KHZ;
		}
	}
	else if (upsample_rate == UPSAMPLE_96KHZ) {
		// for output sample rate of 96KHz
		if ((val0 == 0x0f && val1 == 0xff) ||
		    (val0 == 0x10 && val1 == 0x00)) {
			return SAMPLERATE_192KHZ;
		}
		else if (val0 == 0x0e && val1 == 0xb3) {
			return SAMPLERATE_176KHZ;
		}
		else if (val0 == 0x0a && val1 == 0xaa) {
			return SAMPLERATE_128KHZ;
		}
		else if ((val0 == 0x07 && val1 == 0xff) ||
			 (val0 == 0x08 && val1 == 0x00)) {
			return SAMPLERATE_96KHZ;
		}
		else if (val0 == 0x07 && val1 == 0x59) {
			return SAMPLERATE_88KHZ;
		}
		else if (val0 == 0x05 && val1 == 0x55) {
			return SAMPLERATE_64KHZ;
		}
		else if ((val0 == 0x03 && val1 == 0xff) ||
			 (val0 == 0x04 && val1 == 0x00)) {
			return SAMPLERATE_48KHZ;
		}
		else if (val0 == 0x03 && val1 == 0xac) {
			return SAMPLERATE_44KHZ;
		}
		else if (val0 == 0x02 && val1 == 0xaa) {
			return SAMPLERATE_32KHZ;
		}
	}

	return SAMPLERATE_UNKNOWN;
}


void init(void)
{   
    __delay_ms(100);
    RESET_SetLow();
    __delay_ms(100);
    RESET_SetHigh();
    __delay_ms(10);
	
    // Select page 0
	src4392_write(SRC_REG7F, 0x00);

	// DIR setup:
	// - set default input source
	// - use MCLK as clock source
	// - audio not muted for loss of lock condition
	// - PLL stops for loss of lock condition
	// - RXCKO output disabled
	src4392_write(SRC_REG0D, 0x08);	// default input source = RX1
	src4392_write(SRC_REG0E, 0x00);

	// PLL1 setup:
	// 24.576MHz, p = 2, j = 8, d = 0
	src4392_write(SRC_REG0F, 0x22);
	src4392_write(SRC_REG10, 0x00);
	src4392_write(SRC_REG11, 0x00);

	// Set GP01 for DIR non-audio flag
	src4392_write(SRC_REG1B, 0x06);
	// Set GP02 for DIR non-valid flag
	src4392_write(SRC_REG1C, 0x07);
	// Set GP03 for DIR emphasis flag
	src4392_write(SRC_REG1D, 0x05);
	// Set GP04 for DIR parity error flag
	src4392_write(SRC_REG1E, 0x0d);

	// SRC setup:
	// - DIR as the input data source
	// - use MCLK as clock source
	// - autodem enabled
	src4392_write(SRC_REG2D, 0x02);	// default input source = DIR
	src4392_write(SRC_REG2E, 0x20);
	src4392_write(SRC_REG2F, 0x00);
	src4392_write(SRC_REG30, 0x00);
	src4392_write(SRC_REG31, 0x00);

	// DIT setup:
	// - SRC as the input data source
	// - MCLK as master clock
	// - clock divider 128 to set the output frame rate
	// - block start is an output and valid audio is indicated
	// - c and u data will not be updated
	src4392_write(SRC_REG07, 0x1c);
	src4392_write(SRC_REG08, 0x00);
	src4392_write(SRC_REG09, 0x00);

	// set up for 192KHz output
	src4392_write(SRC_REG08, 0x08);
	src4392_write(SRC_REG7F, 0x02);
	src4392_write(0x00, 0x80);
	src4392_write(0x01, 0x80);
	src4392_write(0x08, 0x18);
	src4392_write(0x09, 0x18);
	src4392_write(SRC_REG7F, 0x00);
	src4392_write(SRC_REG08, 0x00);

	// Power up all blocks
	src4392_write(SRC_REG01, 0x3f);

	// Port A setup:
	// - master with i2s data format
	// - SRC as input data source
	// - MCLK as clock source
	// - clock divider 128
	src4392_write(SRC_REG03, 0x39);
	src4392_write(SRC_REG04, 0x00);

	// Port B setup:
	// - slave with i2s data format
	src4392_write(SRC_REG05, 0x01);
	src4392_write(SRC_REG06, 0x00);
}

/*
                         Main application
 */
void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();

    init();
    
    set_input(INPUT_RX1, DIT_UPSAMPLE);
    
    while (1) {
        __delay_ms(20);
    }
}
/**
 End of File
*/