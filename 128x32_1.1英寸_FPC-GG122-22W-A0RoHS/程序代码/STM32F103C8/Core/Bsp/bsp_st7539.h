#ifndef __BSP_ST7539__H
#define	__BSP_ST7539__H

#include "common.h"

//ST7539 https://www.doc88.com/p-142668406745.html 英文手册

#define HI2Cx    hi2c1

//写命令地址
#define W_CMD_ADDRESS  0x7C
//写数据地址
#define W_DAT_ADDRESS  0x7E

// //读命令地址??
// #define R_CMD_ADDRESS  0x7B
//读数据地址
#define R_DAT_ADDRESS  0x7F


void writeByteData( uint8_t data );
void writeByteCmd( uint8_t cmd );


void lcd_set_column_address( uint8_t column );
void lcd_set_scroll_line( uint8_t line );
void lcd_set_page_address( uint8_t page );
void lcd_set_contraset( uint8_t contraset );
void lcd_set_partial_screen_mode( uint8_t ps );
void lcd_set_ram_address_control( uint8_t ac );
void lcd_set_frame_rate( uint8_t frate );
void lcd_all_pixel_on( uint8_t ap );
void lcd_set_inverse_display( uint8_t inv );
void lcd_set_display_enable( uint8_t pd );
void lcd_set_scan_direction( uint8_t scan );
void lcd_software_reset( void );
void lcd_nop( void );
void lcd_set_bias_ratio( uint8_t ratio );
void lcd_set_com_end( uint8_t comEnd );
void lcd_set_partial_start_address( uint8_t dst );
void lcd_set_partial_end_address( uint8_t den );
void lcd_test_control( uint8_t h );


void lcd_clear( void );
void lcd_init( void );


void lcd_display_test( void );







#endif /*__BSP_ST7539__H*/


