#include <stdio.h>

#include "../slave/modbus_slave.h"
#include "user_config.h"



int main()
{
    uint8_t rx_buff[] = {0x01, 0x01, 0x10, 0x00, 0x00, 0x04, 0x00, 0x00};
    // uint8_t rx_buff[] = {0x01, 0x03, 0x20, 0x00, 0x00, 0x01, 0x00, 0x00};
    uint8_t response[100] = {0};         //TODO: Specify Length
    uint8_t response_length;

    error_t err_ret = GetResponse(rx_buff, SLAVE_ID, response, &response_length);
    if (err_ret != SUCCESS)
    {
        printf("ERR CODE: %d\n", err_ret);
        return 0;
    }

    // for (size_t i = 0; i < response_length; i++)
    // {
    //     printf("0x%02x ", response[i]);
    // }
    // printf("\n");

    PrintArray(response, response_length);

    
    
    return 0;
}