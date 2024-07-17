#include "bsp_st7539.h"

/*
* 功能: 定时器3,us级延时
*	参数: xus, 范围0~65535us
*/
void Delay_Us(uint16_t t){
  uint16_t counter = 0;
	__HAL_TIM_SET_AUTORELOAD( &htim1, t );//设置定时器自动重装载的值, 到该值后重新计数
	__HAL_TIM_SET_COUNTER( &htim1, 0 );//设置定时器初始值
	HAL_TIM_Base_Start( &htim1 );//启动定时器
	while ( counter != t ) {
		counter = __HAL_TIM_GET_COUNTER(&htim1);//获取定时器当前计数值
	}
	HAL_TIM_Base_Stop( &htim1 );//停止定时器
}
void Delay_Ms(uint32_t t){
  while(t--) Delay_Us( 1000 );
}
void Delay_S(uint32_t t){
  while(t--) Delay_Ms( 1000 );
}

static void my_printf( uint8_t cmd, uint8_t code ) {
    switch (code)
    {
    case 0x01:
        printf("写入0x%02X异常 HAL_ERROR\n", cmd);
        break;
    case 0x02:
        printf("写入0x%02X异常 HAL_BUSY\n", cmd);
        break;
    case 0x03:
        printf("写入0x%02X异常 HAL_TIMEOUT\n", cmd);
        break;
    default:
        break;
    }
}
static void my_printf2( uint8_t cmd, uint8_t code ) {
    switch (code)
    {
    case 0x01:
        printf("写入colum 0x%02X异常 HAL_ERROR\n", cmd);
        break;
    case 0x02:
        printf("写入colum 0x%02X异常 HAL_BUSY\n", cmd);
        break;
    case 0x03:
        printf("写入colum 0x%02X异常 HAL_TIMEOUT\n", cmd);
        break;
    default:
        break;
    }
}

void lcd_init( void ) {
//HAL_OK       = 0x00U,
//HAL_ERROR    = 0x01U,
//HAL_BUSY     = 0x02U,
//HAL_TIMEOUT  = 0x03U
    uint8_t res;
    uint8_t data[1];
    //复位
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_SET );
    vTaskDelay(100);
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET );
    vTaskDelay(200);
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_SET );
    vTaskDelay(200);

    data[0] = 0xE2;//Software Reset
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0xA3;//Set Frame Rate 设置帧率 (FR1:0 FR1:176fps +- 15%)11:168fps
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0xEB;//Set Bias Ratio 设置偏差 1/8
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0xC2;//Set Scan Direction Y0(从上到下？) X1(从右到左？)
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0x81;//Set Contraset (设置对比度) (2-byte instruction. Set display duty)
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0x28;//对比度值
    HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    data[0] = 0x40;//Set Scroll Line 设置0行
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0xF1;//Set COM End (部分显示用)
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0xFF;//1/(64+1)
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);
    data[0] = 0xAF;//Set Display Enable
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, data, 1, 1000 );
    if ( res != 0 ) my_printf(data[0], res);


}


static void writeData( uint8_t data ) {
    uint8_t res;
    //printf("写入数据: %02X\n", data);
    res = HAL_I2C_Master_Transmit( &hi2c1, W_DAT_ADDRESS, &data, 1, 1000 );
    if ( res != 0 ) my_printf(data, res);
}

static void setCursor( uint8_t y, uint8_t x ) {
    uint8_t cache;
    uint8_t res;
    //设置行坐标
    printf("设置y坐标..%d\n", y);
    cache = y|0x40;
    res = HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, &cache, 1, 1000 );
    if ( res != 0 ) my_printf(cache, res);

    //设置低位列坐标
    printf("设置低位x坐标..%d\n", x);
    cache = x&0x0F;
    HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, &cache, 1, 1000 );
    if ( res != 0 ) my_printf(cache, res);

    //设置高位列坐标
    printf("设置高位x坐标..%d\n", x);
    cache = ((x&0xF0)>>4)|0x10;
    HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, &cache, 1, 1000 );
    if ( res != 0 ) my_printf(cache, res);
}

void column_set( uint8_t col ) {
    uint8_t cache,res;
    //设置低位列坐标
    printf("设置低位x坐标..%d\n", col);
    cache = col&0x0F;
    HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, &cache, 1, 1000 );
    if ( res != 0 ) my_printf(cache, res);

    //设置高位列坐标
    printf("设置高位x坐标..%d\n", col);
    cache = ((col&0xF0)>>4)|0x10;
    HAL_I2C_Master_Transmit( &hi2c1, W_CMD_ADDRESS, &cache, 1, 1000 );
    if ( res != 0 ) my_printf(cache, res);
}

void lcd_display_test( void ) {
    uint8_t cache, res;
}


