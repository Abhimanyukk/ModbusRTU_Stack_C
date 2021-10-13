#include "modbus_slave.h"

int slave()
{
    printf("Slave %d\n", VALUE);

    return 0;
}

error_t GetResponse(uint8_t *poll_request, uint8_t *response, uint8_t *response_length, uint8_t slave_id)
{
    modbusRequestFrame_t modbusRequestFrame;

    memcpy (&modbusRequestFrame, poll_request, sizeof(modbusResponseFrame_t));

    if (modbusRequestFrame.slave_id != slave_id)
    {
        return WRONG_SLAVE_ID;
    }

    uint8_t no_of_response_bytes;
    uint8_t data[255];      //TODO: Specify Max length
    error_t err_ret;
    
    switch (modbusRequestFrame.function_code)
    {
        case READ_COIL_STATUS:
            err_ret = ReadCoil(modbusRequestFrame.starting_address, &no_of_response_bytes, data);
        break;

        case READ_INPUT_STATUS:

        break;

        case READ_HOLDING_REGISTERS:

        break;

        default:
            return INVALID_FUNCTION_CODE;
    }
}

error_t ReadCoil(uint16_t starting_address, uint8_t *no_of_response_bytes, uint8_t *data)
{
    // uint8_t data = 0;

    // for (int i = 0; i < sizeof(COIL))
    
    printf("Read Coil\n");

    return SUCCESS;
}