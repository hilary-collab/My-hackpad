#pragma once

#define BOARD_NOODLE_XIAO

// Direct pin definitions for 6 switches based on your schematic
#define DIRECT_PINS { \
    { D3, D2, D1, D0, D6, D7 } \
}

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
