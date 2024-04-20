/* 
 * File:   i2c.h
 * Author: schenk
 *
 * Created on April 20, 2024, 7:12 PM
 */

#ifndef I2C_H
#define	I2C_H

#include <stdint.h>

#ifdef	__cplusplus
extern "C" {
#endif

uint8_t  I2C1_Read1ByteRegister(uint16_t address, uint8_t reg);
void I2C1_Write1ByteRegister(uint16_t address, uint8_t reg, uint8_t data);

#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

