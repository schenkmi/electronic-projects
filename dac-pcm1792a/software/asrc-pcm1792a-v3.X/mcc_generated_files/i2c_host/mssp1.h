/**
 * MSSP1 Generated Driver API Header File
 *
 * @file mssp1.h
 *
 * @defgroup i2c_host I2C1_HOST
 *
 * @brief This file contains API prototypes and other data types for the I2C1 module.
 *
 * @version I2C1 Driver Version 2.1.1
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

#ifndef MSSP1_H
#define MSSP1_H

/**
  Section: Included Files
 */

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "i2c_host_event_types.h"
#include "i2c_host_interface.h"

/**
 Section: Data Type Definitions
 */
#define i2c1_host_host_interface I2C1_Host


#define I2C1_Host_Initialize I2C1_Initialize
#define I2C1_Host_Deinitialize I2C1_Deinitialize
#define I2C1_Host_Write I2C1_Write
#define I2C1_Host_Read I2C1_Read
#define I2C1_Host_WriteRead I2C1_WriteRead
#define I2C1_Host_ErrorGet I2C1_ErrorGet
#define I2C1_Host_CallbackRegister I2C1_CallbackRegister
#define I2C1_Host_IsBusy I2C1_IsBusy


/**
 * @ingroup i2c_host
 * @brief External object for I2C1_Host.
 */
extern const i2c_host_interface_t I2C1_Host;

/**
 * @ingroup i2c_host
 * @brief Initializes the I2C1 driver and module.
 *        This routine must be called only once and before any other I2C1 routine is called.
 * @param None.
 * @return None.
 */
void I2C1_Initialize(void);

/**
 * @ingroup i2c_host
 * @brief Deinitializes the I2C1 driver.
 *        It disables the I2C1 module.
 * @param None.
 * @return None.
 */
void I2C1_Deinitialize(void);

/**
 * @ingroup i2c_host
 * @brief Writes data to a Client on the bus.
 *        The function will attempt to write the length number of bytes from the data
 *        buffer to a Client whose address is specified by the address argument.
 *        The I2C Host generates a Start condition, writes the data and then
 *        generates a Stop condition. If the Client NAKs the request or a bus 
 *        error was encountered, the transfer is terminated.
 *        The application can call the I2C1_ErrorGet() function to
 *        discover the cause of the error.
 *
 *        The function is non-blocking. It initiates bus activity and returns
 *        immediately. The transfer is then completed in the peripheral 
 *        interrupt. For the Polling mode, the user has to call  I2C1_Tasks
 *        in the while loop. A transfer request cannot be placed when another 
 *        transfer is in progress. Calling this function when another function 
 *        is already in progress will cause the function to return false.
 *
 * @param [in] address - 7-bit / 10-bit Client address.
 * @param [in] data - pointer to the source data buffer that contains the data to
 *                    be transmitted.
 * @param [in] dataLength - length of the data buffer in number of bytes. Also the
 *                          number of bytes to be written.
 * 
 * @retval true  - The request was placed successfully and the bus activity was
 *                 initiated.
 * @retval false - The request fails, if there was already a transfer in
 *                 progress when this function was called.
 */
bool I2C1_Write(uint16_t address, uint8_t *data, size_t dataLength);

/**
 * @ingroup i2c_host
 * @brief Reads the data from a Client on the bus.
 *        The function will attempt to read the length number of bytes into the data
 *        buffer from a Client whose address is specified by the address argument. 
 *        The I2C Host generates a Start condition, reads the data and then 
 *        generates a Stop condition. If the Client NAKs the request or a bus 
 *        error is encountered, the transfer is terminated. 
 *        The application will call I2C1_ErrorGet() function to
 *        discover the cause of the error.
 *
 *        The function is non-blocking. It initiates the bus activity and returns
 *        immediately. The transfer is then completed in the peripheral 
 *        interrupt. For the Polling mode, the user has to call  I2C1_Tasks
 *        in the while loop. A transfer request cannot be placed when another 
 *        transfer is in progress. Calling this function when another function 
 *        is already in progress will cause the function to return false.
 *
 * @param [in] address - 7-bit / 10-bit Client address.
 * @param [out] data - pointer to the destination data buffer that contains the data to
 *                    be received.
 * @param [in] dataLength - length of the data buffer in number of bytes. Also the
 *                          number of bytes to be read.
 *
 * @retval true  - The request was placed successfully and the bus activity was
 *                 initiated.
 * @retval false - The request fails, if there was already a transfer in
 *                 progress when this function was called.
 */
bool I2C1_Read(uint16_t address, uint8_t *data, size_t dataLength);

/**
 * @ingroup i2c_host
 * @brief Writes data from the writeData function to the bus 
 *        and then reads the data from the Client. After that, it stores the received data in the
 *        readData parameter. The function generates a Start condition on the bus and 
 *        sends the writeLength number of bytes contained in the writeData. 
 *        The function will then insert a Repeated Start condition and 
 *        proceed to read the readLength number of bytes from the client.
 *        The received bytes are stored in the readData buffer. A Stop condition 
 *        is generated after the last byte has been received.
 *
 *        If the Client NAKs the request or a bus error was encountered on 
 *        the bus, the transfer is terminated. The application will call the
 *        I2C1_ErrorGet() function to know that the cause of the error.
 *
 *        The function is non-blocking. It initiates the bus activity and returns
 *        immediately. The transfer is then completed in the peripheral 
 *        interrupt. For the Polling mode, the user has to call I2C1_Tasks
 *        in the while loop. A transfer request cannot be placed when another 
 *        transfer is in progress. Calling this function when another function 
 *        is already in progress will cause the function to return false.
 *
 * @param [in] address     - 7-bit / 10-bit Client address.
 * @param [in] writeData   - pointer to write data buffer.
 * @param [in] writeLength - write data length in bytes.
 * @param [out] readData    - pointer to read data buffer.
 * @param [in] readLength  - read data length in bytes.
 * 
 * @retval true  - The request was placed successfully and the bus activity was
 *                 initiated.
 * @retval false - The request fails, if there was already a transfer in
 *                 progress when this function was called.
 */
bool I2C1_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength);

/**
 * @ingroup i2c_host
 * @brief Gets the error occurred during the I2C Transmit and Receive.
 *        
 * @param None.
 * @retval I2C_ERROR_NONE - No Error
 * @retval I2C_ERROR_NACK - Client returned NACK
 * @retval I2C_ERROR_BUS_COLLISION - Bus Collision Error
 */
i2c_host_error_t I2C1_ErrorGet(void);

/**
 * @ingroup i2c_host
 * @brief Checks if the I2C is busy.
 *        The I2C must be initialized with @ref I2C1_Initialize() 
 *        before calling this API.
 * @param None.
 * @retval true - if I2C is busy.
 * @retval false - if I2C is free.
 */
bool I2C1_IsBusy(void);

/**
 * @ingroup i2c_host
 * @brief Setter function for the I2C interrupt callback. This will be called when any error is generated.
 * @param CallbackHandler - Pointer to custom Callback.
 * @return None.
 *
 * @code
 * void customI2CCallback(void)
 * {
 *    // Custom ISR code
 * }
 *
 * void main(void)
 * {
 *     SYSTEM_Initialize();
 *     I2C1_Initialize();
 *     I2C1_CallbackRegister(customI2CCallback);
 *     while (!I2C1_WriteRead(0x50, writeData, 1, readData , 2));
 *
 *     while (1)
 *     {
 *     }
 * }
 * @endcode
 */
void I2C1_CallbackRegister(void (*callbackHandler)(void));

/**
 * @ingroup i2c_host
 * @brief Interrupt Service Routine (ISR) for I2C1 common interrupts.
 * @param None.
 * @return None.
 */
void I2C1_ISR(void);

/**
 * @ingroup i2c_host
 * @brief ISR function for I2C1 error interrupts.
 * @param None.
 * @return None.
 */
void I2C1_ERROR_ISR(void);

 
#endif //MSSP1_H