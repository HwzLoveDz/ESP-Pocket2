/**
 * @file i2c_peripheral_task.cpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief i2c task
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "i2c_peripheral_task.hpp"

static const char *TAG = "I2C peripheral";

void i2cPeripheralInitTask(void *pvParameters) // only run once
{
    ESP_LOGI(TAG, "i2C peripheral task");
    ESP_ERROR_CHECK(i2c_master_init());

    // pmu_axp202_init();

    // rtc_bm8563_init();
    // drv_drv2605_init();
    // create_RTC_update_func();

    vTaskDelete(NULL);
}

// void touchVibratesTask(void *pvParameters)
// {
//     uint32_t ulNotificationValue;

//     for (;;)
//     {
//         // 返回运行此命令之前的Notification Value
//         // 命令含义: waitting for notification, then reset
//         ulNotificationValue = ulTaskNotifyTake(pdTRUE, // pdTRUE 运行完后，清零
//                                                portMAX_DELAY);
//         if (ulNotificationValue > 0)
//         {
//             // TODO: 处理一些任务
//             create_touchVibrates_func(8); // 更改震动效果3 Strong Click - 30% 6 Sharp Click - 30% 8 Soft Bump - 60%
//         }
//     }
// }

// void rtcUpdateTask(void *pvParameters)
// {
//     for (;;vTaskDelay(pdMS_TO_TICKS(1000)))
//     {
//         // TODO: 处理一些任务
//         create_RTC_update_func();
//     }
// }
