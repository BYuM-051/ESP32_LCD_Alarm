#pragma once

#include "driver/gpio.h"

/* Existing project pinout: main/user_config.h (V1 wiring).
 * Keep the touch bus separate from the board peripherals' I2C bus.
 */
#define PIN_I2C_SCL GPIO_NUM_18
#define PIN_I2C_SDA GPIO_NUM_17
#define PIN_SYSTEM_I2C_SCL GPIO_NUM_48
#define PIN_SYSTEM_I2C_SDA GPIO_NUM_47

#define PIN_LCD_CS GPIO_NUM_9
#define PIN_LCD_CLK GPIO_NUM_10
#define PIN_LCD_DATA0 GPIO_NUM_11
#define PIN_LCD_DATA1 GPIO_NUM_12
#define PIN_LCD_DATA2 GPIO_NUM_13
#define PIN_LCD_DATA3 GPIO_NUM_14
#define PIN_LCD_RST GPIO_NUM_21
#define PIN_LCD_BL GPIO_NUM_8

/* Examples/ESP-IDF/08_Audio_Test/components/codec_board/board_cfg.txt:
 * Board: S3_LCD_3_49.
 */
#define PIN_I2S_MCLK GPIO_NUM_7
#define PIN_I2S_BCLK GPIO_NUM_15
#define PIN_I2S_WS GPIO_NUM_46
#define PIN_I2S_DIN GPIO_NUM_6
#define PIN_I2S_DOUT GPIO_NUM_45
