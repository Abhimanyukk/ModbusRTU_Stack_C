#include "modbus_master.h"

size_t MasterFrame(uint8_t slave_id, function_code_t function_code, uint16_t starting_addr, uint16_t quantity, uint16_t data, uint8_t *pData)
{
    modbusMasterFrame_t modbusMasterFrame;

    modbusMasterFrame.slave_id = slave_id;
    modbusMasterFrame.function_code = function_code;
    modbusMasterFrame.starting_address = starting_addr - MODBUS_REGISTER_OFFSET;
    modbusMasterFrame.data_or_quantity = ( (function_code == WRITE_SINGLE_COIL) || (function_code == WRITE_SINGLE_REGISTER) ) ? data : quantity;
    modbusMasterFrame.crc = 0;

    uint8_t frame_arr[sizeof(modbusMasterFrame_t)];
    memcpy (frame_arr, &modbusMasterFrame, sizeof(modbusMasterFrame_t));

    uint16_t crc_16;
    crc_16 = CalculateCRC(frame_arr, sizeof(modbusMasterFrame) - sizeof(modbusMasterFrame.crc));
    modbusMasterFrame.crc = ((crc_16 >> 8) & 0x00FF) | (crc_16 << 8);
    memcpy (pData, &modbusMasterFrame, sizeof(modbusMasterFrame));

    return sizeof(modbusMasterFrame);
}

uint16_t CalculateCRC (uint8_t *buf, size_t len)
{
    uint16_t CRC = 0xFFFF;
    
    for (size_t pos = 0; pos < len; pos++)
    {
        CRC ^= (uint16_t)buf[pos];

        for (size_t i = 8; i != 0; i--)
        {
            if ((CRC & 0x0001) != 0)
            {
                CRC >>= 1;
                CRC ^= 0xA001;
            }
            else
                CRC >>= 1;
        }
    }
    
    return CRC;
}


