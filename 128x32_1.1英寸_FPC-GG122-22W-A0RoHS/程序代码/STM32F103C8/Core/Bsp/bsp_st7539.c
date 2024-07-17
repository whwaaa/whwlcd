#include "bsp_st7539.h"

//IIC接口写数据
void writeByteData( uint8_t data ) {
    HAL_I2C_Master_Transmit( &HI2Cx, W_DAT_ADDRESS, &data, 1, 1000 );
}

//IIC接口写命令
void writeByteCmd( uint8_t cmd ) {
    HAL_I2C_Master_Transmit( &HI2Cx, W_DAT_ADDRESS, &cmd, 1, 1000 );
}

void lcd_init( void ) {
    uint8_t res;
    uint8_t data[1];
    //复位
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_SET );
    vTaskDelay(100);
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET );
    vTaskDelay(200);
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_SET );
    vTaskDelay(200);

    writeByteCmd(0xE2);//Software Reset
    writeByteCmd(0xA3);//Set Frame Rate 设置帧率 (FR1:0 FR1:176fps +- 15%)11:168fps
    writeByteCmd(0xEB);//Set Bias Ratio 设置偏差 1/8
    writeByteCmd(0xC2);//Set Scan Direction Y0(从上到下？) X1(从右到左？)
    writeByteCmd(0x81);//Set Contraset (设置对比度) (2-byte instruction. Set display duty)
    writeByteCmd(0x28);//对比度值
    writeByteCmd(0x40);//Set Scroll Line 设置0行
    writeByteCmd(0xF1);//Set COM End (部分显示用)
    writeByteCmd(0xFF);//1/(64+1)
    writeByteCmd(0xAF);//Set Display Enable


}

//清屏，清空 RAM 64*192bit
//分8个页，每页数据8bit*192
void lcd_clear( void ) {
    uint8_t data;
    for ( uint8_t page=0; page<8; page++ ) {
        //Set Page Address
        writeByteCmd(0xB0|page);
        //Set Column
        writeByteCmd(0);//0列，低位
        writeByteCmd(0x10|0);//0列，高位
        //Write Data
        for ( int i=0; i<192; i++ ) {
            writeByteData(0);
        }
    }
}

//写数据到RAM的指定地址
void writeDataToRAM( uint8_t page, uint8_t startCol, uint8_t endCol, uint8_t *pdata ) {

    if ( startCol>=endCol || endCol==0 ) return;

    //设置RAM页地址
    lcd_set_page_address(page);
    
    //设置RAM列地址
    lcd_set_column_address(startCol);
    
    //写入数据
    for ( uint8_t i=startCol; i<=endCol; i++ ) {
        writeByteData(pdata[i]);
    }
}

void lcd_display_test( void ) {
    uint8_t data[100];
    for ( int i=0; i<80; i++ ) {
        data[i] = i/8;
    }
    lcd_init();
    lcd_clear();

    writeDataToRAM(0, 100, 180, data);
}


