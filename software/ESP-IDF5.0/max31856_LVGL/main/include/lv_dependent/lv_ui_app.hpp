/**
 * @file lv_ui_app.hpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "lv_ui_task.hpp"
// #include "i2c_app.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// #include "uart_app.h"

#include <stdio.h>
#include <math.h>
#include "lvgl.h"

// #include "lv_ui_assets.h"
#include "../lvgl/examples/lv_examples.h"
// #include "lv_ui.h"  /* custom ui */
#include "ui.h"  /* include it when use squarline */

// typedef enum {
//     JY901B_ACC     = 0,
//     JY901B_GYRO    = 1,
//     JY901B_ANGLE   = 2,
//     JY901B_MAG     = 3
// }jy901b_data_t;

void create_demo_app(void);

// extern TaskHandle_t xTouchVibrates;

#ifdef __cplusplus
}
#endif
