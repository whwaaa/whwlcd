#ifndef __SPI_H__
#define __SPI_H__

#include "common.h"

extern SPI_HandleTypeDef hspi1;

void MX_SPI_Init( void );
void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi);
void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi);


#endif /*__SPI_H__*/



