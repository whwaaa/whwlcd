#ifndef __COMMON_H__
#define __COMMON_H__

//冲突引脚：
// 1.RST 2.CS  B0
// 1.SDA 2.SCK A2

//128*32长条屏幕 排线丝印：FPC-GG12832-22W-AC
// RST      B0 (冲突，改A4)
// I2C_SCL  A3  
// I2C_SDA  A2
#define RST_GPIO_Port   GPIOB
#define RST_Pin         GPIO_PIN_0

//64*48方形屏 排线丝印：JL-188-6633-A
// CS		B0		CH2
// RST		B1		CH6
// DC		B2		CH4
// SCK		A2		CH0 (冲突，改A5)
// MOSI	    A1		CH1
// BL       B4      CH3
#define Jl188a_CS_GPIO_Port    GPIOB
#define Jl188a_CS_Pin          GPIO_PIN_0
#define Jl188a_RST_GPIO_Port   GPIOB
#define Jl188a_RST_Pin         GPIO_PIN_1
#define Jl188a_DC_GPIO_Port    GPIOB
#define Jl188a_DC_Pin          GPIO_PIN_2
#define Jl188a_BL_GPIO_Port    GPIOB
#define Jl188a_BL_Pin          GPIO_PIN_3

/* LIB ------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>

/* Inc ------------------------------------------------------------*/
#include "main.h"
#include "usart.h"
#include "gpio.h"
#include "tim.h"
#include "i2c.h"
#include "spi.h"

/* BSP ------------------------------------------------------------*/
#include "bsp_font.h"
#include "bsp_st7539.h"
#include "bsp_st7565.h"


/* Tools ------------------------------------------------------------*/


#define FONT0 "获取屏幕开发资料"
#define FONT1 "微信搜索公众号："
#define FONT2 "猫狗之家电子"


#endif /* __COMMON_H__ */
