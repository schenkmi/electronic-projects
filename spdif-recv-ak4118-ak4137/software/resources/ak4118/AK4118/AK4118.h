/*
 * AK4118.h
 *
 *  Created on: Sep 21, 2023
 *      Author: User
 */

#ifndef AK4118_AK4118_H_
#define AK4118_AK4118_H_

#include "main.h"
#ifdef USE_FREERTOS
#include "cmsis_os.h"
#elif USE_THREADX
  #include "app_threadx.h"
#endif

#define CLK_PDN_Control_REG_ADDR 		0x00
#define Format_De_em_Control_REG_ADDR	0x01
#define IO_Control0_REG_ADDR			0x02
#define IO_Control1_REG_ADDR			0x03
#define INT0_Mask_REG_ADDR				0x04
#define INT1_Mask_REG_ADDR				0x05
#define Receiver_Status0_REG_ADDR		0x06
#define Receiver_Status1_REG_ADDR		0x07
#define GPE_REG_ADDR					0x20
#define GPDR_REG_ADDR					0x21
#define GPSCR_REG_ADDR					0x22
#define GPLR_REG_ADDR					0x23
#define DATMask_DTSDetect_REG_ADDR		0x24
#define RX_Detect_REG_ADDR				0x25
#define STC_DAT_Detect_REG_ADDR			0x26

typedef union {
	struct {
		uint8_t RSTN:1;
		uint8_t PWN:1;
		uint8_t OCKS:2;
		uint8_t CM:2;
		uint8_t BCU:1;
		uint8_t CS12:1;
	}bits;
	uint8_t reg;
}CLK_PDN_Control_reg_u;

typedef union {
	struct {
		uint8_t DFS:1;
		uint8_t DEM:2;
		uint8_t DEAU:1;
		uint8_t DIF:3;
		uint8_t MONO:1;
	}bits;
	uint8_t reg;
}Format_and_De_em_Control_reg_u;

typedef union {
	struct {
		uint8_t OPS2_0:3;
		uint8_t TX0E:1;
		uint8_t OPS12_10:3;
		uint8_t TX1E:1;
	}bits;
	uint8_t reg;
}IO_Control0_reg_u;

typedef union {
	struct {
		uint8_t IPS:3;
		uint8_t DIT:1;
		uint8_t TLR:1;
		uint8_t UDIT:1;
		uint8_t EFH:2;
	}bits;
	uint8_t reg;
}IO_Control1_reg_u;

typedef union {
	struct {
		uint8_t MPAR0:1;
		uint8_t MAUD0:1;
		uint8_t MPE0:1;
		uint8_t MDTS0:1;
		uint8_t MULK0:1;
		uint8_t MCIT0:1;
		uint8_t MAUT0:1;
		uint8_t MQIT0:1;
	}bits;
	uint8_t reg;
}INT0_Mask_reg_u;

typedef union {
	struct {
		uint8_t MPAR1:1;
		uint8_t MAUD1:1;
		uint8_t MPE1:1;
	  uint8_t MDTS1:1;
	  uint8_t MULK1:1;
	  uint8_t MCIT1:1;
	  uint8_t MAUT1:1;
	  uint8_t MQIT1:1;
	}bits;
	uint8_t reg;
}INT1_Mask_reg_u;

typedef union {
	struct {
		uint8_t PAR:1;
		uint8_t AUDION:1;
		uint8_t PEM:1;
		uint8_t DTSCD:1;
		uint8_t UNLCK:1;
		uint8_t CINT:1;
		uint8_t AUTO:1;
		uint8_t QINT:1;
	}bits;
	uint8_t reg;
}Receiver_status0_reg_u;

typedef union {
	struct {
		uint8_t CCRC:1;
		uint8_t QCRC:1;
		uint8_t V:1;
		uint8_t unused:1;
		uint8_t FS:4;
	}bits;
	uint8_t reg;
}Receiver_status1_reg_u;

typedef union {
	struct {
		uint8_t DTS14:1;
		uint8_t DTS16:1;
		uint8_t DCNT:1;
		uint8_t EXCKMD:1;
		uint8_t FAST:1;
		uint8_t VINE:1;
		uint8_t RXDETE:1;
		uint8_t GPE:1;
	}bits;
	uint8_t reg;
}GPE_reg_u;

typedef union {
	struct {
		uint8_t IO0:1;
		uint8_t IO1:1;
		uint8_t IO2:1;
		uint8_t IO3:1;
		uint8_t IO4:1;
		uint8_t IO5:1;
		uint8_t IO6:1;
		uint8_t IO7:1;
	}bits;
	uint8_t reg;
}GPDR_reg_u;

typedef union {
	struct {
		uint8_t CS0:1;
		uint8_t CS1:1;
		uint8_t CS2:1;
		uint8_t CS3:1;
		uint8_t CS4:1;
		uint8_t CS5:1;
		uint8_t CS6:1;
		uint8_t CS7:1;
	}bits;
	uint8_t reg;
}GPSCR_reg_u;

typedef union {
	struct {
		uint8_t GPL0:1;
		uint8_t GPL1:1;
		uint8_t GPL2:1;
		uint8_t GPL3:1;
		uint8_t GPL4:1;
		uint8_t GPL5:1;
		uint8_t GPL6:1;
		uint8_t GPL7:1;
	}bits;
	uint8_t reg;
}GPLDR_reg_u;

typedef union {
	struct {
		uint8_t MDAT:2;
		uint8_t MSTC:2;
		uint8_t MDR0:1;
		uint8_t MED1:1;
		uint8_t DIV:1;
		uint8_t XMCK:1;
	}bits;
	uint8_t reg;
}DATmask_DTSdetect_reg_u;

typedef union {
	struct {
		uint8_t RXDE0:1;
		uint8_t RXDE1:1;
		uint8_t RXDE2:1;
		uint8_t RXDE3:1;
		uint8_t RXDE4:1;
		uint8_t RXDE5:1;
		uint8_t RXDE6:1;
		uint8_t RXDE7:1;
	}bits;
	uint8_t reg;
}RX_detect_reg_u;

typedef union {
	struct {
		uint8_t DAT:1;
		uint8_t STC:1;
		uint8_t unused:6;
	}bits;
	uint8_t reg;
}STC_DAT_detect_reg_u;

typedef struct {
	CLK_PDN_Control_reg_u CLK_PDN_Control;
	Format_and_De_em_Control_reg_u Format_De_em_Control;
	IO_Control0_reg_u IO_Control0;
	IO_Control1_reg_u IO_Control1;
	INT0_Mask_reg_u   INT0_Mask;
	INT1_Mask_reg_u   INT1_Mask;
	Receiver_status0_reg_u Receiver_Status0;
	Receiver_status1_reg_u Receiver_Status1;
	GPE_reg_u GPE;
	GPDR_reg_u GPDR;
	GPSCR_reg_u GPSCR;
	GPLDR_reg_u GPLDR;
	DATmask_DTSdetect_reg_u DATMask_DTSDetect;
	RX_detect_reg_u RX_Detect;
	STC_DAT_detect_reg_u STC_DAT_Detect;
}ak4118_register_map_s;

typedef struct {
	I2C_HandleTypeDef *i2c_port;
	uint8_t DevAddr_read;
	uint8_t DevAddr_write;
	ak4118_register_map_s regMap;
#ifdef USE_FREERTOS
	SemaphoreHandle_t *mutex;
#elif USE_THREADX
	TX_MUTEX *mutex;
#endif
}ak4118_dev_s;

typedef enum {
	FS_44_1KHz,
	reserved,
	FS_48KHz,
	FS_32KHz,
	FS_22_05KHz,
	FS_11_O25KHz,
	FS_24KHz,
	FS_16KHz,
	FS_88_2KHz,
	FS_8KHz,
	FS_96KHz,
	FS_64KHz,
	FS_176_4KHz,
	FS_192KHz
}Sampling_Frequency_e;

typedef enum {
	RX0,
	RX1,
	RX2,
	RX3,
	RX4,
	RX5,
	RX6,
	RX7
}Input_Channel_e;

typedef enum {
	MCO_96KHz_Default,
	MCO_96KHz,
	MCO_48KHz,
	MCO_192KHz
}Master_Clock_Out_e;

typedef enum {
	PLL_LOCK,
	PLL_UNLOCK
}PLL_Lock_status_e;

typedef enum {
	Out_16bit_right_just,
	Out_18bit_right_just,
	Out_20bit_right_just,
	Out_24bit_right_just,
	Out_24bit_left_just,
	Out_24bit_I2S_64fs,
	In_24bit_left_64_128fs,
	In_24bit_I2S_64_128fs
}Audio_Data_Format_e;

HAL_StatusTypeDef AK4118_Init(ak4118_dev_s *dev);
HAL_StatusTypeDef AK4118_ReadRegister(ak4118_dev_s *dev, uint8_t regAddr, uint8_t *reg);
HAL_StatusTypeDef AK4118_WriteRegister(ak4118_dev_s *dev, uint8_t regAddr, uint8_t *value);
Sampling_Frequency_e AK4118_get_SamplingFrequency(ak4118_dev_s *dev);
void AK4118_Select_Input(ak4118_dev_s * dev, Input_Channel_e channel );
void AK4118_Set_MasterClock_Output(ak4118_dev_s *dev, Master_Clock_Out_e clock);
PLL_Lock_status_e AK4118_PLL_Lock_Status(ak4118_dev_s *dev);
void AK4118_Set_Audio_Data_Format(ak4118_dev_s *dev, Audio_Data_Format_e format);
#endif /* AK4118_AK4118_H_ */
