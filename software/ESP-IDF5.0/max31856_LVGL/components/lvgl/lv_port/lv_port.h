/**
 * @file lv_port.h
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief LVGL hardware config
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

/* LCD BACKLIGHT */
// GPIO SET
#define BLK_PIN                 (46) // Define the output GPIO
// BK LIGHT MODE SET
#if 1
    // USE SET
    #define BK_PWM_USE
// LCD BACKLIGHT SET END
#endif
// LEDC PWM SET
#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_13_BIT // Set duty resolution to 13 bits
#define BLK_PERCENTAGE          (100)   // 0-100% Set display light to 100%
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz
// Set display backlight between 0-100%
void lcd_bk_pwm_set(uint32_t percentage);

/* LCD ST7789 SET */
// SIZE SET
#define LCD_HEIGHT      ( 320 )
#define LCD_WIDTH       ( 240 )
// GPIO SET
#define SCLK_PIN        (12)
#define MOSI_PIN        (11)
#define MISO_PIN        (13)    //-1
#define CS_PIN          (10)
#define DC_PIN          (9)
// SPI SET
#define SPI_PORT        (SPI2_HOST)
#define SPI_CLK         (SPI_MASTER_FREQ_80M)
// FEATURE SET
#define INVERT_COLOR    1
#define LCD_DIRECTION   (0) //0下//90左//180上//270右

/* LCD & TOUCH RST PIN SET */
// if 1为外部特殊芯片引脚连接RST，比如AXP电源芯片引脚，TCA引脚扩展芯片等等，
// 此时调用esp_lcd_panel_lcd_rst();    // 自定义特殊RST引脚
// #define OUT_LCD_RST_PIN (AXP_GPIO_0)
// #define OUT_TP_RST_PIN  (AXP_GPIO_1)
#if 0
    #define RST_PIN         (-1)    // must set -1
    #define TP_RST_PIN      (-1)    // must set -1
// else 0为默认ESP32引脚连接屏幕RST引脚，
// 此时调用esp_lcd_panel_reset(panel_handle);   // 使用主控RST引脚
#else
    #define RST_PIN         (3)    // when (-1),hardware rst
    #define TP_RST_PIN      (21)    // -1
// RST PIN SET END
#endif

/* TP GT911 SET */
#if 1
    // USE SET
    #define TP_USE
    // SIZE SET
    #define TP_HEIGHT       ( LCD_WIDTH )
    #define TP_WIDTH        ( LCD_HEIGHT )
    // FEATURE SET
    #if LCD_DIRECTION == (0)
        // TOUCH PAD SET 0
        #define SWAP_XY         0
        #define MIRROR_X        0
        #define MIRROR_Y        0
    #elif LCD_DIRECTION == (90)
        // TOUCH PAD SET 90
        #define SWAP_XY         1
        #define MIRROR_X        1
        #define MIRROR_Y        0
    #elif LCD_DIRECTION == (180)
        // TOUCH PAD SET 180
        #define SWAP_XY         0
        #define MIRROR_X        1
        #define MIRROR_Y        1
    #elif LCD_DIRECTION == (270)
        // TOUCH PAD SET 270
        #define SWAP_XY         1
        #define MIRROR_X        0
        #define MIRROR_Y        1
    #else 
        // TOUCH PAD SET DEFAULT
        #define SWAP_XY         0   //0//1//0//1
        #define MIRROR_X        0   //0//1//0//0
        #define MIRROR_Y        0   //0//0//1//1
        //输入其他角度就显示0度
    #endif
    // GPIO SET
    #define TP_SCL_PIN      (48)
    #define TP_SDA_PIN      (47)       
    #define TP_INT_PIN      (45)
    // I2C SET
    #define I2C_PORT        (I2C_NUM_0)
    #define I2C_CLK         (400*1000)
    /* LV DISPLAY BUFFER SET */
    // size of the `buf1` and `buf2` in pixel count.
    #define DISP_BUF_HEIGHT (LCD_WIDTH * 120)    // 10
    // SINGLE BUFFERING SET
    #if 0
        #define DISP_BUF1       (LCD_WIDTH * 120)
        #define DISP_BUF2       (NULL)
    // DOUBLE BUFFERING SET
    #else
        #define DISP_BUF1       (LCD_WIDTH * 120)
        #define DISP_BUF2       (LCD_WIDTH * 120)
    // BUFFERING SET END
    #endif
#endif

esp_err_t lv_port_init(void);

#ifdef __cplusplus
}
#endif
