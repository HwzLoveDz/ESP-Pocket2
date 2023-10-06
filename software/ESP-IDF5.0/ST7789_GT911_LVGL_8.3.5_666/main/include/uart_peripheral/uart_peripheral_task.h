/**
 * @file uart_peripheral_task.h
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifdef __cplusplus
extern "C" {
#endif

#include "uart_app.h"

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"

extern const uint32_t c_uiBaud[10];

void Usart1_task(void *pvParameters);
void Usart0_task(void *pvParameters);
void uartPeripheralInitTask(void *pvParameters);

// #endif /*End of "Content enable"*/
#ifdef __cplusplus
}
#endif
