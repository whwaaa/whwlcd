#ifndef __BSP_ST7539__H
#define	__BSP_ST7539__H

#include "common.h"


//ST7539 https://www.doc88.com/p-142668406745.html 英文手册

#define HI2Cx    hi2c1

//写命令地址
#define W_CMD_ADDRESS  0x7C
//写数据地址
#define W_DAT_ADDRESS  0x7E
//读数据地址
#define R_DAT_ADDRESS  0x7F


void fpcgg122_writeByteData( uint8_t data );
void fpcgg122_writeByteCmd( uint8_t cmd );

//设置RAM的数据列地址（写入数据前设置）
void fpcgg122_lcd_set_column_address( uint8_t column );
//设置屏幕显示区顶部所在的RAM数据行
void fpcgg122_lcd_set_scroll_line( uint8_t line );
//设置RAM的数据页地址（写入数据前设置）
void fpcgg122_lcd_set_page_address( uint8_t page );
//设置对比度
void fpcgg122_lcd_set_contraset( uint8_t contraset );
//部分屏模式
void fpcgg122_lcd_set_partial_screen_mode( uint8_t ps );
//控制DDRAM显示的扫描方式
void fpcgg122_lcd_set_ram_address_control( uint8_t ac );
//设置帧率
void fpcgg122_lcd_set_frame_rate( uint8_t frate );
void fpcgg122_lcd_all_pixel_on( uint8_t ap );
void fpcgg122_lcd_set_inverse_display( uint8_t inv );
//显示开启
void fpcgg122_lcd_set_display_enable( uint8_t pd );
//设置扫描方向
void fpcgg122_lcd_set_scan_direction( uint8_t scan );
//软件复位
void fpcgg122_lcd_software_reset( void );
//空操作指令
void fpcgg122_lcd_nop( void );
//设置偏差
void fpcgg122_lcd_set_bias_ratio( uint8_t ratio );
//设置局部显示
void fpcgg122_lcd_set_com_end( uint8_t comEnd );
void fpcgg122_lcd_set_partial_start_address( uint8_t dst );
void fpcgg122_lcd_set_partial_end_address( uint8_t den );
//选择测试命令表
void fpcgg122_lcd_test_control( uint8_t h );

void fpcgg122_lcd_clear( void );
void fpcgg122_lcd_clear_part( uint8_t pageStart, uint8_t pageSize, uint8_t colStart, uint8_t colSize );
void fpcgg122_lcd_init( void );

void fpcgg122_writeFont_16x16( uint8_t x, uint8_t y, char *font );
void fpcgg122_writeFont_24x24( uint8_t x, uint8_t y, char *font );
void fpcgg122_writeFont_32x32( uint8_t x, uint8_t y, char *font );
void fpcgg122_writeLogo_0( uint8_t x, uint8_t y );
void fpcgg122_writeFont_ASCII8x16( uint8_t x, uint8_t y, char *data, uint8_t isBold );

void fpcgg122_lcd_demo0( void );
void fpcgg122_lcd_demo1( void );
void fpcgg122_lcd_demo2( void );

#endif /*__BSP_ST7539__H*/


