/**
 * MSSP2 Generated Driver File
 *
 * @file mssp2.c
 *
 * @ingroup i2c_host
 *
 * @brief This file contains the driver code for I2C2 module.
 *
 * @version I2C2 Driver Version 2.1.0
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

#include <xc.h>
#include "../mssp2.h"

/* I2C2 event system interfaces */
static void I2C2_ReadStart(void);
static void I2C2_WriteStart(void);
static void I2C2_Close(void);
static void I2C2_EventHandler(void);
static void I2C2_ErrorEventHandler(void);
static void I2C2_DefaultCallback(void);

/* I2C2 Interfaces */
static uint8_t I2C2_DataReceive(void);
static void I2C2_DataTransmit(uint8_t data);
static inline void I2C2_BusReset(void);
static inline void I2C2_ReceiveEnable(void);
static inline void I2C2_RestartEnable(void);
static inline void I2C2_RestartDisable(void);
static inline void I2C2_StartSend(void);
static inline void I2C2_StopSend(void);
static inline void I2C2_AckSend(void);
static inline void I2C2_NackSend(void);
static bool I2C2_IsNack(void);
static bool I2C2_IsData(void);
static bool I2C2_IsAddr(void);
static bool I2C2_IsRxBufFull(void);
static inline void I2C2_InterruptsEnable(void);
static inline void I2C2_InterruptsDisable(void);
static inline void I2C2_InterruptClear(void);
static inline void I2C2_ErrorInterruptClear(void);
static inline void I2C2_StatusFlagsClear(void);

static i2c_host_event_states_t I2C2_EVENT_IDLE(void);
static i2c_host_event_states_t I2C2_EVENT_SEND_RD_ADDR(void);
static i2c_host_event_states_t I2C2_EVENT_SEND_WR_ADDR(void);
static i2c_host_event_states_t I2C2_EVENT_TX(void);
static i2c_host_event_states_t I2C2_EVENT_RX(void);
static i2c_host_event_states_t I2C2_EVENT_NACK(void);
static i2c_host_event_states_t I2C2_EVENT_ERROR(void);
static i2c_host_event_states_t I2C2_EVENT_STOP(void);
static i2c_host_event_states_t I2C2_EVENT_RESET(void);

/*
  Section: Driver Interface
 */
const i2c_host_interface_t I2C2_Host = {
    .Initialize = I2C2_Initialize,
    .Deinitialize = I2C2_Deinitialize,
    .Write = I2C2_Write,
    .Read = I2C2_Read,
    .WriteRead = I2C2_WriteRead,
    .TransferSetup = NULL,
    .ErrorGet = I2C2_ErrorGet,
    .IsBusy = I2C2_IsBusy,
    .CallbackRegister = I2C2_CallbackRegister,
    .Tasks = NULL
};

/*
 Section: Private Variable Definitions
 */
static void (*I2C2_Callback)(void) = NULL;
volatile i2c_host_event_status_t i2c2Status = {0};

typedef i2c_host_event_states_t (*i2c2eventHandler)(void);
const i2c2eventHandler i2c2_eventTable[] = {
    I2C2_EVENT_IDLE,
    I2C2_EVENT_SEND_RD_ADDR,
    I2C2_EVENT_SEND_WR_ADDR,
    I2C2_EVENT_TX,
    I2C2_EVENT_RX,
    I2C2_EVENT_NACK,
    I2C2_EVENT_ERROR,
    I2C2_EVENT_STOP,
    I2C2_EVENT_RESET
};

/**
 Section: Public Interfaces
 */
void I2C2_Initialize(void)
{
    /* CKE disabled; SMP Standard Speed;  */
    SSP2STAT = 0x80;
    /* SSPM FOSC/4_SSPxADD_I2C; CKP disabled; SSPEN disabled; SSPOV no_overflow; WCOL no_collision;  */
    SSP2CON1 = 0x8;
    /* SEN disabled; RSEN disabled; PEN disabled; RCEN disabled; ACKEN disabled; ACKDT acknowledge; GCEN disabled;  */
    SSP2CON2 = 0x0;
    /* DHEN disabled; AHEN disabled; SBCDE disabled; SDAHT 100ns; BOEN disabled; SCIE disabled; PCIE disabled;  */
    SSP2CON3 = 0x0;
    /* SSPADD 79;  */
    SSP2ADD = 0x4F;
    I2C2_InterruptsEnable();
    I2C2_CallbackRegister(I2C2_DefaultCallback);
    SSP2CON1bits.SSPEN = 1;
}

void I2C2_Deinitialize(void)
{
    SSP2STAT = 0x00;
    SSP2CON1 = 0x00;
    SSP2CON2 = 0x00;
    SSP2CON3 = 0x00;
    SSP2ADD = 0x00;
    I2C2_InterruptsDisable();
    I2C2_CallbackRegister(I2C2_DefaultCallback);
}

bool I2C2_Write(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!I2C2_IsBusy())
    {
        i2c2Status.busy = true;
        i2c2Status.address = address;
        i2c2Status.switchToRead = false;
        i2c2Status.writePtr = data;
        i2c2Status.writeLength = dataLength;
        i2c2Status.readPtr = NULL;
        i2c2Status.readLength = 0;
        i2c2Status.errorState = I2C_ERROR_NONE;
        I2C2_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

bool I2C2_Read(uint16_t address, uint8_t *data, size_t dataLength)
{
    bool retStatus = false;
    if (!I2C2_IsBusy())
    {
        i2c2Status.busy = true;
        i2c2Status.address = address;
        i2c2Status.switchToRead = false;
        i2c2Status.readPtr = data;
        i2c2Status.readLength = dataLength;
        i2c2Status.writePtr = NULL;
        i2c2Status.writeLength = 0;
        i2c2Status.errorState = I2C_ERROR_NONE;
        I2C2_ReadStart();
        retStatus = true;
    }
    return retStatus;
}

bool I2C2_WriteRead(uint16_t address, uint8_t *writeData, size_t writeLength, uint8_t *readData, size_t readLength)
{
    bool retStatus = false;
    if (!I2C2_IsBusy())
    {
        i2c2Status.busy = true;
        i2c2Status.address = address;
        i2c2Status.switchToRead = true;
        i2c2Status.writePtr = writeData;
        i2c2Status.writeLength = writeLength;
        i2c2Status.readPtr = readData;
        i2c2Status.readLength = readLength;
        i2c2Status.errorState = I2C_ERROR_NONE;
        I2C2_WriteStart();
        retStatus = true;
    }
    return retStatus;
}

i2c_host_error_t I2C2_ErrorGet(void)
{
    i2c_host_error_t retErrorState = i2c2Status.errorState;
    i2c2Status.errorState = I2C_ERROR_NONE;
    return retErrorState;
}

bool I2C2_IsBusy(void)
{
    return i2c2Status.busy || SSP2STATbits.S;
}

void I2C2_CallbackRegister(void (*callbackHandler)(void))
{
    if (callbackHandler != NULL)
    {
        I2C2_Callback = callbackHandler;
    }
}

void I2C2_ISR()
{
    I2C2_EventHandler();
}

void I2C2_ERROR_ISR()
{
    I2C2_ErrorEventHandler();
}

/*
 Section: Private Interfaces
 */
static void I2C2_ReadStart(void)
{
    I2C2_StartSend();
    i2c2Status.state = I2C_STATE_SEND_RD_ADDR;
}

static void I2C2_WriteStart(void)
{
    I2C2_StartSend();
    i2c2Status.state = I2C_STATE_SEND_WR_ADDR;
}

static void I2C2_Close(void)
{
    i2c2Status.busy = false;
    i2c2Status.address = 0xFF;
    i2c2Status.writePtr = NULL;
    i2c2Status.readPtr = NULL;
    i2c2Status.state = I2C_STATE_IDLE;
    I2C2_InterruptClear();
    I2C2_ErrorInterruptClear();
    I2C2_StatusFlagsClear();
}

static void I2C2_EventHandler(void)
{
    I2C2_InterruptClear();
    if (I2C2_IsAddr() && I2C2_IsNack())
    {
        i2c2Status.state = I2C_STATE_NACK;
        i2c2Status.errorState = I2C_ERROR_ADDR_NACK;
    }
    else if (I2C2_IsData() && I2C2_IsNack())
    {
        i2c2Status.state = I2C_STATE_NACK;
        i2c2Status.errorState = I2C_ERROR_DATA_NACK;
    }
    i2c2Status.state = i2c2_eventTable[i2c2Status.state]();
}

static void I2C2_ErrorEventHandler(void)
{
    i2c2Status.state = I2C_STATE_ERROR;
    i2c2Status.errorState = I2C_ERROR_BUS_COLLISION;
    I2C2_ErrorInterruptClear();
    i2c2Status.state = i2c2_eventTable[i2c2Status.state]();
    I2C2_Callback();
}

static void I2C2_DefaultCallback(void)
{
    // Default Callback for Error Indication
}

/* I2C2 Event interfaces */
static i2c_host_event_states_t I2C2_EVENT_IDLE(void)
{
    i2c2Status.busy = false;
    return I2C_STATE_RESET;
}

static i2c_host_event_states_t I2C2_EVENT_SEND_RD_ADDR(void)
{
    I2C2_DataTransmit((uint8_t) (i2c2Status.address << 1 | 1));
    return I2C_STATE_RX;
}

static i2c_host_event_states_t I2C2_EVENT_SEND_WR_ADDR(void)
{
    I2C2_DataTransmit((uint8_t) (i2c2Status.address << 1));
    return I2C_STATE_TX;
}

static i2c_host_event_states_t I2C2_EVENT_TX(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_TX;
    if (i2c2Status.writeLength)
    {
        i2c2Status.writeLength--;
        I2C2_DataTransmit(*i2c2Status.writePtr++);
        retEventState = I2C_STATE_TX;
    }
    else
    {
        if (i2c2Status.switchToRead)
        {
            i2c2Status.switchToRead = false;
            I2C2_RestartEnable();
            retEventState = I2C_STATE_SEND_RD_ADDR;
        }
        else
        {
            retEventState = I2C2_EVENT_STOP();
        }
    }

    return retEventState;
}

static i2c_host_event_states_t I2C2_EVENT_RX(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_RX;

    if (I2C2_IsRxBufFull())
    {
        if (i2c2Status.readLength > 0)
        {
            *i2c2Status.readPtr++ = I2C2_DataReceive();
            i2c2Status.readLength--;

        }

        if (i2c2Status.readLength > 0)
        {
            I2C2_AckSend();
        }
        else
        {
            I2C2_RestartDisable();
            I2C2_NackSend();
            retEventState = I2C_STATE_STOP;
        }

    }
    else
    {
        I2C2_ReceiveEnable();
    }
    return retEventState;
}

static i2c_host_event_states_t I2C2_EVENT_NACK(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_NACK;
    retEventState = I2C2_EVENT_STOP();
    return retEventState;
}

static i2c_host_event_states_t I2C2_EVENT_ERROR(void)
{
    i2c_host_event_states_t retEventState = I2C_STATE_ERROR;
    retEventState = I2C2_EVENT_RESET();
    return retEventState;
}

static i2c_host_event_states_t I2C2_EVENT_STOP(void)
{
    I2C2_StopSend();
    I2C2_Close();
    return I2C_STATE_IDLE;
}

static i2c_host_event_states_t I2C2_EVENT_RESET(void)
{
    I2C2_BusReset();
    i2c2Status.busy = false;
    return I2C_STATE_IDLE;
}

/*
 Section: Register Level Interfaces
 */
static uint8_t I2C2_DataReceive(void)
{
    return SSP2BUF;
}

static void I2C2_DataTransmit(uint8_t data)
{
    SSP2BUF = data;
}

static inline void I2C2_BusReset(void)
{
    SSP2CON1bits.SSPEN = 0;
    SSP2CON1bits.SSPEN = 1;
}

static inline void I2C2_ReceiveEnable(void)
{
    SSP2CON2bits.RCEN = 1;
}

static inline void I2C2_RestartEnable(void)
{
    SSP2CON2bits.RSEN = 1;
}

static inline void I2C2_RestartDisable(void)
{
    SSP2CON2bits.RSEN = 0;
}

static inline void I2C2_StartSend(void)
{
    SSP2CON2bits.SEN = 1;
}

static inline void I2C2_StopSend(void)
{
    SSP2CON2bits.PEN = 1;
}

static inline void I2C2_AckSend(void)
{
    SSP1CON2bits.ACKDT = 0;
    SSP1CON2bits.ACKEN = 1;
}

static inline void I2C2_NackSend(void)
{
    SSP1CON2bits.ACKDT = 1;
    SSP1CON2bits.ACKEN = 1;
}

static bool I2C2_IsNack(void)
{
    return SSP2CON2bits.ACKSTAT;
}

static bool I2C2_IsData(void)
{
    return (SSP2STATbits.D_nA);
}

static bool I2C2_IsAddr(void)
{
    return !(SSP2STATbits.D_nA);
}

static bool I2C2_IsRxBufFull(void)
{
    return SSP2STATbits.BF;
}

static inline void I2C2_InterruptsEnable(void)
{
    PIE3bits.SSP2IE = 1;
    PIE3bits.BCL2IE = 1;
}

static inline void I2C2_InterruptsDisable(void)
{
    PIE3bits.SSP2IE = 0;
    PIE3bits.BCL2IE = 0;
}

static inline void I2C2_InterruptClear(void)
{
    PIR3bits.SSP2IF = 0;
}

static inline void I2C2_ErrorInterruptClear(void)
{
    PIR3bits.BCL2IF = 0;
}

static inline void I2C2_StatusFlagsClear(void)
{
    SSP2CON1bits.WCOL = 0;
    SSP2CON1bits.SSPOV = 0;
}