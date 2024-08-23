#ifndef __BSP_ST7565__H
#define __BSP_ST7565__H

#include "common.h"

void writeByteData( uint8_t data );
void writeByteCmd( uint8_t cmd );

void display_on_off( uint8_t on );
void display_start_line_set( uint8_t line );
void page_address_set( uint8_t page );
void column_address_set( uint8_t col );
void display_data_write( uint8_t data );
void adc_select( uint8_t val );
void display_normal_reverse( uint8_t val );
void display_all_points_ON_OFF( uint8_t val );
void lcd_bias_set( uint8_t val );
void read_modify_write( void );
void read_modify_write_end( void );
void reset( void );
void common_output_mode_select( uint8_t val );
void power_controller_set( uint8_t val );
void v5_voltage_regulator_internal_resistor_ratio_set( uint8_t val );
void the_electronic_volume( uint8_t val );
void sleep_mode( uint8_t val );
void the_booster_ratio( uint8_t val );
void nop_( void );
void test_( void );

void lcd_init( void );
void lcd_test_display( void );

#endif /*__BSP_ST7565__H*/

