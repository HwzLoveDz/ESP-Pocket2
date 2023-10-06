/**
 * @file lv_ui_task.hpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "lv_ui_app.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lv_lib_100ask.h"
#include "lv_demo.h"
#include "lv_port.h"
#include "lvgl.h"

void uiTask(void *pvParameters);

#ifdef __cplusplus
}
#endif
