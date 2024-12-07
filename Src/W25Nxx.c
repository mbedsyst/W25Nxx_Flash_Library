#include "W25Nxx.h"
#include <stdio.h>

// Device Instruction Macros
#define DEVICE_RESET          0xFF
#define READ_JEDEC_ID         0x9F
#define READ_STATUS_REG       0x05
#define WRITE_STATUS_REG      0x1F
#define ENABLE_WRITE          0x06
#define DISABLE_WRITE         0x04
#define SWAP_BLOCKS           0xA1
#define READ_BBM_LUT          0xA5
#define ECC_FAIL_ADDR         0xA9
#define ERASE_BLOCK           0xD8
#define PROG_DATA_LOAD        0x02
#define RAND_PROG_DATA_LOAD   0x84
#define PROG_EXEC             0x10
#define PAGE_READ             0x13
#define READ_EXEC	          0x03
#define FAST_READ             0x0B

// Status Register Address Macros
#define STATUS_REG1			  0xA0
#define STATUS_REG2			  0xB0
#define STATUS_REG3			  0xC0

// Status Register-1 Bit Positions
#define W25N_SR1_BP0         (1 << 3)  // Block Protect Bit 0
#define W25N_SR1_BP1         (1 << 4)  // Block Protect Bit 1
#define W25N_SR1_BP2         (1 << 5)  // Block Protect Bit 2
#define W25N_SR1_BP3         (1 << 6)  // Block Protect Bit 3
#define W25N_SR1_TB          (1 << 2)  // Top/Bottom Block Protect
#define W25N_SR1_WP_E        (1 << 1)  // Write Protection Enable

// Status Register-2 Bit Positions
#define W25N_SR2_BUF         (1 << 3)  // Buffer Read Mode
#define W25N_SR2_ECC_E       (1 << 4)  // ECC Enable
#define W25N_SR2_SR1_L       (1 << 6)  // Status Register-1 Lock
#define W25N_SR2_OTP_E       (1 << 2)  // OTP Access Mode Enable

// Status Register-3 Bit Positions
#define W25N_SR3_LUT_F       (1 << 0)  // Look-Up Table Full
#define W25N_SR3_ECC_0       (1 << 2)  // ECC Status Bit 0
#define W25N_SR3_ECC_1       (1 << 3)  // ECC Status Bit 1
#define W25N_SR3_P_FAIL      (1 << 4)  // Program Failure
#define W25N_SR3_E_FAIL      (1 << 5)  // Erase Failure
#define W25N_SR3_WEL         (1 << 1)  // Write Enable Latch
#define W25N_SR3_BUSY        (1 << 0)  // Erase/Program In Progress


static void W25N_WriteEnable(void)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ENABLE_WRITE);
	SPI2_DeselectSlave();

}

static void W25N_WriteDisable(void)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(DISABLE_WRITE);
	SPI2_DeselectSlave();
}

static void W25N_Reset(void)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(DEVICE_RESET);
	SPI2_DeselectSlave();
	delay_ms(100);
}

void W25N_Init(void)
{
	SPI2_Init();
	W25N_Reset();
	printf("[info] Flash Reset and Initialized.\n\r");
}

uint32_t W25N_JEDEC_ID(void)
{
	uint8_t dummyByte = 0xFF;
	uint8_t id[3];
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(READ_JEDEC_ID);
	SPI2_TransmitReceiveByte(dummyByte);
	SPI2_TransmitReceive_MultiByte(&dummyByte, id, 3);
	SPI2_DeselectSlave();
	printf("[info] Retrieved JEDEC ID.\n\r");
	return ((id[0] << 16) | (id[1] << 8) | (id[2]));
}

uint8_t W25N_ReadStatusReg(uint8_t addr)
{
	uint8_t status_reg;
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(READ_STATUS_REG);
	SPI2_TransmitReceiveByte(addr & 0xFF);
	status_reg = SPI2_TransmitReceiveByte(0xFF);
	SPI2_DeselectSlave();
	printf("[info] Reading Status Register.\n\r");
	return status_reg;
}

static void W25N_WriteStatusReg(uint8_t addr, uint8_t data)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(WRITE_STATUS_REG);
	SPI2_TransmitReceiveByte(addr);
	SPI2_TransmitReceiveByte(data);
	SPI2_DeselectSlave();
	printf("[info] Writing to Status Register.\n\r");
}

void W25N_EraseBlock(uint16_t blockNumber)
{
	uint16_t addr = (blockNumber * 64 * 2048); // 1 Block contains 64 Pages each of 2048 bytes (131072 bytes)
	W25N_WriteEnable();
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(ERASE_BLOCK);
	SPI2_TransmitReceiveByte(0xFF);
	SPI2_TransmitReceiveByte((addr >> 8) & 0xFF);
	SPI2_TransmitReceiveByte((addr) & 0xFF);
	SPI2_DeselectSlave();
	delay_ms(10);
	printf("[info] Erasing Block Number %d.\n\r", blockNumber);
}

uint8_t W25N_GetStatusBit(uint8_t reg_addr, uint8_t bit_pos)
{
    uint8_t reg_value = W25N_ReadStatusReg(reg_addr);
    return (reg_value >> bit_pos) & 0x01;
}

void W25N_SetStatusBit(uint8_t reg_addr, uint8_t bit_pos, uint8_t value)
{
    uint8_t reg_value = W25N_ReadStatusReg(reg_addr);

    if (value)	reg_value |= (1 << bit_pos);
    else        reg_value &= ~(1 << bit_pos);

    W25N_WriteStatusReg(reg_addr, reg_value);
}

uint8_t W25N_GetBlockProtectBits()
{
    uint8_t reg_value = W25N_ReadStatusReg(STATUS_REG1);
    return (reg_value >> 2) & 0x1F;
}

void W25N_SetBlockProtectBits(uint8_t bp_bits)
{
    uint8_t reg_value = W25N_ReadStatusReg(STATUS_REG1);
    reg_value = (reg_value & 0xC3) | ((bp_bits & 0x1F) << 2); // Update BP3-BP0, TB bits
    W25N_WriteStatusReg(STATUS_REG1, reg_value);
}

uint8_t W25N_GetEccEnable()
{
    return W25N_GetStatusBit(STATUS_REG2, 4);
}

void W25N_SetEccEnable(uint8_t enable)
{
    W25N_SetStatusBit(STATUS_REG2, 4, enable);
}

uint8_t W25N_GetBufferReadMode()
{
    return W25N_GetStatusBit(STATUS_REG2, 3);
}

void W25N_SetBufferReadMode(uint8_t mode)
{
    W25N_SetStatusBit(STATUS_REG2, 3, mode);
}

uint8_t W25N_GetWriteProtectionEnable()
{
    return W25N_GetStatusBit(STATUS_REG1, 1);
}

void W25N_SetWriteProtectionEnable(uint8_t enable)
{
    W25N_SetStatusBit(STATUS_REG1, 1, enable);
}

uint8_t W25N_GetStatusRegisterProtectBits()
{
    uint8_t reg_value = W25N_ReadStatusReg(STATUS_REG1);
    return (reg_value & 0x81);
}

void W25N_SetStatusRegisterProtectBits(uint8_t srp_bits)
{
    uint8_t reg_value = W25N_ReadStatusReg(STATUS_REG1);
    reg_value = (reg_value & 0x7E) | (srp_bits & 0x81);
    W25N_WriteStatusReg(STATUS_REG1, reg_value);
}

static void W25N_ExecuteWrite(uint16_t addr)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(PROG_EXEC);
	SPI2_TransmitReceiveByte(0xFF);
	SPI2_TransmitReceiveByte((addr >> 8) & 0xFF);
	SPI2_TransmitReceiveByte((addr) & 0xFF);
	SPI2_DeselectSlave();
}

void W25N_WritePage(uint16_t pageNumber, uint8_t *data, uint16_t size)
{
	uint16_t addr = (pageNumber * 2112);
	W25N_WriteEnable();
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(PROG_DATA_LOAD);
	SPI2_TransmitReceiveByte((addr >> 8) & 0xFF);
	SPI2_TransmitReceiveByte((addr) & 0xFF);
	SPI2_TransmitReceive_MultiByte(data, NULL, size);
	SPI2_DeselectSlave();
	W25N_WriteDisable();
	W25N_ExecuteWrite(addr);
	delay_ms(5);
	printf("[info] Writing Data to Flash Memory.\n\r");
}

static void W25N_ExecuteRead(uint16_t addr, uint8_t *data, uint16_t size)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(READ_EXEC);
	SPI2_TransmitReceiveByte((addr >> 8) & 0xFF);
	SPI2_TransmitReceiveByte((addr) & 0xFF);
	SPI2_TransmitReceiveByte(0xFF);
	SPI2_TransmitReceive_MultiByte(data, NULL, size);
	SPI2_DeselectSlave();
}

void W25N_ReadPage(uint16_t pageNumber, uint8_t *data, uint16_t size)
{
	uint16_t addr = (pageNumber * 2112);
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(PAGE_READ);
	SPI2_TransmitReceiveByte(0xFF);
	SPI2_TransmitReceiveByte((addr >> 8) & 0xFF);
	SPI2_TransmitReceiveByte((addr) & 0xFF);
	SPI2_DeselectSlave();
	delay_ms(1);
	W25N_ExecuteRead(addr, data, size);
	printf("[info] Reading Data (Normal) from Flash Memory.\n\r");
}

void W25N_FastReadPage(uint16_t pageNumber, uint8_t *data, uint16_t size)
{
	uint16_t addr = (pageNumber * 2112);
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(FAST_READ);
	SPI2_TransmitReceiveByte((addr >> 8) & 0xFF);
	SPI2_TransmitReceiveByte((addr) & 0xFF);
	SPI2_TransmitReceiveByte(0xFF);
	SPI2_DeselectSlave();
	delay_ms(1);
	W25N_ExecuteRead(addr, data, size);
	printf("[info] Reading Data (Fast) from Flash Memory.\n\r");
}

void W25N_UpdateLUT(uint16_t lba, uint16_t pba, uint8_t index)
{
    if (index < BBM_LUT_SIZE)
    {
        lut[2 * index] = lba;        // Logical Block Address
        lut[2 * index + 1] = pba;    // Physical Block Address
    }
}

void W25N_GetLUTEntry(uint8_t index, uint16_t *lba, uint16_t *pba)
{
    if (index < BBM_LUT_SIZE)
    {
        *lba = lut[2 * index];      // Logical Block Address
        *pba = lut[2 * index + 1];  // Physical Block Address
    }
}

