#pragma once

#if ARDUINO >= 100
#include "Arduino.h"
#else
// #include "WProgram.h"
#include <stdint.h>
#include <string.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define BM8563_ADDR 0x51 ///< Device I2C address

typedef struct {
  uint8_t Hours;
  uint8_t Minutes;
  uint8_t Seconds;
} RTC_TimeTypeDef;

typedef struct {
  uint8_t WeekDay;
  uint8_t Month;
  uint8_t Date;
  uint16_t Year;
} RTC_DateTypeDef;

typedef uint32_t (*rtc_com_fptr_t)(uint8_t dev_addr, uint8_t reg_addr, uint8_t *data, uint8_t len); //! 类型错误：int

class RTC {
 public:
  RTC();

  int begin(rtc_com_fptr_t read_cb, rtc_com_fptr_t write_cb, uint8_t addr = BM8563_ADDR);

  bool init();

  // void begin(void);
  void GetBm8563Time(void);

  int SetTime(RTC_TimeTypeDef* RTC_TimeStruct);
  int SetDate(RTC_DateTypeDef* RTC_DateStruct);

  void GetTime(RTC_TimeTypeDef* RTC_TimeStruct);
  void GetDate(RTC_DateTypeDef* RTC_DateStruct);

  int SetAlarmIRQ(int afterSeconds);
  int SetAlarmIRQ(const RTC_TimeTypeDef& RTC_TimeStruct);
  int SetAlarmIRQ(const RTC_DateTypeDef& RTC_DateStruct,
                  const RTC_TimeTypeDef& RTC_TimeStruct);

  void clearIRQ();
  void disableIRQ();

 public:
  uint8_t Second;
  uint8_t Minute;
  uint8_t Hour;
  uint8_t Week;
  uint8_t Day;
  uint8_t Month;
  uint8_t Year;
  uint8_t DateString[9];
  uint8_t TimeString[9];

  uint8_t asc[14];

 private:
  void Bcd2asc(void);
  void DataMask();
  void Str2Time(void);

  uint8_t Bcd2ToByte(uint8_t Value);
  uint8_t ByteToBcd2(uint8_t Value);

 private:
  /*定义数组用来存储读取的时间数据 */
  uint8_t trdata[7];
  /*定义数组用来存储转换的 asc 码时间数据*/
  // uint8_t asc[14];

  uint8_t _address;

  void WriteReg(uint8_t reg, uint8_t data);
  uint8_t ReadReg(uint8_t reg);
  
  int _readByte(uint8_t reg, uint8_t nbytes, uint8_t *data);
  int _writeByte(uint8_t reg, uint8_t nbytes, uint8_t *data);

  rtc_com_fptr_t _read_cb = nullptr;
  rtc_com_fptr_t _write_cb = nullptr;
};

extern RTC rtc;

#ifdef __cplusplus
}
#endif
