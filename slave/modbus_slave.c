#include "modbus_slave.h"

#ifndef DATABASE
    const uint16_t COIL_ADDRESS[]       = {0x1000, 0x1001, 0x1002, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007, 0x1008, 0x1009, 0x100A, 0x100B, 0x100C, 0x100D, 0x100E, 0x100F};
    const bool COIL_STATUS[]            = {true, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true};
#endif // !DATABASE

error_t GetResponse(uint8_t *poll_request, uint8_t slave_id, uint8_t *response, uint8_t *response_length)
{
    modbusRequestFrame_t modbusRequestFrame;
    modbusResponseHeader_t modbusResponseHeader;

    memcpy (&modbusRequestFrame, poll_request, sizeof(modbusRequestFrame));

    if (modbusRequestFrame.slave_id != slave_id)
    {
        return WRONG_SLAVE_ID;
    }
    uint8_t no_of_response_bytes;
    uint8_t data[255];      //TODO: Specify Max length
    error_t err_ret;
    uint8_t *buff;
    uint16_t crc_16;
    uint8_t crc_8[2] = {0};

    
    switch (modbusRequestFrame.function_code)
    {
        case READ_COIL_STATUS:
            err_ret = ReadCoil(modbusRequestFrame.starting_address + MODBUS_REGISTER_OFFSET, modbusRequestFrame.data_or_quantity, &no_of_response_bytes, data);

            modbusResponseHeader.slave_id        = modbusRequestFrame.slave_id;
            modbusResponseHeader.function_code   = modbusRequestFrame.function_code;
            modbusResponseHeader.byte_count      = no_of_response_bytes;
            
            *response_length = sizeof(modbusResponseHeader) + no_of_response_bytes + 2;
            buff = (uint8_t *) malloc(*response_length);

            memcpy (buff, &modbusResponseHeader, sizeof(modbusResponseHeader));
            memcpy (buff + sizeof(modbusResponseHeader), data, no_of_response_bytes);
            
            crc_16 = CalculateCRC(buff, sizeof(modbusResponseHeader) + no_of_response_bytes);
            crc_8[0] = (uint8_t) (crc_16 >> 8);
            crc_8[1] = (uint8_t) (crc_16 & 0x00FF);

            memcpy (buff + (sizeof(modbusResponseHeader) + no_of_response_bytes), crc_8, 2);
            memcpy (response, buff, *response_length);

        break;

        case READ_INPUT_STATUS:

        break;

        case READ_HOLDING_REGISTERS:

        break;

        default:
            return INVALID_FUNCTION_CODE;
    }

    return err_ret;
}

error_t ReadCoil(uint16_t starting_address, uint16_t quantity, uint8_t *no_of_response_bytes, uint8_t *data)
{   
    printf("Read Coil\n");

    uint16_t index = GetIndex(starting_address, COIL_ADDRESS, sizeof(COIL_ADDRESS) / sizeof(COIL_ADDRESS[0]));
    if (index == 0)
    {
        return NO_ADDRESS_FOUND;
    }
    index--;

    *no_of_response_bytes = ( quantity / (sizeof (uint8_t) * 8) );
    *no_of_response_bytes = (quantity % (sizeof (uint8_t) * 8) > 0) ? *no_of_response_bytes + 1 : *no_of_response_bytes + 0;
    uint8_t data_bit = 0;
    uint8_t data_byte_count = 0;
    uint8_t left_shift_count = 0;

    while (quantity-- > 0)
    {
        data_bit = data_bit | (COIL_STATUS[index++] << left_shift_count++);
        data[data_byte_count] = data_bit;
        
        if (left_shift_count > 7)
        {
            data_byte_count++;
            data_bit = 0;
            left_shift_count = 0;
        }
    }

    return SUCCESS;
}

uint16_t GetIndex(uint16_t address, const uint16_t *data_arr, uint16_t length)
{
    for (size_t i = 1; i <= length; i++)
        if (data_arr[i - 1] == address)
            return i;
    
    return 0;
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