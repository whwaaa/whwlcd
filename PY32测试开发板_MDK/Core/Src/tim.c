#include "tim.h"

TIM_HandleTypeDef htim1;
TIM_OC_InitTypeDef sConfig;

#define  PERIOD_VALUE       (uint32_t)(100 - 1)
#define  PULSE2_VALUE       40



/**
  * @brief  错误执行函数
  * @param  无
  * @retval 无
  */
void Error_Handler(void) {
  /* 无限循环 */
  while (1) { }
}

/**
  * @brief 初始化全局MSP
  */
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
  GPIO_InitTypeDef   GPIO_InitStruct;
  /*TIM1时钟使能 */
  __HAL_RCC_TIM1_CLK_ENABLE();                              
  /*GPIOA时钟使能 */
  __HAL_RCC_GPIOB_CLK_ENABLE();
  /*复用功能 */
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;                   
  /* 上拉 */
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;                       
  /* 高速*/
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  /*GPIOB3初始化*/
  GPIO_InitStruct.Pin = GPIO_PIN_3;
  GPIO_InitStruct.Alternate = GPIO_AF1_TIM1;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  
  // /* 使能TIM1中断 */
  // HAL_NVIC_SetPriority(TIM1_BRK_UP_TRG_COM_IRQn, 3, 0);
  // HAL_NVIC_EnableIRQ(TIM1_BRK_UP_TRG_COM_IRQn);
}



/**
  * @brief  TIM1初始化函数
  * @param  无
  * @retval 无
  */
void MX_TIM1_Init(void) {

  htim1.Instance = TIM1;/* 选择TIM1 */
  htim1.Init.Period            = 50;/* 自动重装载值 */
  htim1.Init.Prescaler         = 100 - 1;/* 预分频为800-1 */
  htim1.Init.ClockDivision     = TIM_CLOCKDIVISION_DIV1;/* 时钟不分频 */
  htim1.Init.CounterMode       = TIM_COUNTERMODE_UP;/* 向上计数*/
  htim1.Init.RepetitionCounter = 20;/* 不重复计数 */
  htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;/* 自动重装载寄存器没有缓冲 */
  if (HAL_TIM_Base_Init(&htim1) != HAL_OK)/* 基础时钟初始化 */                                
  {
    Error_Handler();
  }

  sConfig.OCMode       = TIM_OCMODE_PWM2;/*输出配置为翻转模式 */
  sConfig.OCPolarity   = TIM_OCPOLARITY_HIGH;/*OC通道输出高电平有效 */
  sConfig.OCFastMode   = TIM_OCFAST_DISABLE;/*输出快速使能关闭 */
  sConfig.OCNPolarity  = TIM_OCNPOLARITY_HIGH;/*OCN通道输出高电平有效 */
  sConfig.OCNIdleState = TIM_OCNIDLESTATE_SET;//TIM_OCNIDLESTATE_RESET;/*空闲状态OC1N输出低电平 */
  sConfig.OCIdleState  = TIM_OCIDLESTATE_SET;//TIM_OCIDLESTATE_RESET;/*空闲状态OC1输出低电平*/
  sConfig.Pulse = 10;/*CC1值为10，占空比=10/50=20%*/                                              
  /* 通道1配置 */
  if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfig, TIM_CHANNEL_2) != HAL_OK)
  {
    Error_Handler();
  }

  /* 通道2开始输出PWM */
  if (HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2) != HAL_OK)                  
  {
    Error_Handler();
  }
}


void set_pwm_configchannel_2( uint8_t pulse ) {
	sConfig.Pulse = pulse;
	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfig, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
}


