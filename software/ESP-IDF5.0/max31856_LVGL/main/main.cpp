/////////////////////////////////////////////////////////////////
/*
MIT License

Copyright (c) 2023 mondraker

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

main.cpp - ST7789_GT911_LVGL_8.3.5_666
Created by mondraker on July 10, 2023.
github:https://github.com/HwzLoveDz
hardware:https://oshwhub.com/mondraker
*/
/////////////////////////////////////////////////////////////////
//! 请注意外设最大支持电压，调压可能会损坏外设器件

#include "i2c_peripheral_task.hpp"
#include "lv_ui_task.hpp"

extern "C" {
    #include "esp_log.h"
    #include "max31856_task.h"
    // #include "uart_peripheral_task.h"
}

static const char *TAG = "main";

// TaskHandle_t xTouchVibrates = NULL;

extern "C" void app_main(void)
{
    ESP_LOGI(TAG, "main code start");
    
    xTaskCreatePinnedToCore(i2cPeripheralInitTask, "i2c_Peripheral_Init_Task", 1024 * 3, NULL, 4, NULL, 0);

    xTaskCreatePinnedToCore(temp_task, "temp_task", 4 * 1024, NULL, 4, NULL, 0);

    xTaskCreatePinnedToCore(uiTask, "lv_ui_Task", 1024 * 6, NULL, 5, NULL, 1);
}
