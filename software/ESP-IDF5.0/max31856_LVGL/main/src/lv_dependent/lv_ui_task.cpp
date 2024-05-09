/**
 * @file lv_ui_task.cpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief demo & lvgl_init 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "lv_ui_task.hpp"
#include "esp_log.h"

static const char *TAG = "lvgl ui";

void uiTask(void *pvParameters)
{
    ESP_ERROR_CHECK(lv_port_init());
    ESP_LOGI(TAG, "lvgl ui task");

    // lv_demo_widgets();      /* A widgets example. This is what you get out of the box */
    // lv_demo_music();        /* A modern, smartphone-like music player demo. */
    // lv_demo_stress();       /* A stress test for LVGL. */
    // lv_demo_benchmark();    /* A demo to measure the performance of LVGL or to compare different settings. */
    
    // lv_100ask_calc_simple_test();
    // lv_100ask_2048_simple_test();
    // lv_100ask_page_manager_simple_test();
    // lv_100ask_file_explorer_simple_test();
    // lv_100ask_sketchpad_simple_test();

    create_demo_app();      /* Create lv_example or your own app example */

    for (;; vTaskDelay(1))  // lv_tick_inc(1);
    {
        lv_task_handler();
    }
}
