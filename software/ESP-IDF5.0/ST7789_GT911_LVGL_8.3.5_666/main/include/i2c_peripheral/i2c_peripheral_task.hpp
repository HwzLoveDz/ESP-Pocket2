/**
 * @file i2c_peripheral_task.hpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "axp20x.hpp"
#include "drv2605.hpp"
#include "bm8563.hpp"

#include "i2c_app.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

#include "i2c_port.h"

void i2cPeripheralInitTask(void *pvParameters);
void touchVibratesTask(void *pvParameters);
void rtcUpdateTask(void *pvParameters);

// #endif /*End of "Content enable"*/
#ifdef __cplusplus
}
#endif
