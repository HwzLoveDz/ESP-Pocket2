#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "uart_peripheral_task.h"

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
#include "wit_c_sdk.h"
#include "driver/uart.h"
#define BUF_SIZE 1024

#include "driver/gpio.h"
#define RXD1_PIN GPIO_NUM_8
#define TXD1_PIN GPIO_NUM_18

#define ACC_UPDATE		0x01
#define GYRO_UPDATE		0x02
#define ANGLE_UPDATE	0x04
#define MAG_UPDATE		0x08
#define READ_UPDATE		0x80

extern volatile char s_cDataUpdate;

void CmdProcess(char);
void AutoScanSensor(void);
void SensorUartSend(uint8_t *p_data, uint32_t uiSize);
void SensorDataUpdata(uint32_t uiReg, uint32_t uiRegNum);
void Delayms(uint16_t ucMs);
void Usart1Init(uint32_t baud_rate);
void CopeCmdData(unsigned char ucData);

#ifdef __cplusplus
}
#endif
