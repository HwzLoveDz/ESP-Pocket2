#include "bm8563.hpp"

/**************************************************************************/
/*!
  @brief  Instantiates a new BM8563 class. I2C, no address adjustments or pins
*/
/**************************************************************************/
RTC::RTC() {}

/**************************************************************************/
/*!
  @brief Setup HW using a specified Wire
  @return Return value from init()
*/
/**************************************************************************/
int RTC::begin(rtc_com_fptr_t read_cb, rtc_com_fptr_t write_cb, uint8_t addr)
{
  if (read_cb == nullptr || write_cb == nullptr)
    return -1;
  _read_cb = read_cb;
  _write_cb = write_cb;
  _address = addr;
  return init();
}

/**************************************************************************/
/*!
  @brief  Setup the HW
  @return Always Pass
*/
/**************************************************************************/
bool RTC::init() {
  // Wire1.begin(21, 22);
  WriteReg(0x00, 0x00);
  WriteReg(0x01, 0x00);
  WriteReg(0x0D, 0x00);
  return 0;
}

/**************************************************************************/
/*!
  @brief Write an 8-bit register.
  @param reg The register to write.
  @param val The value to write.
*/
/**************************************************************************/
// void RTC::WriteReg(uint8_t reg, uint8_t data) {
//   Wire1.beginTransmission(0x51);
//   Wire1.write(reg);
//   Wire1.write(data);
//   Wire1.endTransmission();
// }
void RTC::WriteReg(uint8_t reg, uint8_t data) {
  uint8_t write_data[8];
  write_data[0] = data;
  _writeByte(reg, 1, write_data);
}
int RTC::_writeByte(uint8_t reg, uint8_t nbytes, uint8_t *data)
{
  if (_write_cb != nullptr)
  {
    return _write_cb(_address, reg, data, nbytes);
  }
  return 0;
}

/**************************************************************************/
/*!
  @brief Read an 8-bit register.
  @param reg The register to read.
  @return 8-bit value of the register.
*/
/**************************************************************************/
// uint8_t RTC::ReadReg(uint8_t reg) {
//   Wire1.beginTransmission(0x51);
//   Wire1.write(reg);
//   Wire1.endTransmission(false);
//   Wire1.requestFrom(0x51, 1);
//   return Wire1.read();
// }
uint8_t RTC::ReadReg(uint8_t reg) {
  uint8_t data;
  _readByte(reg, 1, &data);
  return data;
}
int RTC::_readByte(uint8_t reg, uint8_t nbytes, uint8_t *data)
{
  if (_read_cb != nullptr)
  {
    return _read_cb(_address, reg, data, nbytes);
  }

  return 0;
}

void RTC::GetBm8563Time(void) {
  // Wire1.beginTransmission(0x51);
  // Wire1.write(0x02);
  // Wire1.endTransmission(false);
  // Wire1.requestFrom(0x51, 7);
  // while (Wire1.available()) {
  //   trdata[0] = Wire1.read();
  //   trdata[1] = Wire1.read();
  //   trdata[2] = Wire1.read();
  //   trdata[3] = Wire1.read();
  //   trdata[4] = Wire1.read();
  //   trdata[5] = Wire1.read();
  //   trdata[6] = Wire1.read();
  // }
  const uint8_t reg = 0x02;
  uint8_t data[7];
  // 读取 7 字节数据
  int result = _writeByte(reg, 0, nullptr);
  if (result != 0) {return;}  // 出错处理
  result = _readByte(reg, 7, data);
  if (result != 0) {return;}  // 出错处理
  // 处理数据
  for (int i = 0; i < 7; i++) {trdata[i] = data[i];}

  DataMask();
  Bcd2asc();
  Str2Time();
}

void RTC::Str2Time(void) {
  Second = (asc[0] - 0x30) * 10 + asc[1] - 0x30;
  Minute = (asc[2] - 0x30) * 10 + asc[3] - 0x30;
  Hour = (asc[4] - 0x30) * 10 + asc[5] - 0x30;
  /*
  uint8_t Hour;
  uint8_t Week;
  uint8_t Day;
  uint8_t Month;
  uint8_t  Year;
  */
}

void RTC::DataMask() {
  trdata[0] = trdata[0] & 0x7f;  //秒
  trdata[1] = trdata[1] & 0x7f;  //分
  trdata[2] = trdata[2] & 0x3f;  //时

  trdata[3] = trdata[3] & 0x3f;  //日
  trdata[4] = trdata[4] & 0x07;  //星期
  trdata[5] = trdata[5] & 0x1f;  //月

  trdata[6] = trdata[6] & 0xff;  //年
}
/********************************************************************
函 数 名： void Bcd2asc(void)
功 能： bcd 码转换成 asc 码，供Lcd显示用
说 明：
调 用：
入口参数：
返 回 值：无
***********************************************************************/
void RTC::Bcd2asc(void) {
  uint8_t i, j;
  for (j = 0, i = 0; i < 7; i++) {
    asc[j++] =
        (trdata[i] & 0xf0) >> 4 | 0x30; /*格式为: 秒 分 时 日 月 星期 年 */
    asc[j++] = (trdata[i] & 0x0f) | 0x30;
  }
}

uint8_t RTC::Bcd2ToByte(uint8_t Value) {
  uint8_t tmp = 0;
  tmp = ((uint8_t)(Value & (uint8_t)0xF0) >> (uint8_t)0x4) * 10;
  return (tmp + (Value & (uint8_t)0x0F));
}

uint8_t RTC::ByteToBcd2(uint8_t Value) {
  uint8_t bcdhigh = 0;

  while (Value >= 10) {
    bcdhigh++;
    Value -= 10;
  }

  return ((uint8_t)(bcdhigh << 4) | Value);
}

void RTC::GetTime(RTC_TimeTypeDef *RTC_TimeStruct) {
  // if()
  // uint8_t buf[3] = {0};

  // Wire1.beginTransmission(0x51);
  // Wire1.write(0x02);
  // Wire1.endTransmission(false);
  // Wire1.requestFrom(0x51, 3);

  // while (Wire1.available()) {
  //   buf[0] = Wire1.read();
  //   buf[1] = Wire1.read();
  //   buf[2] = Wire1.read();
  // }
  const uint8_t reg = 0x02;
  uint8_t data[3];
  // 读取 3 字节数据
  int result = _readByte(reg, 3, data);
  if (result != 0) {return;}  // 出错处理
  // 处理数据
  RTC_TimeStruct->Seconds = Bcd2ToByte(data[0] & 0x7f);  //秒
  RTC_TimeStruct->Minutes = Bcd2ToByte(data[1] & 0x7f);  //分
  RTC_TimeStruct->Hours = Bcd2ToByte(data[2] & 0x3f);    //时
}

int RTC::SetTime(RTC_TimeTypeDef *RTC_TimeStruct) {
  if (RTC_TimeStruct == NULL || RTC_TimeStruct->Hours > 24 ||
      RTC_TimeStruct->Minutes > 60 || RTC_TimeStruct->Seconds > 60)
    return 0;
  // Wire1.beginTransmission(0x51);
  // Wire1.write(0x02);
  // Wire1.write(ByteToBcd2(RTC_TimeStruct->Seconds));
  // Wire1.write(ByteToBcd2(RTC_TimeStruct->Minutes));
  // Wire1.write(ByteToBcd2(RTC_TimeStruct->Hours));
  // Wire1.endTransmission();
  const uint8_t reg = 0x02;
  uint8_t data[3];
  // 准备要写入的数据
  data[0] = ByteToBcd2(RTC_TimeStruct->Seconds) & 0x7f;   //秒
  data[1] = ByteToBcd2(RTC_TimeStruct->Minutes) & 0x7f;   //分
  data[2] = ByteToBcd2(RTC_TimeStruct->Hours) & 0x3f;     //时
  // 写入数据
  int result = _writeByte(reg, 3, data);
  if (result != 0) {return 0;} // 出错处理
  return 1;
}

void RTC::GetDate(RTC_DateTypeDef *RTC_DateStruct) {
  // uint8_t buf[4] = {0};

  // Wire1.beginTransmission(0x51);
  // Wire1.write(0x05);
  // Wire1.endTransmission(false);
  // Wire1.requestFrom(0x51, 4);

  // while (Wire1.available()) {
  //   buf[0] = Wire1.read();
  //   buf[1] = Wire1.read();
  //   buf[2] = Wire1.read();
  //   buf[3] = Wire1.read();
  // }

  if (RTC_DateStruct == NULL) {return;} // 出错处理
  const uint8_t reg = 0x05;
  uint8_t data[4] = {0};
  // 读取数据
  int result = _readByte(reg, 4, data);
  if (result != 0) {return;} // 出错处理

  RTC_DateStruct->Date = Bcd2ToByte(data[0] & 0x3f);
  RTC_DateStruct->WeekDay = Bcd2ToByte(data[1] & 0x07);
  RTC_DateStruct->Month = Bcd2ToByte(data[2] & 0x1f);

  if (data[2] & 0x80) {
    RTC_DateStruct->Year = 1900 + Bcd2ToByte(data[3] & 0xff);
  } else {
    RTC_DateStruct->Year = 2000 + Bcd2ToByte(data[3] & 0xff);
  }
}

int RTC::SetDate(RTC_DateTypeDef *RTC_DateStruct) {
  if (RTC_DateStruct == NULL || RTC_DateStruct->WeekDay > 7 ||
      RTC_DateStruct->Date > 31 || RTC_DateStruct->Month > 12)
    return 0;
//   Wire1.beginTransmission(0x51);
//   Wire1.write(0x05);
//   Wire1.write(ByteToBcd2(RTC_DateStruct->Date));
//   Wire1.write(ByteToBcd2(RTC_DateStruct->WeekDay));
  const uint8_t reg = 0x05;
  uint8_t data[4] = {0};

  data[0] = ByteToBcd2(RTC_DateStruct->Date);
  data[1] = ByteToBcd2(RTC_DateStruct->WeekDay);

  if (RTC_DateStruct->Year < 2000) {
    // Wire1.write(ByteToBcd2(RTC_DateStruct->Month) | 0x80);
    // Wire1.write(ByteToBcd2((uint8_t)(RTC_DateStruct->Year % 100)));
    data[2] = ByteToBcd2(RTC_DateStruct->Month) | 0x80;
    data[3] = ByteToBcd2((uint8_t)(RTC_DateStruct->Year % 100));
  } else {
    /* code */
    // Wire1.write(ByteToBcd2(RTC_DateStruct->Month) | 0x00);
    // Wire1.write(ByteToBcd2((uint8_t)(RTC_DateStruct->Year % 100)));
    data[2] = ByteToBcd2(RTC_DateStruct->Month) | 0x00;
    data[3] = ByteToBcd2((uint8_t)(RTC_DateStruct->Year % 100));
  }
  // Wire1.endTransmission();
  // 写入数据
  int result = _writeByte(reg, 4, data);
  if (result != 0) {return 0;} // 出错处理
  return 1;
}

int RTC::SetAlarmIRQ(int afterSeconds) {
  uint8_t reg_value = 0;
  reg_value = ReadReg(0x01);

  if (afterSeconds < 0) {
    reg_value &= ~(1 << 0);
    WriteReg(0x01, reg_value);
    reg_value = 0x03;
    WriteReg(0x0E, reg_value);
    return -1;
  }

  uint8_t type_value = 2;
  uint8_t div = 1;
  if (afterSeconds > 255) {
    div = 60;
    type_value = 0x83;
  } else {
    type_value = 0x82;
  }

  afterSeconds = (afterSeconds / div) & 0xFF;
  WriteReg(0x0F, afterSeconds);
  WriteReg(0x0E, type_value);

  reg_value |= (1 << 0);
  reg_value &= ~(1 << 7);
  WriteReg(0x01, reg_value);
  return afterSeconds * div;
}

int RTC::SetAlarmIRQ(const RTC_TimeTypeDef &RTC_TimeStruct) {
  uint8_t irq_enable = false;
  uint8_t out_buf[4] = {0x80, 0x80, 0x80, 0x80};

  if (RTC_TimeStruct.Minutes >= 0) {
    irq_enable = true;
    out_buf[0] = ByteToBcd2(RTC_TimeStruct.Minutes) & 0x7f;
  }

  if (RTC_TimeStruct.Hours >= 0) {
    irq_enable = true;
    out_buf[1] = ByteToBcd2(RTC_TimeStruct.Hours) & 0x3f;
  }

  uint8_t reg_value = ReadReg(0x01);

  if (irq_enable) {
    reg_value |= (1 << 1);
  } else {
    reg_value &= ~(1 << 1);
  }

  for (int i = 0; i < 4; i++) {
    WriteReg(0x09 + i, out_buf[i]);
  }
  WriteReg(0x01, reg_value);

  return irq_enable ? 1 : 0;
}

int RTC::SetAlarmIRQ(const RTC_DateTypeDef &RTC_DateStruct,
                     const RTC_TimeTypeDef &RTC_TimeStruct) {
  uint8_t irq_enable = false;
  uint8_t out_buf[4] = {0x80, 0x80, 0x80, 0x80};

  if (RTC_TimeStruct.Minutes >= 0) {
    irq_enable = true;
    out_buf[0] = ByteToBcd2(RTC_TimeStruct.Minutes) & 0x7f;
  }

  if (RTC_TimeStruct.Hours >= 0) {
    irq_enable = true;
    out_buf[1] = ByteToBcd2(RTC_TimeStruct.Hours) & 0x3f;
  }

  if (RTC_DateStruct.Date >= 0) {
    irq_enable = true;
    out_buf[2] = ByteToBcd2(RTC_DateStruct.Date) & 0x3f;
  }

  if (RTC_DateStruct.WeekDay >= 0) {
    irq_enable = true;
    out_buf[3] = ByteToBcd2(RTC_DateStruct.WeekDay) & 0x07;
  }

  uint8_t reg_value = ReadReg(0x01);

  if (irq_enable) {
    reg_value |= (1 << 1);
  } else {
    reg_value &= ~(1 << 1);
  }

  for (int i = 0; i < 4; i++) {
    WriteReg(0x09 + i, out_buf[i]);
  }
  WriteReg(0x01, reg_value);

  return irq_enable ? 1 : 0;
}

void RTC::clearIRQ() {
  uint8_t data = ReadReg(0x01);
  WriteReg(0x01, data & 0xf3);
}
void RTC::disableIRQ() {
  clearIRQ();
  uint8_t data = ReadReg(0x01);
  WriteReg(0x01, data & 0xfC);
}

RTC rtc;
