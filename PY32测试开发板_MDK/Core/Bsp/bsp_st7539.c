#include "bsp_st7539.h"
#include "bsp_font.h"

//IIC接口写数据
void writeByteData( uint8_t data ) {
    HAL_I2C_Master_Transmit( &HI2Cx, W_DAT_ADDRESS, &data, 1, 1000 );
}

//IIC接口写命令
void writeByteCmd( uint8_t cmd ) {
    HAL_I2C_Master_Transmit( &HI2Cx, W_CMD_ADDRESS, &cmd, 1, 1000 );
}

/**
 * LCD初始化
 */
void lcd_init( void ) {
    //复位
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_SET );
    HAL_Delay(100);
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET );
    HAL_Delay(200);
    HAL_GPIO_WritePin( RST_GPIO_Port, RST_Pin, GPIO_PIN_SET );
    HAL_Delay(200);
    
    // lcd_software_reset();//软件复位（默认值）
    // lcd_set_frame_rate(1);//设置帧率（默认值）
    // lcd_set_bias_ratio(3);//设置偏差（默认值）
    lcd_set_scan_direction(1);//设置扫描方向(上到下左到右)
    // lcd_set_inverse_display(1);//反显
    lcd_set_contraset(0x30);//设置对比度
    // lcd_set_scroll_line(0);//设置屏幕显示区顶部所在的RAM数据行（默认值）
    lcd_set_display_enable(1);//使能
}

/**
 * 清屏，清空 RAM 64*192bit
 * 分8个页，每页数据8bit*192 (其中192列地址，显示区只显示0~127的数据)
 */
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

/**
 * 部分清屏
 * pageStart: 0~7
 * colStart: 0~127
 */
void lcd_clear_part( uint8_t pageStart, uint8_t pageSize, uint8_t colStart, uint8_t colSize ) {
    uint8_t data;
    if ( pageSize==0 || colSize==0 ) return;
    if ( pageStart + pageSize > 8 ) return;
    if ( colStart + colSize > 128 ) return;
    for ( uint8_t page=pageStart; page<8; page++ ) {
        //Set Page Address
        writeByteCmd(0xB0|page);
        //Set Column
        writeByteCmd(colStart);//低位
        writeByteCmd(0x10|colStart);//高位
        //Write Data
        for ( int i=colStart; i<128; i++ ) {
            writeByteData(0);
        }
    }
}

/**
 * 指定位置写入数据
 * page：取值0~7共8页数据页
 * startX：起始x坐标，取值0~127
 * endX：最后x坐标，必须大于startX，取值0~127
 * pdata：数据长度必须大于等于(startX-endX+1)
 */
void writeDataToRAM( uint8_t page, uint8_t startX, uint8_t endX, uint8_t *pdata ) {
    uint8_t xlen;

    if ( startX>endX || endX==0 || endX>127 ) return;
    xlen = endX - startX + 1;

    //设置RAM页地址
    lcd_set_page_address(page);
    
    //设置RAM列地址
    lcd_set_column_address(startX);
    
    //写入数据
    for ( uint8_t i=0; i<xlen; i++ ) {
        writeByteData(pdata[i]);
    }
}

/**
 * 显示8x16大小ASCII字符
 * x取值：0~127
 * y取值：0~63
 * data：显示的数据
 * isBold：1粗体，0非粗体
*/
void writeFont_ASCII8x16( uint8_t x, uint8_t y, char *data, uint8_t isBold ) {
    uint8_t page, fontLen, yu, xlen_t, (*asciiFont_t)[16], pNum;
    uint16_t xlen;

    xlen = strlen(data) * 8;//utf8一个字3字节
    xlen = xlen > (128 - x) ? (128 - x) : xlen;
    fontLen = strlen(data);//字数长度
    //计算RAM页地址(0~3)
    page = y / 8;
    yu = y % 8;
    if ( isBold ) {
        asciiFont_t = (uint8_t (*)[16])asciiFont_bold;
    } else {
        asciiFont_t = (uint8_t (*)[16])asciiFont;
    }
    if ( yu == 0 ) {
        pNum = 2;//一个字高16占2页
    } else {
        pNum = 3;//一个字高16占3页
    }

    for ( uint8_t i=0; i<pNum&&page<9; i++,page++ ) {
        xlen_t = xlen;
        //设置RAM列地址
        lcd_set_column_address(x);
        //设置RAM页地址
        lcd_set_page_address(page);
        if ( yu == 0 ) {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(asciiFontIdx)); idx++ ) {
                     if ( data[b] == asciiFontIdx[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<8&&xlen_t>0; j++ ) {
                            xlen_t--;
                            writeByteData(asciiFont_t[idx][i*8+j]);
                        }
                        break;
                    }
                }
            }
        } else {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(asciiFontIdx)); idx++ ) {
                     if ( data[b] == asciiFontIdx[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<8&&xlen_t>0; j++ ) {
                            xlen_t--;
                            if ( i == 0 ) {
                                writeByteData(asciiFont_t[idx][i*8+j]<<yu);
                            } else if ( i == 1 ) {
                                writeByteData(asciiFont_t[idx][j]>>(8-yu)|asciiFont_t[idx][i*8+j]<<yu);
                            } else if ( i == 2 ) {
                                writeByteData(asciiFont_t[idx][j]>>(8-yu));
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**
 * 显示16x16字符
 * x取值：0~127
 * y取值：0~63
 * data：显示的数据
*/
void writeFont_16x16( uint8_t x, uint8_t y, char *font ) {
    uint8_t page, fontLen, yu, pNum;
    uint16_t xlen, xlen_t;

    xlen = strlen(font) / 3 * 16;//utf8一个字3字节
    xlen = xlen > (128 - x) ? (128 - x) : xlen;
    fontLen = (xlen+15)/16;//字数长度
    //计算RAM页地址(0~3)
    page = y / 8;
    yu = y % 8;
    if ( yu == 0 ) {
        pNum = 2;//一个字高16占2页
    } else {
        pNum = 3;//一个字高16占3页
    }

    //一个字高16占2页
    for ( uint8_t i=0; i<pNum&&page<9; i++,page++ ) {
        xlen_t = xlen;
        //设置RAM列地址
        lcd_set_column_address(x);
        //设置RAM页地址
        lcd_set_page_address(page);

        if ( yu == 0 ) {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_16)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_16[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<16&&xlen_t>0; j++ ) {
                            xlen_t--;
                            writeByteData(myFont_16[idx*2+i][j]);
                        }
                        break;
                    }
                }
            }
        } else {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_16)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_16[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<16&&xlen_t>0; j++ ) {
                            xlen_t--;
                            if ( i == 0 ) {
                                writeByteData(myFont_16[idx*2+i][j]<<yu);
                            } else  if ( i == 1 ) {
                                writeByteData(myFont_16[idx*2+i][j]>>(8-yu)|(myFont_16[idx*2+i][j]<<yu));
                            } else  if ( i == 2 ) {
                                writeByteData(myFont_16[idx*2+i][j]>>(8-yu));
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**
 * 显示21x21字符
 * x取值：0~127
 * y取值：0~63
 * data：显示的数据
*/
void writeFont_21x21( uint8_t x, uint8_t y, char *font ) {
    uint8_t page, fontLen, yu, pNum;
    uint16_t xlen, xlen_t;

    xlen = strlen(font) / 3 * 21;//utf8一个字3字节
    xlen = xlen > (128 - x) ? (128 - x) : xlen;
    fontLen = (xlen+20)/21;//字数长度
    //计算RAM页地址(0~3)
    page = y / 8;
    yu = y % 8;
    if ( yu == 0 ) {
        pNum = 3;//一个字高21占3页
    } else {
        pNum = 4;//一个字高21占4页
    }

    for ( uint8_t i=0; i<pNum&&page<9; i++,page++ ) {
        xlen_t = xlen;
        //设置RAM列地址
        lcd_set_column_address(x);
        //设置RAM页地址
        lcd_set_page_address(page);

        if ( yu == 0 ) {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_21)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_21[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<21&&xlen_t>0; j++ ) {
                            xlen_t--;
                            writeByteData(myFontBold_21[idx*3+i][j]);
                        }
                        break;
                    }
                }
            }
        } else {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_21)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_21[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<21&&xlen_t>0; j++ ) {
                            xlen_t--;
                            if ( i == 0 ) {
                                writeByteData(myFontBold_21[idx*3+i][j]<<yu);
                            } else if ( i == 1 ) {
                                writeByteData((myFontBold_21[idx*3+(i-1)][j]>>(8-yu))|(myFontBold_21[idx*3+i][j]<<yu));
                            } else if ( i == 2 ) {
                                writeByteData((myFontBold_21[idx*3+(i-1)][j]>>(8-yu))|(myFontBold_21[idx*3+i][j]<<yu));
                            } else if ( i == 3 ) {
                                writeByteData(myFontBold_21[idx*3+(i-1)][j]>>(8-yu));
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**
 * 显示24x24字符
 * x取值：0~127
 * y取值：0~63
 * data：显示的数据
*/
void writeFont_24x24( uint8_t x, uint8_t y, char *font ) {
    uint8_t page, fontLen, yu, pNum;
    uint16_t xlen, xlen_t;

    xlen = strlen(font) / 3 * 24;//utf8一个字3字节
    xlen = xlen > (128 - x) ? (128 - x) : xlen;
    fontLen = (xlen+23)/24;//字数长度
    //计算RAM页地址(0~3)
    page = y / 8;
    yu = y % 8;
    if ( yu == 0 ) {
        pNum = 3;//一个字高24占3页
    } else {
        pNum = 4;//一个字高24占4页
    }

    for ( uint8_t i=0; i<pNum&&page<9; i++,page++ ) {
        xlen_t = xlen;
        //设置RAM列地址
        lcd_set_column_address(x);
        //设置RAM页地址
        lcd_set_page_address(page);

        if ( yu == 0 ) {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_24)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_24[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<24&&xlen_t>0; j++ ) {
                            xlen_t--;
                            writeByteData(myFont_24[idx*3+i][j]);
                        }
                        break;
                    }
                }
            }
        } else {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_24)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_24[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<24&&xlen_t>0; j++ ) {
                            xlen_t--;
                            if ( i == 0 ) {
                                writeByteData(myFont_24[idx*3+i][j]<<yu);
                            } else if ( i == 1 ) {
                                writeByteData((myFont_24[idx*3+(i-1)][j]>>(8-yu))|(myFont_24[idx*3+i][j]<<yu));
                            } else if ( i == 2 ) {
                                writeByteData((myFont_24[idx*3+(i-1)][j]>>(8-yu))|(myFont_24[idx*3+i][j]<<yu));
                            } else if ( i == 3 ) {
                                writeByteData(myFont_24[idx*3+(i-1)][j]>>(8-yu));
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**
 * 显示32x32字符
 * x取值：0~127
 * y取值：0~63
 * data：显示的数据
*/
void writeFont_32x32( uint8_t x, uint8_t y, char *font ) {
    uint8_t page, fontLen, yu, pNum;
    uint16_t xlen, xlen_t;

    xlen = strlen(font) / 3 * 32;//utf8一个字3字节
    xlen = xlen > (128 - x) ? (128 - x) : xlen;
    fontLen = (xlen+31)/32;//字数长度
    //计算RAM页地址(0~3)
    page = y / 8;
    yu = y % 8;
    if ( yu == 0 ) {
        pNum = 4;//一个字高32占4页
    } else {
        pNum = 5;//一个字高32占5页
    }

    for ( uint8_t i=0; i<pNum&&page<9; i++,page++ ) {
        xlen_t = xlen;
        //设置RAM列地址
        lcd_set_column_address(x);
        //设置RAM页地址
        lcd_set_page_address(page);

        if ( yu == 0 ) {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_32)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_32[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<32&&xlen_t>0; j++ ) {
                            xlen_t--;
                            writeByteData(myFont_32[idx*4+i][j]);
                        }
                        break;
                    }
                }
            }
        } else {
            //遍历所有字
            for ( uint8_t b=0; b<fontLen; b++ ) {
                //查找font索引
                for ( uint8_t idx=0; idx<(sizeof(myFontIdx_32)/3); idx++ ) {
                    if ( (uint32_t)(font[b*3]<<16|font[b*3+1]<<8|font[b*3+2]) == myFontIdx_32[idx] ) {//查找到font索引
                        //写入一个字font数据
                        for ( uint8_t j=0; j<32&&xlen_t>0; j++ ) {
                            xlen_t--;
                            if ( i == 0 ) {
                                writeByteData(myFont_32[idx*4+i][j]<<yu);
                            } else if ( i == 1 ) {
                                writeByteData((myFont_32[idx*4+(i-1)][j]>>(8-yu))|(myFont_32[idx*4+i][j]<<yu));
                            } else if ( i == 2 ) {
                                writeByteData((myFont_32[idx*4+(i-1)][j]>>(8-yu))|(myFont_32[idx*4+i][j]<<yu));
                            } else if ( i == 3 ) {
                                writeByteData((myFont_32[idx*4+(i-1)][j]>>(8-yu))|(myFont_32[idx*4+i][j]<<yu));
                            } else if ( i == 4 ) {
                                writeByteData(myFont_32[idx*4+(i-1)][j]>>(8-yu));
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}

/**
 * 显示logo
 * x取值：0~127
 * y取值：0~63
 * data：显示的数据
*/
void writeLogo_0( uint8_t x, uint8_t y ) {
    uint8_t page, xlen, xlen_t, yu, pNum;

    xlen = 128 - x;
    page = y / 8;
    yu = y % 8;
    if ( yu == 0 ) {
        pNum = 4;//高64占4页
    } else {
        pNum = 5;//高64占5页
    }

    for ( uint8_t i=0; i<pNum&&page<9; i++,page++ ) {
        xlen_t = xlen;
        //设置RAM列地址
        lcd_set_column_address(x);
        //设置RAM页地址
        lcd_set_page_address(page);
        if ( yu == 0 ) {
            for ( uint8_t j=0; j<32&&xlen_t>0; j++ ) {
                xlen_t--;
                writeByteData(logo_0[i][j]);
            }
        } else {
            for ( uint8_t j=0; j<32&&xlen_t>0; j++ ) {
                xlen_t--;
                if ( i == 0 ) {
                    writeByteData(logo_0[i][j]<<yu);
                } else if ( i == 1 ) {
                    writeByteData(logo_0[i-1][j]>>(8-yu)|logo_0[i][j]<<yu);
                } else if ( i == 2 ) {
                    writeByteData(logo_0[i-1][j]>>(8-yu)|logo_0[i][j]<<yu);
                } else if ( i == 3 ) {
                    writeByteData(logo_0[i-1][j]>>(8-yu)|logo_0[i][j]<<yu);
                } else if ( i == 4 ) {
                    writeByteData(logo_0[i-1][j]>>(8-yu));
                }
            } 
        }
    }
}


void lcd_demo( void ) {
    lcd_init();//初始化
    lcd_clear();//清屏
    writeFont_16x16(0, 0, FONT0);
    writeFont_16x16(0, 16, FONT1);
    /* Infinite loop */
    for(;;)
    {
        lcd_set_scroll_line(0);//从0行显示（0~3页）
        HAL_Delay(5000);

        lcd_clear_part(4, 4, 0, 127);
        writeFont_21x21(0, 32+6, FONT2);
        lcd_set_scroll_line(32);//从32行显示（4~7页）

        HAL_Delay(5000);
        lcd_clear_part(4, 4, 0, 127);
        writeLogo_0(45, 36);
        HAL_Delay(3000);
    }
}

