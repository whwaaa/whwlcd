#ifndef __BSP_ST7539__H
#define	__BSP_ST7539__H

#include "common.h"

//ST7539 https://www.doc88.com/p-142668406745.html 英文手册

//写命令地址
#define W_CMD_ADDRESS  0x7C
//写数据地址
#define W_DAT_ADDRESS  0x7E

//读命令地址??
#define R_CMD_ADDRESS  0x7B
//读数据地址
#define R_DAT_ADDRESS  0x7F

void Delay_Us(uint16_t t);
void lcd_init( void );

void lcd_display_test( void );







#endif /*__BSP_ST7539__H*/


