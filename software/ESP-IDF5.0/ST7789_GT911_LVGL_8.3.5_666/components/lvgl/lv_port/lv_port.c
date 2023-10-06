/**
 * @file lv_port.c
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief LVGL driver
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "esp_err.h"
#include "esp_log.h"
#include "lv_port.h"
#include "lvgl.h"

#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"

#include "driver/gpio.h"
#include "driver/ledc.h"
#include "driver/spi_master.h"

#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"

/* TP */
#include "esp_log.h"
#include "driver/i2c.h"
#include "esp_lcd_touch_gt911.h"

/* AXP202 */
// #include "axp20x.hpp"
/* AXP202 */

static esp_lcd_touch_handle_t tp; // TP
static lv_disp_drv_t disp_drv;

static const char *TAG = "lv_port";

static void lv_tick_inc_cb()
{
    lv_tick_inc(1);
}

static void lcd_bk_gpio_install(void)
{
    ESP_LOGI(TAG, "Install LCD backlight gpio");
    gpio_config_t bk_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << BLK_PIN};
    ESP_ERROR_CHECK(gpio_config(&bk_gpio_config));

    gpio_set_level(BLK_PIN, 0);
}

static void lcd_bk_set(bool State)
{
    if (State)
    {
        ESP_LOGI(TAG, "Turn on LCD backlight");
        gpio_set_level(BLK_PIN, 1);
    }
    else
    {
        ESP_LOGI(TAG, "Turn off LCD backlight");
        gpio_set_level(BLK_PIN, 0);
    }
}

static void lcd_bk_gpio_pwm_install(void)
{
    ESP_LOGI(TAG, "Install LCD backlight pwm gpio");
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = BLK_PIN,
        .duty           = 0, // Set duty to ((2 ** 13) - 1) * 0% = 0
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

// Set display backlight between 0-100%
void lcd_bk_pwm_set(uint32_t percentage)
{
    ESP_LOGI(TAG, "Set LCD backlight to %d%%", percentage);
    // convert percentage to duty
    uint32_t scaled_duty = (percentage / 100.00) * 8191;
    // Set duty to ledc_duty
    ESP_ERROR_CHECK(ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, scaled_duty));
    // Update duty to apply the new value
    ESP_ERROR_CHECK(ledc_update_duty(LEDC_MODE, LEDC_CHANNEL));
}

//自定义特殊lcd RST引脚
static void esp_lcd_panel_out_reset(void)
{
    ESP_LOGI(TAG, "OUT LCD RST");
    // axp.setGPIOMode(AXP_GPIO_0, AXP_IO_OUTPUT_HIGH_MODE);
    /* CODE THERE */
    // set gpio level
    // axp.gpioWrite(OUT_LCD_RST_PIN, 0);
    /* CODE END */
    vTaskDelay(pdMS_TO_TICKS(100));
    /* CODE THERE */
    // set gpio level 1
    // axp.gpioWrite(OUT_LCD_RST_PIN, 1);
    /* CODE END */
    vTaskDelay(pdMS_TO_TICKS(500));
}
//自定义特殊touch RST引脚
static void esp_lcd_touch_out_reset(void)
{
    ESP_LOGI(TAG, "OUT TOUCH RST");
    // axp.setGPIOMode(AXP_GPIO_1, AXP_IO_OUTPUT_HIGH_MODE);
    /* CODE THERE */
    // set gpio level 0
    // axp.gpioWrite(OUT_TP_RST_PIN, 0);
    /* CODE END */
    vTaskDelay(pdMS_TO_TICKS(100));
    /* CODE THERE */
    // set gpio level 1
    // axp.gpioWrite(OUT_TP_RST_PIN, 1);
    /* CODE END */
    vTaskDelay(pdMS_TO_TICKS(500));
}

//内部touch RST引脚
static void esp_lcd_touch_reset(void)
{
    ESP_LOGI(TAG, "RST TOUCH");
    gpio_config_t touch_gpio_config = {
        .mode = GPIO_MODE_OUTPUT,
        .pin_bit_mask = 1ULL << TP_RST_PIN};
    ESP_ERROR_CHECK(gpio_config(&touch_gpio_config));

    gpio_set_level(TP_RST_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(10));

    gpio_set_level(TP_RST_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(500));
}

static void tp_init(void) // TP
{

    // ESP_LOGI(TAG, "Initialize I2C bus");
    // i2c_config_t i2c_conf = {
    //     .mode = I2C_MODE_MASTER,
    //     .sda_io_num = TP_SDA_PIN,
    //     .scl_io_num = TP_SCL_PIN,
    //     .sda_pullup_en = GPIO_PULLUP_ENABLE,
    //     .scl_pullup_en = GPIO_PULLUP_ENABLE,
    //     .master.clk_speed = I2C_CLK,
    // };
    // ESP_ERROR_CHECK(i2c_param_config(I2C_PORT, &i2c_conf));
    // ESP_ERROR_CHECK(i2c_driver_install(I2C_PORT, I2C_MODE_MASTER, 0, 0, 0));

    esp_lcd_panel_io_handle_t tp_io_handle = NULL;
    esp_lcd_panel_io_i2c_config_t tp_io_config = ESP_LCD_TOUCH_IO_I2C_GT911_CONFIG();

    esp_lcd_new_panel_io_i2c(0, &tp_io_config, &tp_io_handle);

    esp_lcd_touch_config_t tp_cfg = {
        .x_max = TP_HEIGHT,
        .y_max = TP_WIDTH,
        .rst_gpio_num = -1,
        .int_gpio_num = TP_INT_PIN,
        .flags = {
            .swap_xy = SWAP_XY,
            .mirror_x = MIRROR_X,
            .mirror_y = MIRROR_Y,
        },
    };
    // vTaskDelay(pdMS_TO_TICKS(1000));
    esp_err_t err = ESP_FAIL;
    while (err != ESP_OK)
    {

//自定义特殊TP_RST引脚
#ifdef OUT_TP_RST_PIN
        esp_lcd_touch_out_reset();    
//内部TP_RST引脚
#else
        esp_lcd_touch_reset();
//END
#endif

        if (tp != NULL)
        {
            esp_lcd_touch_del(tp);
        }
        esp_lcd_touch_new_i2c_gt911(tp_io_handle, &tp_cfg, &tp);
        err = esp_lcd_touch_read_data(tp);
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

static void example_lvgl_touch_cb(lv_indev_drv_t *drv, lv_indev_data_t *data) // TP
{
    uint16_t touchpad_x[1] = {0};
    uint16_t touchpad_y[1] = {0};
    uint8_t touchpad_cnt = 0;

    /* Read touch controller data */
    esp_lcd_touch_read_data(drv->user_data);

    /* Get coordinates */
    bool touchpad_pressed = esp_lcd_touch_get_coordinates(drv->user_data, touchpad_x, touchpad_y, NULL, &touchpad_cnt, 1);

    if (touchpad_pressed && touchpad_cnt > 0)
    {
        data->point.x = touchpad_x[0];
        data->point.y = touchpad_y[0];
        data->state = LV_INDEV_STATE_PRESSED;
    }
    else
    {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static bool lv_port_flush_ready(void)
{
    lv_disp_flush_ready(&disp_drv);
    return false;
}

static void disp_flush(lv_disp_drv_t *drv, const lv_area_t *area, lv_color_t *color_map)
{
    esp_lcd_panel_handle_t panel_handle = (esp_lcd_panel_handle_t)drv->user_data;
    int offsetx1 = area->x1;
    int offsetx2 = area->x2;
    int offsety1 = area->y1;
    int offsety2 = area->y2;
    esp_lcd_panel_draw_bitmap(panel_handle, offsetx1, offsety1, offsetx2 + 1, offsety2 + 1, color_map);
}

static void lv_port_disp_init(void)
{
    static lv_disp_draw_buf_t draw_buf_dsc;
    static lv_color_t disp_buf1[DISP_BUF1];
    static lv_color_t disp_buf2[DISP_BUF2];

    spi_bus_config_t buscfg = {
        .sclk_io_num = SCLK_PIN,
        .mosi_io_num = MOSI_PIN,
        .miso_io_num = MISO_PIN,
        .quadwp_io_num = -1,
        .quadhd_io_num = -1,
        .max_transfer_sz = LCD_WIDTH * LCD_HEIGHT * sizeof(uint16_t)};
    ESP_ERROR_CHECK(spi_bus_initialize(SPI_PORT, &buscfg, SPI_DMA_CH_AUTO));

    esp_lcd_panel_io_handle_t io_handle = NULL;
    esp_lcd_panel_io_spi_config_t io_config = {
        .dc_gpio_num = DC_PIN,
        .cs_gpio_num = CS_PIN,
        .pclk_hz = SPI_CLK,
        .spi_mode = 0,
        .trans_queue_depth = 10,
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8,
        .on_color_trans_done = lv_port_flush_ready,
        .user_ctx = &disp_drv};
    ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI_PORT, &io_config, &io_handle));

    // io_config.pclk_hz = SPI_CLK;
    // ESP_ERROR_CHECK(esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI_PORT, &io_config, &io_handle));

    ESP_LOGI(TAG, "Install LCD driver of st7789");
    esp_lcd_panel_handle_t panel_handle = NULL;
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = RST_PIN,
        .color_space = ESP_LCD_COLOR_SPACE_RGB,
        .bits_per_pixel = 16,
    };
    ESP_ERROR_CHECK(esp_lcd_new_panel_st7789(io_handle, &panel_config, &panel_handle));
//自定义特殊RST引脚
#ifdef OUT_LCD_RST_PIN
    esp_lcd_panel_out_reset();    
//使用主控RST引脚
#else
    esp_lcd_panel_reset(panel_handle);   
//END
#endif
    esp_lcd_panel_init(panel_handle);

    esp_lcd_panel_invert_color(panel_handle, INVERT_COLOR);
    esp_lcd_panel_set_gap(panel_handle, 0, 0);

    if (LCD_DIRECTION == 0)
    {
        esp_lcd_panel_swap_xy(panel_handle, 0);
        esp_lcd_panel_mirror(panel_handle, false, false);
    }
    else if (LCD_DIRECTION == 90)
    {
        esp_lcd_panel_swap_xy(panel_handle, 1);
        esp_lcd_panel_mirror(panel_handle, true, false);
    }
    else if (LCD_DIRECTION == 180)
    {
        esp_lcd_panel_swap_xy(panel_handle, 0);
        esp_lcd_panel_mirror(panel_handle, true, true);
    }
    else if (LCD_DIRECTION == 270)
    {
        esp_lcd_panel_swap_xy(panel_handle, 1);
        esp_lcd_panel_mirror(panel_handle, false, true);
    }
    else
    {
        ESP_LOGE(TAG, "LCD_DIRECTION error");
    }

    // IDF 5.0 need it
    if (ESP_IDF_VERSION_MAJOR > 4)
    {
        esp_lcd_panel_disp_on_off(panel_handle, true);
    }

    lv_disp_draw_buf_init(&draw_buf_dsc, disp_buf1, disp_buf2, DISP_BUF_HEIGHT);
    lv_disp_drv_init(&disp_drv);
    disp_drv.hor_res = LCD_WIDTH;
    disp_drv.ver_res = LCD_HEIGHT;
    disp_drv.flush_cb = disp_flush;
    disp_drv.draw_buf = &draw_buf_dsc;
    disp_drv.user_data = panel_handle;
    // lv_disp_drv_register(&disp_drv);
    lv_disp_t *disp = lv_disp_drv_register(&disp_drv);

#ifdef TP_USE
    static lv_indev_drv_t indev_drv; // Input device driver (Touch)
    lv_indev_drv_init(&indev_drv);
    indev_drv.type = LV_INDEV_TYPE_POINTER;
    indev_drv.disp = disp;
    indev_drv.read_cb = example_lvgl_touch_cb;
    indev_drv.user_data = tp;
    // lv_indev_drv_register(&indev_drv);
    lv_indev_t *my_indev = lv_indev_drv_register(&indev_drv);
#endif
}

static esp_err_t lv_port_tick_init(void)
{
    TimerHandle_t os_timer = xTimerCreate("lvgl_tick", 1 / portTICK_PERIOD_MS, true, NULL, lv_tick_inc_cb);
    xTimerStart(os_timer, 0);
    return ESP_OK;
}

esp_err_t lv_port_init(void)
{
#ifdef BK_PWM_USE
    lcd_bk_gpio_pwm_install();
    lcd_bk_pwm_set(BLK_PERCENTAGE);
#else
    lcd_bk_gpio_install();
    lcd_bk_set(true);
#endif

#ifdef TP_USE
    tp_init(); // TP
#endif

    lv_init();
    lv_port_disp_init();
    lv_port_tick_init();

    return ESP_OK;
}
