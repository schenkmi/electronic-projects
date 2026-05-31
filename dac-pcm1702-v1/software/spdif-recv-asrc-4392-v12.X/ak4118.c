/**
 * PIC16F18056 based async sample rate converter
 * for AK4118 / AK4137
 *
 * Copyright (c) 2026-2026, Michael Schenk
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
#include "ak4118.h"
#include "mcc_generated_files/system/system.h"
#include <stddef.h>

#define AK4118_I2C_SLAVE_ADDR       0x10

#define AK4118_REG_CLK_PWR_CTL		0x00
#define AK4118_REG_FORMAT_CTL		0x01
#define AK4118_REG_FORMAT_CTL_DIF0	4
#define AK4118_REG_IO_CTL0		    0x02
#define AK4118_REG_IO_CTL1		    0x03
#define AK4118_IPS0                 0
#define AK4118_REG_INT0_MASK		0x04
#define AK4118_REG_INT1_MASK		0x05
#define AK4118_REG_RCV_STATUS0		0x06
#define AK4118_REG_RCV_STATUS1		0x07
#define AK4118_REG_RXCHAN_STATUS0	0x08
#define AK4118_REG_RXCHAN_STATUS1	0x09
#define AK4118_REG_RXCHAN_STATUS2	0x0a
#define AK4118_REG_RXCHAN_STATUS3	0x0b
#define AK4118_REG_RXCHAN_STATUS4	0x0c
#define AK4118_REG_TXCHAN_STATUS0	0x0d
#define AK4118_REG_TXCHAN_STATUS1	0x0e
#define AK4118_REG_TXCHAN_STATUS2	0x0f
#define AK4118_REG_TXCHAN_STATUS3	0x10
#define AK4118_REG_TXCHAN_STATUS4	0x11
#define AK4118_REG_BURST_PREAMB_PC0	0x12
#define AK4118_REG_BURST_PREAMB_PC1	0x13
#define AK4118_REG_BURST_PREAMB_PD0	0x14
#define AK4118_REG_BURST_PREAMB_PD1	0x15
#define AK4118_REG_QSUB_CTL		    0x16
#define AK4118_REG_QSUB_TRACK		0x17
#define AK4118_REG_QSUB_INDEX		0x18
#define AK4118_REG_QSUB_MIN		    0x19
#define AK4118_REG_QSUB_SEC		    0x1a
#define AK4118_REG_QSUB_FRAME		0x1b
#define AK4118_REG_QSUB_ZERO		0x1c
#define AK4118_REG_QSUB_ABS_MIN		0x1d
#define AK4118_REG_QSUB_ABS_SEC		0x1e
#define AK4118_REG_QSUB_ABS_FRAME	0x1f
#define AK4118_REG_GPE			    0x20
#define AK4118_REG_GPDR			    0x21
#define AK4118_REG_GPSCR		    0x22
#define AK4118_REG_GPLR			    0x23
#define AK4118_REG_DAT_MASK_DTS		0x24
#define AK4118_REG_RX_DETECT		0x25
#define AK4118_REG_STC_DAT_DETECT	0x26
#define AK4118_REG_RXCHAN_STATUS5	0x27
#define AK4118_REG_TXCHAN_STATUS5	0x28
#define AK4118_REG_MAX			    0x29

#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))

typedef struct {
    uint8_t reg;
    uint8_t val;
} RegisterDefault_t;

static const RegisterDefault_t ak4118_reg_defaults[] = {
	{AK4118_REG_CLK_PWR_CTL,    0x63}, // 0100 1111 CM1=0, CM0=0, OCKS1=1, OCKS0=1
	{AK4118_REG_FORMAT_CTL,     0x5A}, // 0101 1010
	{AK4118_REG_IO_CTL0,        0x88},
	{AK4118_REG_IO_CTL1,        0x48},
	{AK4118_REG_INT0_MASK,      0xee},
	{AK4118_REG_INT1_MASK,      0xb5},
	{AK4118_REG_GPE,            0x77},
	{AK4118_REG_GPDR,           0x00},
	{AK4118_REG_GPSCR,          0x00},
	{AK4118_REG_GPLR,           0x00},
	{AK4118_REG_DAT_MASK_DTS,   0x3f},
	{AK4118_REG_RX_DETECT,      0xff},
	{AK4118_REG_STC_DAT_DETECT, 0x03},
	{AK4118_REG_TXCHAN_STATUS5, 0x20},
};

static AK4118_t* ak4118_instance = NULL;

/* Read one byte from the AK4118 via I2C */
static uint8_t ak4118_read(uint8_t reg)
{
    uint8_t data;
    I2C1_Read1ByteRegister(AK4118_I2C_SLAVE_ADDR, reg, &data); 
    return data;
}

/* Write one byte to the AK4118 via I2C */
static void ak4118_write(uint8_t reg, uint8_t val) {
    I2C1_Write1ByteRegister(AK4118_I2C_SLAVE_ADDR, reg, val);
}

/* Initialize AK4118 */
void ak4118_init(AK4118_t* instance) {
    ak4118_instance = instance;

    for(uint8_t cnt = 0; cnt < ARRAY_SIZE(ak4118_reg_defaults); cnt++) {
        RegisterDefault_t reg_def = ak4118_reg_defaults[cnt];

        if (reg_def.reg == AK4118_REG_FORMAT_CTL) {
            reg_def.val &= ~(0x07 << AK4118_REG_FORMAT_CTL_DIF0);
            reg_def.val |= ((instance->data_format & 0x07) << AK4118_REG_FORMAT_CTL_DIF0);
        }

        ak4118_write(reg_def.reg, reg_def.val);   
    }
}

/* select input */
void ak4118_set_input(int input) {
    // IPS2[2..0] : input
    uint8_t val = ak4118_read(AK4118_REG_IO_CTL1);   
    val &= ~(0x07 << AK4118_IPS0);
    val |= ((input & 0x07) << AK4118_IPS0);
    ak4118_write(AK4118_REG_IO_CTL1, val);
}

/* print samplrate */
void ak4118_print_samplerate(void) {
    if (ak4118_instance) {
        uint8_t sample_rate = (ak4118_read(AK4118_REG_RCV_STATUS1 /*0x07*/) & 0xf0);
        if (sample_rate != ak4118_instance->previous.sampling_rate) {
            printf("Sampling rate : ");
            switch (sample_rate) {
                case 0x10:
                  printf("Reserved\r\n");
                  break;
                case 0x00:
                  printf("44.1KHz\r\n");
                  break;
                case 0x20:
                  printf("48KHz\r\n");
                  break;
                case 0x80:
                  printf("88.2KHz\r\n");
                  break;
                case 0xa0:
                  printf("96KHz\r\n");
                  break;
                case 0xc0:
                  printf("176.4KHz\r\n");
                  break;
                case 0xe0:
                  printf("192KHz\r\n");
                  break;
            }

            ak4118_instance->previous.sampling_rate = sample_rate;
        }
    }
}

/* print SPDIF status */
void ak4118_print_spdif_status(void) {
    if (ak4118_instance) {
        uint8_t status = ak4118_read(AK4118_REG_RCV_STATUS0 /*0x06*/);
        if (status != ak4118_instance->previous.status_register) {
            printf("Status : \r\n");
            printf("Parity Error or Biphase Error Status: %s\r\n", (status & 0x01) ? "Error" : "No Error");   
            printf("Audio Bit Output: %s\r\n", (status & 0x02) ? "Non Audio" : "Audio");  
            printf("Pre-emphasis Detect: %s\r\n", (status & 0x04) ? "ON" : "OFF");  
            printf("DTS-CD Auto Detect: %s\r\n", (status & 0x08) ? "Detect" : "No detect"); 
            printf("PLL Lock Status: %s\r\n", (status & 0x10) ? "Unlocked" : "Locked"); 
            printf("Channel Status Buffer Interrupt: %s\r\n", (status & 0x20) ? "Changed" : "No change"); 
            printf("Non-PCM Auto Detect: %s\r\n", (status & 0x40) ? "Detect" : "No detect"); 
            printf("Q-subcode Buffer Interrupt: %s\r\n", (status & 0x80) ? "Changed" : "No change");

            ak4118_instance->previous.status_register = status;
        }  
    }
}

/* print selexted input */
void ak4118_print_input(void) {
    if (ak4118_instance) {
        uint8_t input = ak4118_read(AK4118_REG_IO_CTL1) & 0x07;
        if (input != ak4118_instance->previous.input) {
            printf("Using input : RX%u\r\n", input);

            ak4118_instance->previous.input = input;
        }  
    }
}