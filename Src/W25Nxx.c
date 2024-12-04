#include "W25Nxx.h"

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
#define NORMAL_READ           0x03
#define FAST_READ             0x0B

// Status Register Address Macros
#define STATUS_REG1			  0xA0
#define STATUS_REG2			  0xB0
#define STATUS_REG3			  0xC0

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
	return status_reg;
}

void W25N_WriteStatusReg(uint8_t addr, uint8_t data)
{
	SPI2_SelectSlave();
	SPI2_TransmitReceiveByte(WRITE_STATUS_REG);
	SPI2_TransmitReceiveByte(addr);
	SPI2_TransmitReceiveByte(data);
	SPI2_DeselectSlave();
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
}
