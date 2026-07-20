#pragma once

#define BOARD_NOODLE_XIAO

/* -------------------------------------------------------------------------
 *  💡 終極翻譯字典：將 Seeed Studio XIAO RP2040 的 D 腳，完美映射到晶片內部的 GP 腳
 * ------------------------------------------------------------------------- */
#define D0  GP26
#define D1  GP27
#define D2  GP28
#define D3  GP29
#define D4  GP22  // 補齊：OLED SDA 
#define D5  GP23  // 補齊：OLED SCL
#define D6  GP1   // 修正：XIAO 官方 D6 對應 GP1
#define D7  GP2   // 修正：XIAO 官方 D7 對應 GP2
#define D8  GP3
#define D9  GP4
#define D10 GP5   // 補齊：RGB LED 腳位

/* 1. 設定虛擬矩陣為 1 行 6 列，用來集中讀取你的 6 個獨立直連引腳 */
#define MATRIX_ROWS 1
#define MATRIX_COLS 6

/* 2. 直連引腳定義 (已完美修正多餘的大括號) */
#define DIRECT_PINS { \
    { D3, D2, D1, D0, D6, D7 } \
}

/* 3. 旋鈕旋轉引腳 (A腳和B腳) */
#define ENCODERS_PAD_A { D9 }
#define ENCODERS_PAD_B { D8 }
#define ENCODER_RESOLUTION 4

/* 4. OLED 螢幕 I2C 驅動定義 */
#define I2C_DRIVER I2CD1
#define I2C_SDA_PIN D4
#define I2C_SCL_PIN D5

/* 5. Mini RGB LED 配置 (已修正為新版官方規範 WS2812) */
#define WS2812_DI_PIN D10
#define RGBLED_NUM 2
