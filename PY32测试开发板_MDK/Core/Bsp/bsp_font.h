#ifndef __BSP_FONT__H
#define __BSP_FONT__H

#include "common.h"

//阴码，逆向，列行式
extern uint8_t logo_0[4][32];

//获取屏幕开发资料微信搜索公众号：猫狗之家电子
extern const uint32_t myFontIdx_16[22];
//微软雅黑 Light，16x16，等比缩放
extern const uint8_t myFont_16[44][32];

//获取屏幕开发资料微信搜索公众号：猫狗之家电子
extern const uint32_t myFontIdx_21[22];
//微软雅黑 21x21，加粗，等比缩放
extern const uint8_t myFontBold_21[66][21];

#if USE_24x24_FONT
extern const uint32_t myFontIdx_24[4];
//微软雅黑 24x24，加粗，等比缩放
extern const uint8_t myFont_24[16][24];
#else
extern const uint32_t myFontIdx_24[1];
extern const uint8_t myFont_24[1][1];
#endif

#if USE_32x32_FONT
extern const uint32_t myFontIdx_32[4];
//微软雅黑 32x32，加粗，等比缩放
extern const uint8_t myFont_32[16][32];
#else
extern const uint32_t myFontIdx_32[1];
extern const uint8_t myFont_32[1][1];
#endif

extern const char asciiFontIdx[62];
//微软雅黑 8x16 等比缩放
extern const uint8_t asciiFont[62][16];
#if USE_32x32_FONT
extern const uint8_t asciiFont_bold[62][16];
#else
extern const uint8_t asciiFont_bold[1][1];
#endif

extern const uint8_t disCache[4][25*32];

#endif /*__BSP_FONT_H*/


