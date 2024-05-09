#pragma once

static const char *TEMP_TAG = "max31856";

#ifdef __cplusplus
extern "C" {
#endif

// #include "uart_peripheral_task.h"
#include "max31856.h"

/**
 * @file uart_app.h
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

void temp_task(void *args);

extern max31856_cfg_t max31856_A,max31856_B;

#ifdef __cplusplus
}
#endif
