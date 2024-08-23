#include "bsp_st7565.h"
#include "bsp_font.h"

//SPI接口写数据
void writeByteData( uint8_t data ) {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);//CS_L
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_SET);//1数据
    HAL_SPI_Transmit( &hspi1, &data, 1, 1000 );
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);//CS_H
}

//SPI接口写命令
void writeByteCmd( uint8_t cmd ) {
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);//CS_L
    HAL_GPIO_WritePin(DC_GPIO_Port, DC_Pin, GPIO_PIN_RESET);//0命令
    HAL_SPI_Transmit( &hspi1, &cmd, 1, 1000 );
    HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);//CS_H
}

void lcd_clear( void ) {
    for ( uint8_t i=0; i<8; i++ ) {
        page_address_set(i);
        column_address_set(0);
        for ( uint8_t j=0; j<132; j++ ) {
            display_data_write(0x00);
        }
    }
}

void lcd_init( void ) {
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);
    HAL_Delay(200);

    reset();//复位
    adc_select(1);
    HAL_Delay(100);
    power_controller_set(4);//Voltage Coboost ON 
    HAL_Delay(10);
    power_controller_set(6);//Voltage Regulator ON 
    HAL_Delay(10);
    power_controller_set(7);//Voltage Follower ON 
    HAL_Delay(10);

    lcd_bias_set(0);//默认设置Bias 1/9
    HAL_Delay(10);

    //电阻率选择
    v5_voltage_regulator_internal_resistor_ratio_set(7);
    HAL_Delay(10);

    //对比度设置
    the_electronic_volume(2);
    HAL_Delay(10);

    //初始化显示行0-63
    display_start_line_set(0);
    HAL_Delay(10);
    //display_all_points_ON_OFF();

    display_on_off(1);//开启显示
    //display_normal_reverse(0);//反显

    lcd_clear();

}



uint8_t data[100];
void lcd_test_display( void ) {
    

    page_address_set(1);
    column_address_set(0);
    for ( uint8_t i=0; i<50; i++ ) {
        //data[i] = 0x01;
        display_data_write(0x0F);
    }
    for ( uint8_t i=50; i<132; i++ ) {
        //data[i] = 0x01;
        display_data_write(0xF0);
    }

    // page_address_set(1);
    // column_address_set(0);
    // for ( uint8_t i=0; i<40; i++ ) {
    //     display_data_write(0x03);
    // }

    // for ( uint8_t i=0; i<10; i++ ) {
    //     //data[i] = 0x01;
    //     display_data_write(0xC3);
    // }

    //display_on_off(0);
    // for ( uint8_t i=0; i<10; i++ ) {
    //     //data[i] = 0x02;
    //     display_data_write(0x02);
    // }
    // for ( uint8_t i=0; i<10; i++ ) {
    //     //data[i] = 0xF0;
    //     display_data_write(0xF0);
    // }
    //  for ( uint8_t i=0; i<10; i++ ) {
    //     //data[i] = 0xF0;
    //     display_data_write(0xFF);
    // }
    display_on_off(1);//开启显示

}

