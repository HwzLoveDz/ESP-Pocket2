/**
 * @file max31856_task.c
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief uart task
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "max31856_task.h"

void temp_task(void *args)
{
    ESP_ERROR_CHECK(spi_master_init());

    max31856_A = max31856_init(GPIO_NUM_7);
    thermocouple_set_type(&max31856_A, MAX31856_TCTYPE_K, GPIO_NUM_7);

    max31856_B = max31856_init(GPIO_NUM_15);
    thermocouple_set_type(&max31856_B, MAX31856_TCTYPE_K, GPIO_NUM_15);
    while (1)
    {
        // thermocouple_read_fault(&max31856_A, false);
        thermocouple_read_coldjunction(&max31856_A, GPIO_NUM_7);
        thermocouple_read_temperature(&max31856_A, GPIO_NUM_7);
        // ESP_LOGI(TEMP_TAG, "TempA:%.2f", max31856_A.coldjunction_c);

        // thermocouple_read_fault(&max31856_B, false);
        thermocouple_read_coldjunction(&max31856_B, GPIO_NUM_15);
        thermocouple_read_temperature(&max31856_B, GPIO_NUM_15);
        // ESP_LOGI(TEMP_TAG, "TempB:%.2f", max31856_B.coldjunction_c);
    }
}

max31856_cfg_t max31856_A,max31856_B;
