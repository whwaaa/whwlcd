#ifndef __BSP_ST7565__H
#define __BSP_ST7565__H

#include "common.h"

void jl188a_writeByteData( uint8_t data );
void jl188a_writeByteCmd( uint8_t cmd );

void jl188a_display_on_off( uint8_t on );
void jl188a_display_start_line_set( uint8_t line );
void jl188a_page_address_set( uint8_t page );
void jl188a_column_address_set( uint8_t col );
void jl188a_display_data_write( uint8_t data );
void jl188a_adc_select( uint8_t val );
void jl188a_display_normal_reverse( uint8_t val );
void jl188a_display_all_points_ON_OFF( uint8_t val );
void jl188a_lcd_bias_set( uint8_t val );
void jl188a_read_modify_write( void );
void jl188a_read_modify_write_end( void );
void jl188a_reset( void );
void jl188a_common_output_mode_select( uint8_t val );
void jl188a_power_controller_set( uint8_t val );
void jl188a_v5_voltage_regulator_internal_resistor_ratio_set( uint8_t val );
void jl188a_the_electronic_volume( uint8_t val );
void jl188a_sleep_mode( uint8_t val );
void jl188a_the_booster_ratio( uint8_t val );
void jl188a_nop_( void );
void jl188a_test_( void );

void jl188a_lcd_init( void );
void jl188a_lcd_clear( void );
void jl188a_writeDataToRAM( uint8_t page, uint8_t startX, uint8_t endX, uint8_t *pdata );
void jl188a_writeFont_ASCII8x16( uint8_t x, uint8_t y, char *data, uint8_t isBold );
void jl188a_writeFont_16x16( uint8_t x, uint8_t y, char *font );
void jl188a_writeFont_24x24( uint8_t x, uint8_t y, char *font );
void jl188a_writeFont_32x32( uint8_t x, uint8_t y, char *font );
void jl188a_slideFont32x32( uint8_t width, uint8_t x, uint8_t y, char *font, uint16_t fIdx );
void jl188a_writeLogo_0( uint8_t x, uint8_t y );

void jl188a_lcd_display_demo0( void );
void jl188a_lcd_display_demo1( void );
uint8_t jl188a_check_isExist( void );
#endif /*__BSP_ST7565__H*/

