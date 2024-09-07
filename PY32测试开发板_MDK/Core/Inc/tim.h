#ifndef __TIM_H__
#define __TIM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "common.h"

extern TIM_HandleTypeDef htim1;

void MX_TIM1_Init(void);
	
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef* tim_baseHandle);
//void HAL_TIM_Base_MspDeInit(TIM_HandleTypeDef* tim_baseHandle);

void set_pwm_configchannel_2( uint8_t pulse );
	
#endif /*__TIM_H__*/



