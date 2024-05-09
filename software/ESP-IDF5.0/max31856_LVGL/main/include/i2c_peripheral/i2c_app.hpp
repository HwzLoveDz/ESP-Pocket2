/**
 * @file i2c_app.hpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#include "i2c_peripheral_task.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void pmu_axp202_init(void);
// void rtc_bm8563_init(void);
// void drv_drv2605_init(void);

// void create_RTC_update_func(void);
// void create_touchVibrates_func(uint8_t effect);
// float create_PMU_getBatPercentage_func(void);

// extern RTC_DateTypeDef dateStruct; // RTC Date Struct
// extern RTC_TimeTypeDef timeStruct; // RTC Time Struct

#ifdef __cplusplus
}
#endif
