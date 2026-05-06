/*
 * AK4118.c
 *
 *  Created on: Sep 21, 2023
 *      Author: User
 */


#include "AK4118.h"

extern I2C_HandleTypeDef hi2c3;
/**
 * @fn HAL_StatusTypeDef AK4118_Init(ak4118_dev_s*)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @return
 */
HAL_StatusTypeDef AK4118_Init(ak4118_dev_s *dev){
	HAL_StatusTypeDef status = HAL_ERROR;
	uint8_t rxBuffer[0x28] ={0};
	int counter = 0;
#ifdef USE_FREERTOS

#elif USE_THREADX
	tx_mutex_get(dev->mutex, TX_WAIT_FOREVER);
#endif
	while (status != HAL_OK){
	status = HAL_I2C_Mem_Read(dev->i2c_port, dev->DevAddr_read, CLK_PDN_Control_REG_ADDR,
			I2C_MEMADD_SIZE_8BIT, rxBuffer, 0x28, 1);
    counter++;
	}
#ifdef USE_FREERTOS

#elif USE_THREADX
	tx_mutex_put(dev->mutex);
#endif
	dev->regMap.CLK_PDN_Control.reg = rxBuffer[CLK_PDN_Control_REG_ADDR];
	dev->regMap.DATMask_DTSDetect.reg = rxBuffer[DATMask_DTSDetect_REG_ADDR];
	dev->regMap.INT0_Mask.reg = rxBuffer[INT0_Mask_REG_ADDR];
	dev->regMap.INT1_Mask.reg = rxBuffer[INT1_Mask_REG_ADDR];
	dev->regMap.IO_Control0.reg = rxBuffer[IO_Control0_REG_ADDR];
	dev->regMap.IO_Control1.reg = rxBuffer[IO_Control1_REG_ADDR];
	dev->regMap.Receiver_Status0.reg = rxBuffer[Receiver_Status0_REG_ADDR];
	dev->regMap.Receiver_Status1.reg = rxBuffer[Receiver_Status1_REG_ADDR];
	dev->regMap.RX_Detect.reg = rxBuffer[RX_Detect_REG_ADDR];
	dev->regMap.STC_DAT_Detect.reg = rxBuffer[STC_DAT_Detect_REG_ADDR];
	dev->regMap.Format_De_em_Control.reg = rxBuffer[Format_De_em_Control_REG_ADDR];
	dev->regMap.GPDR.reg = rxBuffer[GPDR_REG_ADDR];
	dev->regMap.GPE.reg = rxBuffer[GPE_REG_ADDR];
	dev->regMap.GPLDR.reg = rxBuffer[GPLR_REG_ADDR];
	dev->regMap.GPSCR.reg = rxBuffer[GPSCR_REG_ADDR];
	return status;
}

/**
 * @fn void AK4118_Set_Audio_Data_Format(ak4118_dev_s*, Audio_Data_Format_e)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @param format
 */
void AK4118_Set_Audio_Data_Format(ak4118_dev_s *dev, Audio_Data_Format_e format){
	dev->regMap.Format_De_em_Control.bits.DEM = format;
	AK4118_WriteRegister(dev, Format_De_em_Control_REG_ADDR, &dev->regMap.Format_De_em_Control.reg );
}

/**
 * @fn Sampling_Frequency_e AK4118_get_SamplingFrequency(ak4118_dev_s*)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @return
 */
Sampling_Frequency_e AK4118_get_SamplingFrequency(ak4118_dev_s *dev){
	AK4118_ReadRegister(dev,  Receiver_Status1_REG_ADDR, &dev->regMap.Receiver_Status1.reg);
	return dev->regMap.Receiver_Status1.bits.FS;
}

/**
 * @fn PLL_Lock_status_e AK4118_PLL_Lock_Status(ak4118_dev_s*)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @return
 */
PLL_Lock_status_e AK4118_PLL_Lock_Status(ak4118_dev_s *dev){
	AK4118_ReadRegister(dev, Receiver_Status0_REG_ADDR,  &dev->regMap.Receiver_Status0.reg);
	return dev->regMap.Receiver_Status0.bits.UNLCK;
}

/**
 * @fn void AK4118_Select_Input(ak4118_dev_s*, Input_Channel_e)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @param channel
 */
void AK4118_Select_Input(ak4118_dev_s * dev, Input_Channel_e channel ){
	dev->regMap.IO_Control1.bits.IPS = channel;
	AK4118_WriteRegister(dev, IO_Control1_REG_ADDR, &dev->regMap.IO_Control1.reg );
}

/**
 * @fn void AK4118_Set_MasterClock_Output(ak4118_dev_s*, Master_Clock_Out_e)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @param clock
 */
void AK4118_Set_MasterClock_Output(ak4118_dev_s *dev, Master_Clock_Out_e clock){
	dev->regMap.CLK_PDN_Control.bits.OCKS = clock;
	AK4118_WriteRegister(dev, CLK_PDN_Control_REG_ADDR, &dev->regMap.CLK_PDN_Control.reg );
}

/**
 * @fn HAL_StatusTypeDef AK4118_ReadRegister(ak4118_dev_s*, uint8_t, uint8_t*)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @param regAddr
 * @param reg
 * @return
 */
HAL_StatusTypeDef AK4118_ReadRegister(ak4118_dev_s *dev, uint8_t regAddr, uint8_t *reg){
	HAL_StatusTypeDef status;
#ifdef USE_FREERTOS

#elif USE_THREADX
	tx_mutex_get(dev->mutex, TX_WAIT_FOREVER);
#endif
	status = HAL_I2C_Mem_Read(dev->i2c_port, dev->DevAddr_read, regAddr,
			I2C_MEMADD_SIZE_8BIT, reg, 1, 100);
#ifdef USE_FREERTOS

#elif USE_THREADX
	tx_mutex_put(dev->mutex);
#endif
	return status;
}

/**
 * @fn HAL_StatusTypeDef AK4118_WriteRegister(ak4118_dev_s*, uint8_t, uint8_t*)
 * @brief
 *
 * @pre
 * @post
 * @param dev
 * @param regAddr
 * @param value
 * @return
 */
HAL_StatusTypeDef AK4118_WriteRegister(ak4118_dev_s *dev, uint8_t regAddr, uint8_t *value){
	HAL_StatusTypeDef status;
#ifdef USE_FREERTOS

#elif USE_THREADX
	tx_mutex_get(dev->mutex, TX_WAIT_FOREVER);
#endif
	status = HAL_I2C_Mem_Write(dev->i2c_port, dev->DevAddr_write, regAddr,
			I2C_MEMADD_SIZE_8BIT, value, 1, 100);
#ifdef USE_FREERTOS

#elif USE_THREADX
	tx_mutex_put(dev->mutex);
#endif
	return status;
}
