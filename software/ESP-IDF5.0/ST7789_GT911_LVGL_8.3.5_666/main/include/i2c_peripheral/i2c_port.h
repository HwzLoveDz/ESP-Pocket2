/**
 * @file i2c_port.h
 * @author by mondraker (https://oshwhub.com/mondraker)(https://github.com/HwzLoveDz)
 * @brief 
 * @version 0.1
 * @date 2023-07-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include "esp_log.h"
#include "driver/i2c.h"
#include "sdkconfig.h"

//! ESP32C3只有I2C_NUM_0一个I2C通道
// #define _I2C_NUMBER(num)            I2C_NUM_##num                           /*!< I2C port*/
// #define I2C_NUMBER(num)             _I2C_NUMBER(num)

#define AXP_ISR_GPIO                (gpio_num_t)(2)  /*!< axp power chip interrupt Pin*/
#define GPIO_INPUT_PIN_SEL          (1ULL<<AXP_ISR_GPIO)

#define I2C_MASTER_SCL_IO           48//CONFIG_I2C_MASTER_SCL                   /*!< gpio number for I2C master clock */
#define I2C_MASTER_SDA_IO           47//CONFIG_I2C_MASTER_SDA                   /*!< gpio number for I2C master data  */
#define I2C_MASTER_NUM              I2C_NUM_0//I2C_NUMBER(I2C_NUM_0)  /*!< I2C port number for master dev */
#define I2C_MASTER_FREQ_HZ          400*1000             /*!< I2C master clock frequency */
#define I2C_MASTER_TX_BUF_DISABLE   0                                       /*!< I2C master doesn't need buffer */
#define I2C_MASTER_RX_BUF_DISABLE   0                                       /*!< I2C master doesn't need buffer */

#define WRITE_BIT                   I2C_MASTER_WRITE                        /*!< I2C master write */
#define READ_BIT                    I2C_MASTER_READ                         /*!< I2C master read */
#define ACK_CHECK_EN                0x1                                     /*!< I2C master will check ack from slave*/
#define ACK_CHECK_DIS               0x0                                     /*!< I2C master will not check ack from slave */
#define ACK_VAL                     (i2c_ack_type_t)0x0                     /*!< I2C ack value */
#define NACK_VAL                    (i2c_ack_type_t)0x1                     /*!< I2C nack value */

esp_err_t i2c_master_init(void);
uint32_t twi_read(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);   //! 类型错误：uint16_t
uint32_t twi_write(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len);  //! 类型错误：uint16_t

#ifdef __cplusplus
}
#endif
