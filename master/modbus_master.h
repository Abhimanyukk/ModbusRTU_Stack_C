#ifndef MODBUS_MASTER_H
#define MODBUS_MASTER_H

#include <stdio.h>
#include <string.h>
#include <stdint.h>

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
typedef struct __attribute__((packed, scalar_storage_order("big-endian"))) ModbusMasterFrame
{
    uint8_t slave_id;
    function_code_t function_code;
    uint16_t starting_address;
    uint16_t data_or_quantity;
    uint16_t crc;
} modbusMasterFrame_t;

#define MODBUS_REGISTER_OFFSET  1

uint16_t CalculateCRC (uint8_t *buf, size_t len);
size_t MasterFrame(uint8_t slave_id, function_code_t function_code, uint16_t starting_addr, uint16_t quantity, uint16_t data, uint8_t *pData);


#endif // !MODBUS_MASTER_H
