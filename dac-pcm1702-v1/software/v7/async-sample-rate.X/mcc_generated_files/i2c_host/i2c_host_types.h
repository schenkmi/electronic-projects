/**
 * I2C Generated Driver Types Header File
 *
 * @file i2c_host_types.h
 *
 * @ingroup i2c_host_interface
 *
 * @brief This file contains additional data types for the I2C module.
 *
 * @version I2C Driver Version 2.1.0
 */

/*
© [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef I2C_HOST_TYPES_H
#define	I2C_HOST_TYPES_H

/**
 * @ingroup i2c_host_interface
 * @enum  i2c_host_error_t
 * @brief Enumeration for the I2C errors
 */
typedef enum
{
    I2C_ERROR_NONE,             /**< No error */
    I2C_ERROR_ADDR_NACK,        /**< Client returned address NACK */
    I2C_ERROR_DATA_NACK,        /**< Client returned data NACK */
    I2C_ERROR_BUS_COLLISION,    /**< Bus Collision error */
} i2c_host_error_t;

/**
 * @ingroup i2c_host_interface
 * @struct i2c_host_transfer_setup_t
 * @brief Structure for the I2C clock change
 */
typedef struct
{
  uint32_t clkSpeed;            /**< I2C Clock Speed */
} i2c_host_transfer_setup_t;

#endif // end of I2C_HOST_TYPES_H