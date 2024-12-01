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


void W25N_Reset(void);
uint32_t W25N_ReadJEDEC_ID(void);
void W25N_WriteEnable(void);
void W25N_WriteDisable(void);

#endif
