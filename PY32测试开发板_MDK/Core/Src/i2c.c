#include "i2c.h"

I2C_HandleTypeDef hi2c1;

/* I2C1 init function */
void MX_I2C_Init(void)
{
  hi2c1.Instance = I2C;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  // hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  // hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  // hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    while(1);
  }
  
}

void HAL_I2C_MspInit(I2C_HandleTypeDef* i2cHandle)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(i2cHandle->Instance==I2C)
  {
    __HAL_RCC_SYSCFG_CLK_ENABLE();                              /*SYSCFG时钟使能*/
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_I2C_CLK_ENABLE();
    /**I2C GPIO Configuration
    PA3     ------> I2C_SCL
    PA2     ------> I2C_SDA
    */
    GPIO_InitStruct.Pin = GPIO_PIN_3|GPIO_PIN_2;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_OD;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Alternate = GPIO_AF12_I2C;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    /*复位I2C*/
    __HAL_RCC_I2C_FORCE_RESET();
    __HAL_RCC_I2C_RELEASE_RESET();
    
  }
}

void HAL_I2C_MspDeInit(I2C_HandleTypeDef* i2cHandle)
{

  if(i2cHandle->Instance==I2C1)
  {
    /* Peripheral clock disable */
    __HAL_RCC_I2C_CLK_DISABLE();

    /**I2C GPIO Configuration
    PA3     ------> I2C_SCL
    PA2     ------> I2C_SDA
    */
    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_3);

    HAL_GPIO_DeInit(GPIOA, GPIO_PIN_2);
  }
}


