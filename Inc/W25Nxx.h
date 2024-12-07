#ifndef __W25NXX_H__
#define __W25NXX_H__

#include "SPI.h"
#include "SYSTICK.h"
#include "UART.h"

// W25N01GV Device Macros
#define W25N_PAGE_SIZE		2048
#define W25N_PAGE_COUNT		65536
#define W25N_BLOCK_SIZE		64
#define W25N_BLOCK_COUNT	1024
#define W25N_OTP_SIZE		2048
#define W25N_OTP_COUNT		10
#define W25N_TOTAL_SIZE		134217728

#define BBM_LUT_SIZE 			20
static uint16_t lut[BBM_LUT_SIZE * 2];

// Initialization and ID Functions
void W25N_Init(void);
uint32_t W25N_JEDEC_ID(void);

// Status Register Control functions
uint8_t W25N_GetBlockProtectBits();
void W25N_SetBlockProtectBits(uint8_t bp_bits);
uint8_t W25N_GetEccEnable();
void W25N_SetEccEnable(uint8_t enable);
uint8_t W25N_GetBufferReadMode();
void W25N_SetBufferReadMode(uint8_t mode);
uint8_t W25N_GetWriteProtectionEnable();
void W25N_SetWriteProtectionEnable(uint8_t enable);
uint8_t W25N_GetStatusRegisterProtectBits();
void W25N_SetStatusRegisterProtectBits(uint8_t srp_bits);

void W25N_WritePage(uint16_t pageNumber, uint8_t *data, uint16_t size);
void W25N_ReadPage(uint16_t pageNumber, uint8_t *data, uint16_t size);
void W25N_FastReadPage(uint16_t pageNumber, uint8_t *data, uint16_t size);

// Erase Function
void W25N_EraseBlock(uint16_t blockNumber);

#endif
