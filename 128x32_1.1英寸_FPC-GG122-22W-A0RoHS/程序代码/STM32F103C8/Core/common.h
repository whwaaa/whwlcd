#ifndef __COMMON_H__
#define __COMMON_H__


/* LIB ------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include "main.h"
#include "i2c.h"
#include "tim.h"
#include "usart.h"
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

#define FW_VERSION  "V1.0.1"


#endif /* __COMMON_H__ */



