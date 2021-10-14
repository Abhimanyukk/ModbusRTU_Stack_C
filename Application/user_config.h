#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define SLAVE_ID            1
#define FUNCTION_CODE       1
#define STARTING_ADDRESS    0x1001

// #define COIL_ADDRESS        {0x1000, 0x1001, 0x1002, 0x1003, 0x1004, 0x1005, 0x1006, 0x1007, 0x1008, 0x1009, 0x100A, 0x100B, 0x100C, 0x100D, 0x100E, 0x100F}
// #define COIL_ADDRESS        "aaa"
// #define COIL_STATUS         {true, false, true, true, false, true, true, false, true, true, false, true, true, false, false, true}

// typedef struct __attribute__((packed, scalar_storage_order("big-endian"))) DataBase
// {
//     uint16_t *coil_address;
//     uint8_t *coil_status;
// }dataBase_t;

#endif // USER_CONFIG_H