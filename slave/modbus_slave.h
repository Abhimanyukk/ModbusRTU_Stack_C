#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define VALUE 6

// #define SUCCESS         true
// #define ERROR           false

typedef uint8_t error_t;
enum error_t
{
    SUCCESS = 0,
    ERROR,
    WRONG_SLAVE_ID,
    INVALID_FUNCTION_CODE
};

typedef uint8_t function_code_t;
enum function_code_t
{
    READ_COIL_STATUS = 1,
    READ_INPUT_STATUS,
    READ_HOLDING_REGISTERS,
    READ_INPUT_REGISTERS,
    WRITE_SINGLE_COIL,
    WRITE_SINGLE_REGISTER,
    WRITE_MULTIPLE_COILS = 15,
    WRITE_MULTIPLE_REGISTERS
};

#pragma pack(1)
typedef struct __attribute__((packed, scalar_storage_order("big-endian"))) ModbusRequestFrame
{
    uint8_t slave_id;
    function_code_t function_code;
    uint16_t starting_address;
    uint16_t data_or_quantity;
    uint16_t crc;
} modbusRequestFrame_t;

#pragma pack(1)
typedef struct __attribute__((packed, scalar_storage_order("big-endian"))) ModbusResponseFrame
{
    uint8_t slave_id;
    function_code_t function_code;
    uint8_t byte_count;
    uint8_t *data;
    uint16_t crc;
} modbusResponseFrame_t;

error_t GetResponse(uint8_t *poll_request, uint8_t *response, uint8_t *response_length, uint8_t slave_id);
error_t ReadCoil(uint16_t starting_address, uint8_t *no_of_bytes, uint8_t *data);
int slave();