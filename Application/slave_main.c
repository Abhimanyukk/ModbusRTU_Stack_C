#include <stdio.h>

#include "../slave/modbus_slave.h"
#include "user_config.h"

const uint8_t coil_address[]    = {0x1000, 0x1001};
const uint8_t coil_status[]     = {true, false};
int main()
{
    printf("HEELO\n");

    // int i = slave();

    uint8_t rx_buff[] = {0x01, 0x01, 0x10, 0x01, 0x00, 0x02, 0x00, 0x00};
    uint8_t response[100] = {0};         //TODO: Specify Length
    uint8_t response_length;
    dataBase_t dataBase;

    dataBase.coil_address = (uint8_t*)malloc(strlen(coil_address) * sizeof(uint8_t));


    error_t err_ret = GetResponse(rx_buff, response, &response_length, SLAVE_ID);

    return 0;
}