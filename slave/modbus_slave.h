#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#define MODBUS_REGISTER_OFFSET  0

typedef uint8_t error_t;
enum error_t
{
    SUCCESS = 0,
    ERROR,
    WRONG_SLAVE_ID,
    INVALID_FUNCTION_CODE,
    NO_ADDRESS_FOUND
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
typedef struct __attribute__((packed, scalar_storage_order("big-endian"))) ModbusResponseHeader
{
    uint8_t slave_id;                   // 1
    function_code_t function_code;      // 1
    uint8_t byte_count;                 // 1
    // uint8_t *data;                      
    // uint16_t crc;                       // 2
} modbusResponseHeader_t;                // 5 + len of data

error_t GetResponse(uint8_t *poll_request, uint8_t slave_id, uint8_t *response, uint8_t *response_length);
error_t ReadCoil(uint16_t starting_address, uint16_t quantity, uint8_t *no_of_response_bytes, uint8_t *data);
uint16_t GetIndex(uint16_t address, const uint16_t *data_arr, uint16_t length);
uint16_t CalculateCRC (uint8_t *buf, size_t len);