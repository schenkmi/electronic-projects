/**
 * PIC16F18056 based async sample rate converter
 * for CS8416 / AK4137
 *
 * Copyright (c) 2024-2024, Michael Schenk
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

#include "i2c.h"
#include "cs8416.h"

#include <stddef.h>

#define CS8416_I2C_SLAVE_ADDR     0x10 /* Page 34: [0010 AD2 AD1 AD0] added R(1) or /W(0) => 0x20 write, 0x21 read */

#define SPDIF_CONTROL0	0x00
#define SPDIF_CONTROL1	0x01
#define SPDIF_CONTROL2	0x02
#define SPDIF_CONTROL3	0x03
#define SPDIF_CONTROL4	0x04
#define SPDIF_SADF		0x05		// Serial Audio Data Format Register (05h)
#define SPDIF_REM		0x06		// Receiver Error Mask (06h)
#define SPDIF_IM		0x07		// Interrupt Mask (07h)
#define SPDIF_IMODE_MSB	0x08		// Interrupt Mode MSB (08h)
#define SPDIF_IMODE_LSB	0x09		// Interrupt Mode LSB (09h)
#define SPDIF_RCSTAT	0x0a		// Receiver Channel Status (0Ah)
#define SPDIF_FDSTAT	0x0b		// Format Detect Status (0Bh)
#define SPDIF_RERROR	0x0c		// Receiver Error (0Ch), see SPDIF_REM
#define SPDIF_INT1STAT	0x0d		// Interrupt 1 Status (0Dh)
#define SPDIF_QCHAN		0x0e		// Q-Channel Subcode spans between 0x0e to 0x17
#define SPDIF_ORMCK_RATIO	0x18	// OMCK/RMCK Ratio (18h)
#define SPDIF_CSR_A0	0x19		// Channel Status Registers for Channel A
#define SPDIF_CSR_B0	0x1e		// Channel Status Registers for Channel B
#define SPDIF_IEC61937BP 	0x23	// IEC61937 Burst Preamble (23h - 26h)
#define SPDIF_VREG		0x7f		// CS8416 I.D. and Version Register (7Fh)

// Bit definitions for SPDIF_CONTROL0
#define SPDIF_FSWCLK	6			// Forces the clock signal on OMCK to be output on RMCK regardless of the SWCLK
#define	SPDIF_PDUR		3			// Normal/High Update Rate phase detector
#define SPDIF_TRUNC		2			// Truncate incoming data

// Bit definitions for SPDIF_CONTROL1
#define	SPDIF_SWCLK		7			// Lets OMCK determine RMCK, OSCLK, OLRCLK when PLL loses lock
#define SPDIF_MUTESAO	6			// Mute control for the serial audio output port
#define SPDIF_INT1		5			// Interrupt output pin control
#define SPDIF_INT0		4			//
#define SPDIF_HOLD1		3			//	
#define SPDIF_HOLD0		2			// How received audio sample is affected if receiver error occurs
#define SPDIF_RMCKF		1			// 0: RMCK = 256*Fs, 1: RMCK = 128*Fs
#define SPDIF_CHS		0			// Receiver Channel Status register decoded from A(0) channel or B(1) channel

// Bit definitions for SPDIF_CONTROL2
#define SPDIF_DETCI		7 			// D to E status transfer inhibit
#define SPDIF_EMPH_CNTL2	6		// De-emphasis control
#define SPDIF_EMPH_CNTL1	5		//
#define SPDIF_EMPH_CNTL0	4		//
#define SPDIF_GPO0SEL3	3			// GPO0 source select
#define SPDIF_GPO0SEL2	2
#define SPDIF_GPO0SEL1	1
#define SPDIF_GPO0SEL0	0

// Bit definitions for SPDIF_CONTROL3
#define SPDIF_GPO1SEL3	7			// GPO1 source select
#define SPDIF_GPO1SEL2	6
#define SPDIF_GPO1SEL1	5
#define SPDIF_GPO1SEL0	4
#define SPDIF_GPO2SEL3	3			// GPO2 source select
#define SPDIF_GPO2SEL2	2
#define SPDIF_GPO2SEL1	1
#define SPDIF_GPO2SEL0	0

// Bit definitions for SPDIF_CONTROL4
#define SPDIF_RUN 		7			// 1 = power on
#define SPDIF_RXD		6
#define SPDIF_RXSEL0	3			// Selects RXP0 to RXP7 for input to the receiver
#define SPDIF_TXSEL0	0			// Selects RXP0 to RXP7 as the input for GPO TX source

// Bit definitions for SPDIF_SADF
#define SPDIF_SOMS		7
#define SPDIF_SOSF		6
#define	SPDIF_SORES1	5
#define SPDIF_SORES0	4
#define SPDIF_SOJUST	3
#define SPDIF_SODEL		2
#define SPDIF_SOSPOL	1
#define SPDIF_SOLRPOL	0

// Bit definitions for SPDIF_REM
// Bit definitions for SPDIF_RERROR
#define SPDIF_QCRC		6			// Q-subcode data CRC error
#define SPDIF_CCRC		5			// Channel Status Block CRC error
#define SPDIF_UNLOCK	4			// PLL out of lock
#define SPDIF_V			3			// Received AES3 Validity bit status (1 = Confidence error)
#define SPDIF_CONF		2			// Condidence error (UNLOCK || BIP)
#define SPDIF_BIP		1			// Bi-phase error bit
#define SPDIF_PAR		0			// Parity error

// Bit definitions for SPDIF_IM
#define SPDIF_PCCHM		6			// PC burst preamble change	
#define SPDIF_OSLIPM	5			// Serial audio output port data slip interrupt
#define SPDIF_DETCM		4			// Indicates the completion of a D to E C-buffer transfer
#define SPDIF_CCHM		3			// Indicates that the current 10 bytes of channel status is different from the previous 10 bytes
#define SPDIF_RERRM		2			// A receiver error has occurred
#define SPDIF_QCHM		1			// A new block of Q-subcode is available for reading
#define SPDIF_FCHM		0			// Format Change

// Bit definitions for SPDIF_IMODE_MSB/SPDIF_IMODE_LSB
#define SPDIF_PCCH1		6			
#define SPDIF_OSLIP1	5
#define SPDIF_DETC1		4
#define SPDIF_CCH1		3
#define SPDIF_RERR1		2
#define SPDIF_QCH1		1
#define SPDIF_FCH1		0

#define SPDIF_PCCH0		6			
#define SPDIF_OSLIP0	5
#define SPDIF_DETC0		4
#define SPDIF_CCH0		3
#define SPDIF_RERR0		2
#define SPDIF_QCH0		1
#define SPDIF_FCH0		0

// Bit definitions for SPDIF_RCSTAT
#define SPDIF_AUX3		7			// Auxilliary data length
#define SPDIF_AUX2		6
#define SPDIF_AUX1		5
#define SPDIF_AUX0		4
#define SPDIF_PRO		3			// Indicates professional format
#define SPDIF_COPY		2			// 1 = Copyright not asserted
#define SPDIF_ORIG		1			// 1 = Receiver data is original
#define SPDIF_EMPH		0			// 0 = 50uS/15uS pre-emphasis indicated

// Bit definitions for SPDIF_FDSTAT
#define SPDIF_PCM		6			// PCM data was detected
#define SPDIF_IEC61937	5			// IEC61937 data was detected
#define SPDIF_DTS_LD	4			// DTS_LD data was detected
#define SPDIF_DTS_CD	3			// DTS_CD data was detected
#define SPDIF_SIL		1			// Digital Silence was detected
#define SPDIF_96KHZ		0			// 0 = input sample rate <= 48kHz

// Bit definitions for SPDIF_INT1STAT
#define SPDIF_PCCH		6			
#define SPDIF_OSLIP		5
#define SPDIF_DETC		4
#define SPDIF_CCH		3
#define SPDIF_RERR		2
#define SPDIF_QCH		1
#define SPDIF_FCH		0

// Bit definitions for spdif_readStatus()
#define SPDIF_STATUS_SILENCE 	0			// digital silence detected
#define SPDIF_STATUS_PCM		1			// input data is in PCM format
#define SPDIF_CONFIDENCE_ERROR	2			// parity+biphase error
#define SPDIF_INTERRUPT			7

static CS8416_t* cs8416_instance = NULL;

/* Read one byte from the CS8416 via I2C */
static uint8_t cs8416_read(uint8_t reg)
{
  return I2C1_Read1ByteRegister(CS8416_I2C_SLAVE_ADDR, reg); 
}

/* Write one byte to the CS8416 via I2C */
static void cs8416_write(uint8_t reg, uint8_t val) {
    I2C1_Write1ByteRegister(CS8416_I2C_SLAVE_ADDR, reg, val);
}

void cs8416_init(CS8416_t* instance) {
    uint8_t reg = 0x00;
    
    cs8416_instance = instance;

    
    cs8416_write(SPDIF_CONTROL0, 0x00);
    
    // RMCKF[1] : 0 => RMCK output frequency is 256*FS.
    cs8416_write(SPDIF_CONTROL1, 0x00);
    // RMCKF[1] : 1 => RMCK output frequency is 128*FS.
    //cs8416_write(SPDIF_CONTROL1, 0x02); 
    
    // DETCI[7] : 0 => D to E status transfer inhibit allow update
    // EMPH_CNTL[2:0] : 0x4 => 50 ?s/15 ?s de-emphasis filter auto-select on.
    // GPO0SEL[3..0] : 0 => GPO0 Source select
    cs8416_write(SPDIF_CONTROL2, (0x04 << SPDIF_EMPH_CNTL0) |		// Automatic de-emphasis filter select
								 (0x00 << SPDIF_GPO0SEL0));		// GPO0 Source select

    cs8416_write(SPDIF_CONTROL3, 0x00);
   
    // Master mode, OSCLK & OLRCLK are outputs (I2S)
    // OSCLK frequency = 128*Fs
    cs8416_write(SPDIF_SADF, (1 << SPDIF_SOMS) | (1 << SPDIF_SOSF) |
                             (1 << SPDIF_SODEL) | (1 << SPDIF_SOLRPOL));

    switch(cs8416_instance->output_word_length) {
        case CS_OWLDirect:
            reg |= (0x3 << 4);
            break;
        case CS_OWL16Bit:
            reg |= (0x2 << 4);
            break;
        case CS_OWL20Bit:
            reg |= (0x1 << 4);
            break;
        case CS_OWL24Bit:
        default:
            reg |= (0x0 << 4);
            break;
    }

    switch(cs8416_instance->output_format) {
        case CS_MSB:
            /* Master, 128*Fs, 24Bit, Left Justified (LSB Justified) */
            reg |= ((1 << SPDIF_SOMS) | (1 << SPDIF_SOSF));
            break;
        case CS_LSB:
            /* Master, 128*Fs, 24Bit, Right Justified (MSB Justified) */
            reg |= ((1 << SPDIF_SOMS) | (1 << SPDIF_SOSF) | (1 << SPDIF_SOJUST));
            break;
        case CS_I2S:
        default:
            /* Master, 128*Fs, 24Bit, I2S */
            reg |= ((1 << SPDIF_SOMS) | (1 << SPDIF_SOSF) | (1 << SPDIF_SODEL) | (1 << SPDIF_SOLRPOL));
            break;
    }

    cs8416_write(SPDIF_SADF, reg);

	cs8416_write(SPDIF_REM, 0x7F);								// Enable all errors
	//cs8416_write(SPDIF_IM, _BV(SPDIF_RERRM) | _BV(SPDIF_FCHM));	// Enable error and format change interrupts

    // RUN[7] : 1
    // RXD[6] : 0
    // RXSEL[5..3] : input
    // TXSEL[2..0] : 0
    uint8_t val = (uint8_t)((1<<SPDIF_RUN) | ((0x00 /* input */ & 0x7) << SPDIF_RXSEL0) | (0x0 << SPDIF_TXSEL0));
    cs8416_write(SPDIF_CONTROL4, val);
}
