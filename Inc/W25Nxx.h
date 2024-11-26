#ifndef __W25NXX_H__
#define __W25NXX_H__

#include "SPI.h"

void W25N_Reset(void);
uint32_t W25N_ReadJEDEC_ID(void);
void W25N_WriteEnable(void);
void W25N_WriteDisable(void);

#endif
