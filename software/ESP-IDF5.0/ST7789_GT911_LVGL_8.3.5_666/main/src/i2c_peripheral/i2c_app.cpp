/**
 * @file i2c_app.cpp
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief i2c function
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "i2c_app.hpp"

static const char *TAG = "i2c app";

// RTC_DateTypeDef dateStruct; // RTC Date Struct
// RTC_TimeTypeDef timeStruct; // RTC Time Struct

void create_touchVibrates_func(uint8_t effect)
{
    // set the effect to play
    printf("effect: ");
    drv.effect_name(effect);
    printf("\n");
    drv.setWaveform(0, effect); // play effect
    drv.setWaveform(1, 0);      // end waveform
    // play the effect!
    drv.go();
}

void create_RTC_update_func(void)
{
    // Get RTC
    rtc.GetDate(&dateStruct);
    rtc.GetTime(&timeStruct);
    // Print RTC
    // ESP_LOGI(TAG, "%04d/%02d/%02d  %02d  %02d:%02d:%02d",
    //          dateStruct.Year,
    //          dateStruct.Month,
    //          dateStruct.Date,
    //          dateStruct.WeekDay,
    //          timeStruct.Hours,
    //          timeStruct.Minutes,
    //          timeStruct.Seconds);
}

float create_PMU_getBatPercentage_func(void)
{
    return (axp.getBattVoltage()/(4.1*1000))*100;
}

void rtc_bm8563_init()
{
    if (rtc.begin(twi_read, twi_write, BM8563_ADDR)) //
    {
        ESP_LOGE(TAG, "Error init bm8563 !!!");
        while (1);
    }
    ESP_LOGI(TAG, "Success init bm8563 !!!");

    // // Set RTC Date
    // dateStruct.WeekDay = 3;
    // dateStruct.Month   = 6;
    // dateStruct.Date    = 21;
    // dateStruct.Year    = 2023;
    // rtc.SetDate(&dateStruct);
    // // Set RTC Time
    // timeStruct.Hours   = 15;
    // timeStruct.Minutes = 8;
    // timeStruct.Seconds = 15;
    // rtc.SetTime(&timeStruct);
}

void drv_drv2605_init()
{
    if (drv.begin(twi_read, twi_write, DRV2605_ADDR)) //
    {
        ESP_LOGE(TAG, "Error init drv2605 !!!");
        while (1);
    }
    ESP_LOGI(TAG, "Success init drv2605 !!!");

    // Use LRA (Linear Resonance Actuator) mode.
    drv.useLRA();
    // drv.useERM();

    // Select the waveform Library to use
    // 0 = Empty, 1-5 are ERM, 6 is LRA.
    drv.selectLibrary(6);

    // I2C trigger by sending 'go' command
    // default, internal trigger when sending GO command
    drv.setMode(DRV2605_MODE_INTTRIG);

    // 开机振动
    create_touchVibrates_func(14);
}

void pmu_axp202_init()
{
    if (axp.begin(twi_read, twi_write, AXP202_SLAVE_ADDRESS))
    {
        ESP_LOGE(TAG, "Error init axp20x !!!");
        while (1);
    }
    ESP_LOGI(TAG, "Success init axp20x !!!");

    // 两个警告等级（类似于手机20%一提醒，10%一提醒）和一个关机电压（类似于手机3%关机，实际显示0%）
    axp.setVWarningLevel1(3450);
    axp.setVWarningLevel2(3400);
    axp.setPowerDownVoltage(2600);
    uint16_t level1 = axp.getVWarningLevel1();
    uint16_t level2 = axp.getVWarningLevel2();
    uint16_t level3 = axp.getPowerDownVoltage();
    ESP_LOGI(TAG, "getVWarningLevel1:%u mV", level1 );
    ESP_LOGI(TAG, "getVWarningLevel2:%u mV", level2);
    ESP_LOGI(TAG, "getPowerDonwLevel3:%u mV", level3);

    axp.setPowerOutPut(AXP202_DCDC3, AXP202_ON); // 主控供电，十轴传感器供电
    axp.setPowerOutPut(AXP202_DCDC2, AXP202_ON);

    axp.setLDO2Voltage(3300); // 屏幕与SD卡供电
    axp.setPowerOutPut(AXP202_LDO2, AXP202_ON);

    axp.setLDO4Voltage(AXP202_LDO4_3300MV); // 音频供电
    axp.setPowerOutPut(AXP202_LDO4, AXP202_ON);

    axp.setLDO3Voltage(3500); // 触觉驱动器供电
    axp.setPowerOutPut(AXP202_LDO3, AXP202_ON);

    axp.setPowerOutPut(AXP202_EXTEN, AXP202_ON);

    if (axp.isDCDC2Enable())
    {
        ESP_LOGI(TAG, "DC2: %u mV", axp.getDCDC2Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "DC2: DISABLE");
    }

    if (axp.isDCDC3Enable())
    {
        ESP_LOGI(TAG, "DC3: %u mV", axp.getDCDC3Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "DC3: DISABLE");
    }

    if (axp.isLDO2Enable())
    {
        ESP_LOGI(TAG, "LDO2: %u mV", axp.getLDO2Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "LDO2: DISABLE");
    }

    if (axp.isLDO3Enable())
    {
        ESP_LOGI(TAG, "LDO3: %u mV", axp.getLDO3Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "LDO3: DISABLE");
    }

    if (axp.isLDO4Enable())
    {
        ESP_LOGI(TAG, "LDO4: %u mV", axp.getLDO4Voltage());
    }
    else
    {
        ESP_LOGI(TAG, "LDO4: DISABLE");
    }

    if (axp.isExtenEnable())
    {
        ESP_LOGI(TAG, "Exten: ENABLE");
    }
    else
    {
        ESP_LOGI(TAG, "Exten: DISABLE");
    }

    // When the chip is axp192 / 173, the allowed values are 0 ~ 15,
    // corresponding to the axp1xx_charge_current_t enumeration
    //  axp.setChargeControlCur(AXP1XX_CHARGE_CUR_550MA);

    // axp202 allows maximum charging current of 1800mA, minimum 300mA
    axp.setChargeControlCur(300);

    axp.setChgLEDContrl(AXP20X_LED_CHARGING_CTL);   // CHGLED由充电状态控制
    axp.setChgLEDChargingMode(AXP20X_LED_LIGHT_WHEN_CHARGING);  // CHGLED由充电状态控制模式
    // axp.setChgLEDContrl(AXP20X_LED_REG_32H_CTL); // CHGLED由REG32H控制
    // axp.setChgLEDMode(AXP20X_LED_BLINK_4HZ);  // CHGLED由REG32H控制模式

    ESP_LOGI(TAG, "setChargeControlCur:%u", axp.getChargeControlCur());
    ESP_LOGI(TAG, "getCoreTemp:%.2f C", axp.getTemp());

    // Backup battery charge control
    // Backup Battery model: KTS CR2032W 3.0V 220mAh
    axp.setBackupChargeControl(AXP202_ON);
    axp.setBackupChargeVoltage(AXP202_BACKUP_VOLTAGE_3V0);
    axp.setBackupChargeCurrent(AXP202_BACKUP_CURRENT_100UA);

    axp.setGPIOMode(AXP_GPIO_0, AXP_IO_OUTPUT_HIGH_MODE); // 打开主板指示灯PIO0
    axp.gpioWrite(AXP_GPIO_0, 1);
}

RTC_DateTypeDef dateStruct; // RTC Date Struct
RTC_TimeTypeDef timeStruct; // RTC Time Struct
