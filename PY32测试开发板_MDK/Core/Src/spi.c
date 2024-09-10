#include "spi.h"

SPI_HandleTypeDef hspi1;

void MX_SPI_Init( void ) {
    /*初始化SPI配置*/
    hspi1.Instance               = SPI1;                       /* SPI1 */
    hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;  /* 128分频 */
    hspi1.Init.Direction         = SPI_DIRECTION_2LINES;       /* 全双工 */
    hspi1.Init.CLKPolarity       = SPI_POLARITY_LOW;           /* 时钟极性低 */
    hspi1.Init.CLKPhase          = SPI_PHASE_1EDGE ;           /* 数据采样从第一个时钟边沿开始 */
    hspi1.Init.DataSize          = SPI_DATASIZE_8BIT;          /* SPI数据长度为8bit */
    hspi1.Init.FirstBit          = SPI_FIRSTBIT_MSB;           /* 先发送MSB */
    hspi1.Init.NSS               = SPI_NSS_SOFT;               /* NSS软件模式 */
    hspi1.Init.Mode = SPI_MODE_MASTER;                         /* 配置为主机 */
    if (HAL_SPI_DeInit(&hspi1) != HAL_OK)                      /* SPI反初始化 */
    {
        while(1);
    }
    /*SPI初始化*/
    if (HAL_SPI_Init(&hspi1) != HAL_OK)
    {
        while(1);
    }
}

/**
  * @brief 初始化全局MSP
  */
 void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
 {
   GPIO_InitTypeDef  GPIO_InitStruct;
 
    __HAL_RCC_GPIOA_CLK_ENABLE();                   /* GPIOA时钟使能 */
    __HAL_RCC_SYSCFG_CLK_ENABLE();                  /* 使能SYSCFG时钟 */
    __HAL_RCC_SPI1_CLK_ENABLE();                    /* SPI1时钟使能 */

    /*SCK A5*/
    GPIO_InitStruct.Pin       = GPIO_PIN_5;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull =      GPIO_PULLDOWN;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // /*SPI NSS*/
    // GPIO_InitStruct.Pin = GPIO_PIN_4;
    // GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    // if (hspi->Init.CLKPolarity == SPI_POLARITY_LOW)
    // {
    //   GPIO_InitStruct.Pull = GPIO_PULLDOWN;
    // }
    // else
    // {
    //   GPIO_InitStruct.Pull = GPIO_PULLUP;
    // }
    // GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    // GPIO_InitStruct.Alternate = GPIO_AF0_SPI1;
    // HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    /*GPIO配置为SPI：MOSI*/
    GPIO_InitStruct.Pin       = GPIO_PIN_1;
    GPIO_InitStruct.Mode      = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull      = GPIO_PULLDOWN;
    GPIO_InitStruct.Speed     = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF10_SPI1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // /*中断配置*/
    // HAL_NVIC_SetPriority(SPI1_IRQn, 1, 0);
    // HAL_NVIC_EnableIRQ(SPI1_IRQn);
 
 }
 
 void HAL_SPI_MspDeInit(SPI_HandleTypeDef *hspi)
{
  if (hspi->Instance == SPI1)
  {
    /*##-1- Reset peripherals ##################################################*/
    __HAL_RCC_SPI1_FORCE_RESET();
    __HAL_RCC_SPI1_RELEASE_RESET();

    /*##-2- Disable peripherals and GPIO Clocks ################################*/
    /* Deconfigure SPI SCK */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_1 | GPIO_PIN_5 );

    // HAL_NVIC_DisableIRQ(SPI1_IRQn);
  }
}
