#include "bsp_st7565.h"

/**
 * Display ON/OFF
 * 
 * 打开或关闭显示器
 * on:1 打开  on:0 关闭
*/
void jl188a_display_on_off( uint8_t on ) {
    uint8_t data;
    if ( on ) {
        data = 0xAF;
    } else {
        data = 0xAE;
    }
    jl188a_writeByteCmd(data);
}

/**
 * Display Start Line Set
 * 
 * 指定显示RAM数据的显示起始行地址
 * line取值：0~63
*/
void jl188a_display_start_line_set( uint8_t line ) {
    uint8_t data;
    if ( line > 0x3F ) {
        line = 0x3F;
    }
    data = 0x40 | line;
    jl188a_writeByteCmd(data);
}

/**
 * 设置页地址
 * 
 * 指定显示RAM数据时对应的页地址
 * page取值：0~8
*/
void jl188a_page_address_set( uint8_t page ) {
    uint8_t data;
    if ( page > 8 ) {
        page = 0;
    }
    data = 0xB0 | page;
    jl188a_writeByteCmd(data);
}

/**
 * 设置列地址
 * 
 * 指定显示RAM数据时对应的列地址
 * col取值：0~131
*/
void jl188a_column_address_set( uint8_t col ) {
    uint8_t data;
    if ( col > 131 ) {
        col = 0;
    }
    data = 0x10 | (col&0xF0) >> 4;
    jl188a_writeByteCmd(data);
    data = 0x00 | (col&0x0F);
    jl188a_writeByteCmd(data);
}

/**
 * 将8位数据写入指定的显示数据RAM地址
*/
void jl188a_display_data_write( uint8_t data ) {
    jl188a_writeByteData(data);
}

/**
 * 
*/
void jl188a_adc_select( uint8_t val ) {
    uint8_t data;
    val = val == 1 ? 1 : 0;
    data = 0xA0 | val;
    jl188a_writeByteCmd(data);
}

/**
 * 屏幕反显
 * val: 0正显 1反显
*/
void jl188a_display_normal_reverse( uint8_t val ) {
    uint8_t data;
    val = val == 1 ? 1 : 0;
    data = 0xA6 | val;
    jl188a_writeByteCmd(data);
}

/**
 * 不管RAM的内容是什么，强制打开所有的显示
 * val: 0默认 1强制
*/
void jl188a_display_all_points_ON_OFF( uint8_t val ) {
    uint8_t data;
    val = val == 1 ? 1 : 0;
    data = 0xA4 | val;
    jl188a_writeByteCmd(data);
}

/**
 * 选择电压偏置比
 * val: 0 1
 * 
*/
void jl188a_lcd_bias_set( uint8_t val ) {
    uint8_t data;
    val = val == 1 ? 1 : 0;
    data = 0xA2 | val;
    jl188a_writeByteCmd(data);
}

/**
 * 临时修改某个位置的数据时设置
 * 执行End命令后，col地址恢复到之前
*/
void jl188a_read_modify_write( void ) {
    jl188a_writeByteCmd(0xE0);
}

/**
 * End，col地址恢复到之前
*/
void jl188a_read_modify_write_end( void ) {
    jl188a_writeByteCmd(0xEE);
}

/**
 * 复位
*/
void jl188a_reset( void ) {
    jl188a_writeByteCmd(0xE2);
}

/**
 * 选择COM输出终端的扫描方向,详细信息请参见
 * "Common Output Mode Select Circuit."
*/
void jl188a_common_output_mode_select( uint8_t val ) {
    uint8_t data;
    val = val == 1 ? 1 : 0;
    data = 0xC0 | (val<<3);
    jl188a_writeByteCmd(data);
}

/**
 * 设置电源电路功能
 * val: 0~7
*/
void jl188a_power_controller_set( uint8_t val ) {
    uint8_t data;
    if ( val > 7 ) {
        val = 0;
    }
    data = 0x28 | val;
    jl188a_writeByteCmd(data);
}

/**
 * 设置V5电压调节器内部电阻比率
 * val: 0~7
*/
void jl188a_v5_voltage_regulator_internal_resistor_ratio_set( uint8_t val ) {
    uint8_t data;
    if ( val > 7 ) {
        val = 0;
    }
    data = 0x20 | val;
    jl188a_writeByteCmd(data);
}

/**
 * 设置对比度
*/
void jl188a_the_electronic_volume( uint8_t val ) {
    if ( val > 63 ) {
        val = 0;
    }
    jl188a_writeByteCmd(81);
    jl188a_writeByteCmd(val);
}

/**
 * 睡眠模式
 * val：0工作 1睡眠
*/
void jl188a_sleep_mode( uint8_t val ) {
    uint8_t data;
    val = val == 1 ? 1 : 0;
    data = 0xAC | val;
    jl188a_writeByteCmd(data);
    jl188a_writeByteCmd(0x00);
}

/**
 * booster 设置
 * val: 0~2
*/
void jl188a_the_booster_ratio( uint8_t val ) {
    if ( val > 2 ) {
        val = 0;
    }
    jl188a_writeByteCmd(0xF8);
    jl188a_writeByteCmd(val);
}

/**
 * 空指令
*/
void jl188a_nop_( void ) {
    jl188a_writeByteCmd(0xE3);
}

/**
 * 测试指令
*/
void jl188a_test_( void ) {
    jl188a_writeByteCmd(0xFC);
}


