#ifndef __W25NXX_H__
#define __W25NXX_H__

#include "SPI.h"

// W25N01GV Device Macros
#define W25N_PAGE_SIZE		2048
#define W25N_PAGE_COUNT		65536
#define W25N_BLOCK_SIZE		64
#define W25N_BLOCK_COUNT	1024
#define W25N_OTP_SIZE		2048
#define W25N_OTP_COUNT		10
#define W25N_TOTAL_SIZE		134217728

// Initialization and Control Functions
void W25N_Init(void);
uint32_t W25N_JEDEC_ID(void);

// Status Register Functions
uint8_t W25N_ReadStatusReg(uint8_t addr);
void W25N_WriteStatusReg(uint8_t addr, uint8_t data);

// Erase Function
void W25N_EraseBlock(uint16_t blockNumber);

#endif
