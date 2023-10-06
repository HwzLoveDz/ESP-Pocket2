/**
 * @file uart_peripheral_task.c
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief uart task
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "uart_peripheral_task.h"

// static const char *TAG = "UART peripheral";

void Usart1_task(void *pvParameters)
{
	unsigned char ucTemp;

	Usart1Init(9600);

	for (;;)
	{
		// TODO: 处理一些任务
		if(uart_read_bytes(UART_NUM_1, &ucTemp, 1, portMAX_DELAY) == 1)
			WitSerialDataIn(ucTemp);
	}
}

void Usart0_task(void *pvParameters)
{
	unsigned char c;

	for (;;)
	{
		// TODO: 处理一些任务
		if(scanf("%c", &c) != -1)
		{
			CopeCmdData(c);
		}
		else
		{
			vTaskDelay(100 / portTICK_PERIOD_MS);
		}
	}
}

void uartPeripheralInitTask(void *pvParameters)
{
	WitInit(WIT_PROTOCOL_NORMAL, 0x50);
	WitSerialWriteRegister(SensorUartSend);
	WitRegisterCallBack(SensorDataUpdata);
	WitDelayMsRegister(Delayms);
	Delayms(10);
	// printf("\r\n********************** wit-motion normal example  ************************\r\n");
	AutoScanSensor();

	vTaskDelete(NULL);
}

