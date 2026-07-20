#pragma once
#define BOARD_NOODLE_XIAO
#define D0  GP26
#define D1  GP27
#define D2  GP28
#define D3  GP29
#define D6  GP0
#define D7  GP1
#define D8  GP2
#define D9  GP4
#define MATRIX_ROWS 1 //
#define MATRIX_COLS 6 // 
#define DIRECT_PINS { \
    { D3, D2, D1, D0, D6, D7 } \
}}

// Rotary Encoder pins (D9 and D8)
#define ENCODERS_PAD_A { D9 }
#define ENCODERS_PAD_B { D8 }
#define ENCODER_RESOLUTION 4

// OLED screen I2C driver pins (D4 and D5)
#define I2C_DRIVER I2CD1
#define I2C_SDA_PIN D4
#define I2C_SCL_PIN D5

// RGB LED configuration
#define RGB_DI_PIN D10
#define RGBLED_NUM 2