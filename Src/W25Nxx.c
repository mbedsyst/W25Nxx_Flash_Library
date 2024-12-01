#include "W25Nxx.h"

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

void W25N_Reset(void)
{

}

uint32_t W25N_ReadJEDEC_ID(void)
{

}

void W25N_WriteEnable(void)
{

}

void W25N_WriteDisable(void)
{

}
