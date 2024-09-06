#ifndef __COMMON_H__
#define __COMMON_H__

#define SLIDE_STR "微信搜索公众号：猫狗之家电子获取屏幕开发资料 "

/* LIB ------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "main.h"
#include "tim.h"
#include "usart.h"
#include "spi.h"
#include "stm32f1xx_it.h"

/* BSP ------------------------------------------------------------*/
#include "bsp_st7539.h"

/* FreeRTOS ------------------------------------------------------------*/
#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "event_groups.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define FW_VERSION  "V1.0.0"


#endif /* __COMMON_H__ */



