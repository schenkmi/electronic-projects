/**
 * PIC16F18446 based async sample rate converter
 * for TI/BB SRC4392/SRC4382
 * PCM1792A
 *
 * Copyright (c) 2021-2024, Michael Schenk
 * All Rights Reserved
 *
 * Author: Michael Schenk
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * OEMs, ISVs, VARs and other distributors that combine and distribute
 * commercially licensed software with Michael Schenks software
 * and do not wish to distribute the source code for the commercially
 * licensed software under version 2, or (at your option) any later
 * version, of the GNU General Public License (the "GPL") must enter
 * into a commercial license agreement with Michael Schenk.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file LICENSE.txt. If not, write to
 * the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * http://www.gnu.org/licenses/gpl-2.0.html
 */

#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "src4392.h"





// Page 38 
#define SRC4392_I2C_SLAVE_ADDR              0x70   /* 1110000 R(1) or /W(0) => 0xe0 write, 0xe1 read */


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

#define   SRC_REG2D_SRCIS (0x3 << 0) 
#define   SRC_REG2D_SRCIS_DIR (0x2 << 0)


#define   SRC_REG2D_MUTE (1 << 4)


#define SRC_REG2E	0x2e		// SRC control
#define SRC_REG2F	0x2f		// SRC control
#define SRC_REG30	0x30		// SRC control attenuation left channel 0.5dB
#define SRC_REG31	0x31		// SRC control attenuation right channel 0.5dB
#define SRC_REG32	0x32		// SRC input/output ratio
#define SRC_REG33	0x33		// SRC input/output ratio
#define SRC_REG7F	0x7f		// page selection


//
//// Sample rate enums
//#define SAMPLERATE_UNKNOWN	0	// unknown
//#define SAMPLERATE_32KHZ	1	// 32.0KHz
//#define SAMPLERATE_44KHZ	2	// 44.1KHz
//#define SAMPLERATE_48KHZ	3	// 48.0KHz
//#define SAMPLERATE_64KHZ	4	// 64.0KHz
//#define SAMPLERATE_88KHZ	5	// 88.2KHz
//#define SAMPLERATE_96KHZ	6	// 96.0KHz
//#define SAMPLERATE_128KHZ	7	// 128.0KHz
//#define SAMPLERATE_176KHZ	8	// 176.4KHz
//#define SAMPLERATE_192KHZ	9	// 192.0KHz

/*
 * Upsampling enums
 */
//#define UPSAMPLE_192KHZ		0	// 192KHz
//#define UPSAMPLE_96KHZ		1	// 96KHz



//uint8_t		upsample_rate = UPSAMPLE_192KHZ;
//uint8_t		dit_mode = DIT_UPSAMPLE;


// input 0,1,2 or 3

//#define INPUT_RX1   0
//#define INPUT_RX2   1
//#define INPUT_RX3   2
//#define INPUT_RX4   3
#define MAX_INPUTS  4

//#define SRC_OUTPUT_BITS 20
//#define SRC_OUTPUT_BITS 24


static SRC4392_t* src4392_instance = NULL;

// Read one byte from the SRC4392
static uint8_t src4392_read(uint8_t reg)
{
  return I2C1_Read1ByteRegister(SRC4392_I2C_SLAVE_ADDR, reg); 
}


// Write one byte to the SRC4392
static void src4392_write(uint8_t reg, uint8_t val)
{
    I2C1_Write1ByteRegister(SRC4392_I2C_SLAVE_ADDR, reg, val);
}



// Set the digital de-emphasis mode
static void set_deemphasis(SRC4392_t* instance)
{
    if (instance) {
        // Select SRC4392 page 0
        src4392_write(SRC_REG7F, 0x00);

        if (instance->deemphases == DeEmphasisAuto) {
            src4392_write(SRC_REG2E, 0x20);
        }
        else if (instance->deemphases == DeEmphasisOff) {
            src4392_write(SRC_REG2E, 0x00);
        }
    }
}

// Set the upsample rate
// rate: UpsamplingTo192kHz or UpsamplingTo96kHz
static void set_upsample(SRC4392_t* instance)
{
    if (instance) {
    
        // mute audio

        // Select SRC4392 page 0
        src4392_write(SRC_REG7F, 0x00);

        if (instance->upsample_rate == UpsamplingTo192kHz) {
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
        else if (instance->upsample_rate == UpsamplingTo96kHz) {
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
}


// Set the DIT (digital output) routing
// input: input number, mode: DIT_LOOPOUT or DIT_UPSAMPLE
static void set_dit_mode(SRC4392_t* instance, int input)
{
    if (instance && (input < MAX_INPUTS)) {
        uint8_t	val;

        // Select SRC4392 page 0
        src4392_write(SRC_REG7F, 0x00);

        if (instance->digital_audio_interface_transmitter == DITUpsample) {
            if (instance->upsample_rate == UpsamplingTo192kHz) {
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
            else if (instance->upsample_rate == UpsamplingTo96kHz) {
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
        else if (instance->digital_audio_interface_transmitter == DITPassthrough) {
            // set both AES and TX outputs to receive their
            // data via the bypass multiplexor without going
            // through the DIT block.
            val = (uint8_t)((input) << 6 | 0x30);       
            src4392_write(SRC_REG08, val);
        }
    }
}

// Set the input
// input: 0..4, mode: DIT_UPSAMPLE or DIT_LOOPOUT
//void set_input(uint8_t input, enum SRC4392DigitalAudioInterfaceTransmitter dit)


void src4392_set_input(int input)
{
    if (src4392_instance && (input < MAX_INPUTS)) {
        uint8_t	val;
        
        // Select page 0
        src4392_write(SRC_REG7F, 0x00);

        // - set DIR input source to the appropriate RX port
        // - use MCLK as clock source
        // - audio muted for loss of lock condition
        // - PLL free runs for loss of lock condition
        // - RXCKO output disabled
        val = 0x08 | (uint8_t)input;
        src4392_write(SRC_REG0D, val);
        src4392_write(SRC_REG0E, 0x18);

        // set SRC input source to DIR
        val = src4392_read(SRC_REG2D);
       // val &= ~SRC_REG2D_SRCIS;
      //  val |= SRC_REG2D_SRCIS_DIR;
        
        val = ((val & ~SRC_REG2D_SRCIS) | SRC_REG2D_SRCIS_DIR);
        
        
        
        src4392_write(SRC_REG2D, val);

        // update DIT mode
        set_dit_mode(src4392_instance, input);       
    }
}

void src4392_set_attenuation(int right, int left)
{
    uint8_t right_att = (right < 0) ? 0 : (right > 0xff) ? 0xff : (uint8_t)right;
    uint8_t left_att = (left < 0) ? 0 : (left > 0xff) ? 0xff : (uint8_t)left;
    
    // Select SRC4392 page 0
    src4392_write(SRC_REG7F, 0x00);   
    // Output Attenuation (dB) = ?N × 0.5, where N = AL[7:0]DEC.
    src4392_write(SRC_REG30, left_att);
    // Output Attenuation (dB) = ?N × 0.5, where N = AR[7:0]DEC.
    src4392_write(SRC_REG31, right_att);
}

void src4392_mute(bool mute) {
     // Select SRC4392 page 0
    src4392_write(SRC_REG7F, 0x00);
    
    
    uint8_t	val = src4392_read(SRC_REG2D);
    
    if (mute) {
        val |= SRC_REG2D_MUTE;
    } else {
        val &= ~SRC_REG2D_MUTE; 
    }
    src4392_write(SRC_REG2D, val);
}

// Return the enum representing the current sample rate (SAMPLERATE_xxKHZ).
enum SRC4392SamplingRate src4392_get_sample_rate(void)
{
	if (src4392_instance) {
        uint8_t	val0, val1;

        // Select SRC4392 page 0
        src4392_write(SRC_REG7F, 0x00);

        val0 = src4392_read(SRC_REG32);
        val1 = src4392_read(SRC_REG33);

        if (src4392_instance->upsample_rate == UpsamplingTo192kHz) {
            // for output sample rate = 192K
            if ((val0 == 0x07 && val1 == 0xff) ||
                (val0 == 0x08 && val1 == 0x00)) {
                return SamplingRate192_kHz;
            }
            else if (val0 == 0x07 && val1 == 0x59) {
                return SamplingRate176_4_kHz;
            }
            else if (val0 == 0x05 && val1 == 0x55) {
                return SamplingRate128_kHz;
            }
            else if ((val0 == 0x03 && val1 == 0xff) ||
                 (val0 == 0x04 && val1 == 0x00)) {
                return SamplingRate96_kHz;
            }
            else if (val0 == 0x03 && val1 == 0xac) {
                return SamplingRate88_2_kHz;
            }
            else if (val0 == 0x02 && val1 == 0xaa) {
                return SamplingRate64_kHz;
            }
            else if ((val0 == 0x01 && val1 == 0xff) ||
                 (val0 == 0x02 && val1 == 0x00)) {
                return SamplingRate48_kHz;
            }
            else if (val0 == 0x01 && val1 == 0xd6) {
                return SamplingRate44_1_kHz;
            }
            else if (val0 == 0x01 && val1 == 0x55) {
                return SamplingRate32_kHz;
            }
        }
        else if (src4392_instance->upsample_rate == UpsamplingTo96kHz) {
            // for output sample rate of 96KHz
            if ((val0 == 0x0f && val1 == 0xff) ||
                (val0 == 0x10 && val1 == 0x00)) {
                return SamplingRate192_kHz;
            }
            else if (val0 == 0x0e && val1 == 0xb3) {
                return SamplingRate176_4_kHz;
            }
            else if (val0 == 0x0a && val1 == 0xaa) {
                return SamplingRate128_kHz;
            }
            else if ((val0 == 0x07 && val1 == 0xff) ||
                 (val0 == 0x08 && val1 == 0x00)) {
                return SamplingRate96_kHz;
            }
            else if (val0 == 0x07 && val1 == 0x59) {
                return SamplingRate88_2_kHz;
            }
            else if (val0 == 0x05 && val1 == 0x55) {
                return SamplingRate64_kHz;
            }
            else if ((val0 == 0x03 && val1 == 0xff) ||
                 (val0 == 0x04 && val1 == 0x00)) {
                return SamplingRate48_kHz;
            }
            else if (val0 == 0x03 && val1 == 0xac) {
                return SamplingRate44_1_kHz;
            }
            else if (val0 == 0x02 && val1 == 0xaa) {
                return SamplingRate32_kHz;
            }
        }
    }
	return SamplingRateUnknown;
}

void src4392_init(SRC4392_t* instance) {
    src4392_instance = instance;
    
    
        // Select page 0
	src4392_write(SRC_REG7F, 0x00);

	// DIR setup:
	// - set default input source
	// - use MCLK as clock source
	// - audio not muted for loss of lock condition
	// - PLL stops for loss of lock condition
	// - RXCKO output disabled
    
    // 000010 00
    // 00 => RXMUX1 / RXMUX0 => (RX1)
    // 0
    // 1 => RXCLK => MCLK
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


    switch (instance->output_word_length) {
        case OWL20Bit:
            src4392_write(SRC_REG2F, 0x40); // SRC output 20 Bit
            break;
        case OWL18Bit:
            src4392_write(SRC_REG2F, 0x80); // SRC output 18 Bit
            break;  
        case OWL16Bit:
            src4392_write(SRC_REG2F, 0xc0); // SRC output 16 Bit
            break; 
        default:
             src4392_write(SRC_REG2F, 0x00); // SRC output 24 Bit
            break;
    }
    
	src4392_write(SRC_REG30, 0x00);
	src4392_write(SRC_REG31, 0x00);

	// DIT setup:
	// - SRC as the input data source
	// - MCLK as master clock
	// - clock divider 128 to set the output frame rate
	// - block start is an output and valid audio is indicated
	// - c and u data will not be updated
    
    // 0x1c => 0001'1100
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
    
 
    set_deemphasis(instance);
    set_upsample(instance);
}

void src4392_test() {
    
    uint8_t	val = src4392_read(SRC_REG2D);
}

