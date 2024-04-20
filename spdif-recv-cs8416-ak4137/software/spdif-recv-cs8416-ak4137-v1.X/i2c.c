


#include "mcc_generated_files/system/system.h"

uint8_t  I2C1_Read1ByteRegister(uint16_t address, uint8_t reg) {
bool i2c_status;
uint8_t value;

i2c_status = I2C1_WriteRead(address, &reg, 1, &value, 1);
if (i2c_status) {
    while (I2C1_IsBusy());
    return value;
} else {
    return 0;
}

}

#if 0
static void AT24CM02_DataToSendSet(block_t *block, uint8_t *dataToSend)
{
    dataToSend[0] = (block->wordAdress >> 8) &0xFF;
    dataToSend[1] = block->wordAdress & 0xFF;
 
    for (uint16_t index = 0; index < block->dataSize; ++index) {
        dataToSend[index + 2] = *(block->data + index);
    }
}
#endif
void I2C1_Write1ByteRegister(uint16_t address, uint8_t reg, uint8_t data) {
    bool i2c_status;
    
    //uint16_t to_write = (reg << 8 || data);
    uint8_t blob[2] = { reg, data};
    
    i2c_status = I2C1_Write(address, blob, (sizeof(blob) / sizeof(blob[0])));
if (i2c_status) {
    while (I2C1_IsBusy());
}
    
}
