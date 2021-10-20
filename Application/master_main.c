#include <stdio.h>

#include "../master/modbus_master.h"
#include "user_config.h"

void PrintArray(uint8_t *response, uint8_t response_length)
{
    while (response_length--)
    {
        printf("0x%02x ", *response);
        *response++;
    }
    printf("\n");
}

int main()
{
    uint8_t master_frame_arr[20] = {0};
    uint8_t master_frame_len = 0;
    master_frame_len = MasterFrame(SLAVE_ID, FUNCTION_CODE, STARTING_INDEX, NO_OF_REGISTERS, 0, master_frame_arr);

    PrintArray(master_frame_arr, master_frame_len);
}

