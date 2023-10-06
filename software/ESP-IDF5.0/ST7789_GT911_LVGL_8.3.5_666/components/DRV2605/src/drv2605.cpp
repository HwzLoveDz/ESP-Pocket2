/*!
 * @file drv2605.cpp
 *
 * @mainpage Adafruit DRV2605L Haptic Driver
 *
 * @section intro_sec Introduction
 *
 * This is a library for the Adafruit DRV2605L Haptic Driver ---->
 * http://www.adafruit.com/products/2305
 *
 * Check out the links above for our tutorials and wiring diagrams.
 *
 * This motor/haptic driver uses I2C to communicate.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * @section author Author
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * @section license License
 *
 * MIT license, all text above must be included in any redistribution.
 *
 */
/**************************************************************************/

#if ARDUINO >= 100
#include "Arduino.h"
#else
// #include "WProgram.h"
#include <math.h>
#endif

#include "drv2605.hpp"

/*========================================================================*/
/*                            CONSTRUCTORS                                */
/*========================================================================*/

/**************************************************************************/
/*!
  @brief  Instantiates a new DRV2605 class. I2C, no address adjustments or pins
*/
/**************************************************************************/
Adafruit_DRV2605::Adafruit_DRV2605() {}

/*========================================================================*/
/*                           PUBLIC FUNCTIONS                             */
/*========================================================================*/

/**************************************************************************/
/*!
  @brief Setup HW using a specified Wire
  @param theWire Pointer to a TwoWire object, defaults to &Wire
  @return Return value from init()
*/
/**************************************************************************/
// bool Adafruit_DRV2605::begin(TwoWire *theWire)
// {
//   if (i2c_dev)
//     delete i2c_dev;
//   i2c_dev = new Adafruit_I2CDevice(DRV2605_ADDR, theWire);
//   return init();
// }
int Adafruit_DRV2605::begin(drv_com_fptr_t read_cb, drv_com_fptr_t write_cb, uint8_t addr)
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
bool Adafruit_DRV2605::init()
{
  // if (!i2c_dev->begin())
  // return false;
  // uint8_t id = readRegister8(DRV2605_REG_STATUS);
  // Serial.print("Status 0x"); Serial.println(id, HEX);

  writeRegister8(DRV2605_REG_MODE, 0x00); // out of standby

  writeRegister8(DRV2605_REG_RTPIN, 0x00); // no real-time-playback

  writeRegister8(DRV2605_REG_WAVESEQ1, 1); // strong click
  writeRegister8(DRV2605_REG_WAVESEQ2, 0); // end sequence

  writeRegister8(DRV2605_REG_OVERDRIVE, 0); // no overdrive

  writeRegister8(DRV2605_REG_SUSTAINPOS, 0);
  writeRegister8(DRV2605_REG_SUSTAINNEG, 0);
  writeRegister8(DRV2605_REG_BREAK, 0);
  writeRegister8(DRV2605_REG_AUDIOMAX, 0x64);

  // select ERM or LRA
  useLRA();
  // Set REG_CONTROL3
  writeRegister8(DRV2605_REG_CONTROL3,
                 readRegister8(DRV2605_REG_CONTROL3) | 0x25);

  return 0;
}

/**************************************************************************/
/*!
  @brief Select the haptic waveform to use.
  @param slot The waveform slot to set, from 0 to 7
  @param w The waveform sequence value, refers to an index in the ROM library.

    Playback starts at slot 0 and continues through to slot 7, stopping if it
  encounters a value of 0. A list of available waveforms can be found in
  section 11.2 of the datasheet: http://www.adafruit.com/datasheets/DRV2605.pdf
*/
/**************************************************************************/
void Adafruit_DRV2605::setWaveform(uint8_t slot, uint8_t w)
{
  writeRegister8(DRV2605_REG_WAVESEQ1 + slot, w);
}

/**************************************************************************/
/*!
  @brief Select the waveform library to use.
  @param lib Library to use, 0 = Empty, 1-5 are ERM, 6 is LRA.

    See section 7.6.4 in the datasheet for more details:
  http://www.adafruit.com/datasheets/DRV2605.pdf
*/
/**************************************************************************/
void Adafruit_DRV2605::selectLibrary(uint8_t lib)
{
  writeRegister8(DRV2605_REG_LIBRARY, lib);
}

/**************************************************************************/
/*!
  @brief Start playback of the waveforms (start moving!).
*/
/**************************************************************************/
void Adafruit_DRV2605::go() { writeRegister8(DRV2605_REG_GO, 1); }

/**************************************************************************/
/*!
  @brief Stop playback.
*/
/**************************************************************************/
void Adafruit_DRV2605::stop() { writeRegister8(DRV2605_REG_GO, 0); }

/**************************************************************************/
/*!
  @brief Set the device mode.
  @param mode Mode value, see datasheet section 7.6.2:
  http://www.adafruit.com/datasheets/DRV2605.pdf

    0: Internal trigger, call go() to start playback\n
    1: External trigger, rising edge on IN pin starts playback\n
    2: External trigger, playback follows the state of IN pin\n
    3: PWM/analog input\n
    4: Audio\n
    5: Real-time playback\n
    6: Diagnostics\n
    7: Auto calibration
*/
/**************************************************************************/
void Adafruit_DRV2605::setMode(uint8_t mode)
{
  writeRegister8(DRV2605_REG_MODE, mode);
}

/**************************************************************************/
/*!
  @brief Set the realtime value when in RTP mode, used to directly drive the
  haptic motor.
  @param rtp 8-bit drive value.
*/
/**************************************************************************/
void Adafruit_DRV2605::setRealtimeValue(uint8_t rtp)
{
  writeRegister8(DRV2605_REG_RTPIN, rtp);
}

/**************************************************************************/
/*!
  @brief Read an 8-bit register.
  @param reg The register to read.
  @return 8-bit value of the register.
*/
/**************************************************************************/
// uint8_t Adafruit_DRV2605::readRegister8(uint8_t reg) {
//   uint8_t buffer[1] = {reg};
//   i2c_dev->write_then_read(buffer, 1, buffer, 1);
//   return buffer[0];
// }
uint8_t Adafruit_DRV2605::readRegister8(uint8_t reg)
{
  uint8_t data;
  _readByte(reg, 1, &data);
  return data;
}
int Adafruit_DRV2605::_readByte(uint8_t reg, uint8_t nbytes, uint8_t *data)
{
  if (_read_cb != nullptr)
  {
    return _read_cb(_address, reg, data, nbytes);
  }

  return 0;
}

/**************************************************************************/
/*!
  @brief Write an 8-bit register.
  @param reg The register to write.
  @param val The value to write.
*/
/**************************************************************************/
// void Adafruit_DRV2605::writeRegister8(uint8_t reg, uint8_t val) {
//   uint8_t buffer[2] = {reg, val};
//   i2c_dev->write(buffer, 2);
// }
void Adafruit_DRV2605::writeRegister8(uint8_t reg, uint8_t val)
{
  uint8_t write_data[8];
  write_data[0] = val;
  _writeByte(reg, 1, write_data);
}
int Adafruit_DRV2605::_writeByte(uint8_t reg, uint8_t nbytes, uint8_t *data)
{
  if (_write_cb != nullptr)
  {
    return _write_cb(_address, reg, data, nbytes);
  }
  return 0;
}

/**************************************************************************/
/*!
  @brief Use ERM (Eccentric Rotating Mass) mode.
*/
/**************************************************************************/
void Adafruit_DRV2605::useERM()
{
  writeRegister8(DRV2605_REG_FEEDBACK,
                 readRegister8(DRV2605_REG_FEEDBACK) & 0x7F);
}

/**************************************************************************/
/*!
  @brief Use LRA (Linear Resonance Actuator) mode.
*/
/**************************************************************************/
void Adafruit_DRV2605::useLRA()
{
  writeRegister8(DRV2605_REG_FEEDBACK,
                 readRegister8(DRV2605_REG_FEEDBACK) | 0x80);
}

/**************************************************************************/
/*!
  @brief Now effect name.
*/
/**************************************************************************/
void Adafruit_DRV2605::effect_name(uint8_t effect)
{

    // if (effect == 1)
    // {
    //     printf("11.2 Waveform Library Effects List");
    // }

    if (effect == 1)
    {
        printf(("1 - Strong Click - 100%%\n"));
    }
    if (effect == 2)
    {
        printf(("2 - Strong Click - 60%%\n"));
    }
    if (effect == 3)
    {
        printf(("3 - Strong Click - 30%%\n"));
    }
    if (effect == 4)
    {
        printf(("4 - Sharp Click - 100%%\n"));
    }
    if (effect == 5)
    {
        printf(("5 - Sharp Click - 60%%\n"));
    }
    if (effect == 6)
    {
        printf(("6 - Sharp Click - 30%%\n"));
    }
    if (effect == 7)
    {
        printf(("7 - Soft Bump - 100%%\n"));
    }
    if (effect == 8)
    {
        printf(("8 - Soft Bump - 60%%\n"));
    }
    if (effect == 9)
    {
        printf(("9 - Soft Bump - 30%%\n"));
    }
    if (effect == 10)
    {
        printf(("10 - Double Click - 100%%\n"));
    }
    if (effect == 11)
    {
        printf(("11 - Double Click - 60%%\n"));
    }
    if (effect == 12)
    {
        printf(("12 - Triple Click - 100%%\n"));
    }
    if (effect == 13)
    {
        printf(("13 - Soft Fuzz - 60%%\n"));
    }
    if (effect == 14)
    {
        printf(("14 - Strong Buzz - 100%%\n"));
    }
    if (effect == 15)
    {
        printf(("15 - 750 ms Alert 100%%\n"));
    }
    if (effect == 16)
    {
        printf(("16 - 1000 ms Alert 100%%\n"));
    }
    if (effect == 17)
    {
        printf(("17 - Strong Click 1 - 100%%\n"));
    }
    if (effect == 18)
    {
        printf(("18 - Strong Click 2 - 80%%\n"));
    }
    if (effect == 19)
    {
        printf(("19 - Strong Click 3 - 60%%\n"));
    }
    if (effect == 20)
    {
        printf(("20 - Strong Click 4 - 30%%\n"));
    }
    if (effect == 21)
    {
        printf(("21 - Medium Click 1 - 100%%\n"));
    }
    if (effect == 22)
    {
        printf(("22 - Medium Click 2 - 80%%\n"));
    }
    if (effect == 23)
    {
        printf(("23 - Medium Click 3 - 60%%\n"));
    }
    if (effect == 24)
    {
        printf(("24 - Sharp Tick 1 - 100%%\n"));
    }
    if (effect == 25)
    {
        printf(("25 - Sharp Tick 2 - 80%%\n"));
    }
    if (effect == 26)
    {
        printf(("26 - Sharp Tick 3 - 60%%\n"));
    }
    if (effect == 27)
    {
        printf(("27 - Short Double Click Strong 1 - 100%%\n"));
    }
    if (effect == 28)
    {
        printf(("28 - Short Double Click Strong 2 - 80%%\n"));
    }
    if (effect == 29)
    {
        printf(("29 - Short Double Click Strong 3 - 60%%\n"));
    }
    if (effect == 30)
    {
        printf(("30 - Short Double Click Strong 4 - 30%%\n"));
    }
    if (effect == 31)
    {
        printf(("31 - Short Double Click Medium 1 - 100%%\n"));
    }
    if (effect == 32)
    {
        printf(("32 - Short Double Click Medium 2 - 80%%\n"));
    }
    if (effect == 33)
    {
        printf(("33 - Short Double Click Medium 3 - 60%%\n"));
    }
    if (effect == 34)
    {
        printf(("34 - Short Double Sharp Tick 1 - 100%%\n"));
    }
    if (effect == 35)
    {
        printf(("35 - Short Double Sharp Tick 2 - 80%%\n"));
    }
    if (effect == 36)
    {
        printf(("36 - Short Double Sharp Tick 3 - 60%%\n"));
    }
    if (effect == 37)
    {
        printf(("37 - Long Double Sharp Click Strong 1 - 100%%\n"));
    }
    if (effect == 38)
    {
        printf(("38 - Long Double Sharp Click Strong 2 - 80%%\n"));
    }
    if (effect == 39)
    {
        printf(("39 - Long Double Sharp Click Strong 3 - 60%%\n"));
    }
    if (effect == 40)
    {
        printf(("40 - Long Double Sharp Click Strong 4 - 30%%\n"));
    }
    if (effect == 41)
    {
        printf(("41 - Long Double Sharp Click Medium 1 - 100%%\n"));
    }
    if (effect == 42)
    {
        printf(("42 - Long Double Sharp Click Medium 2 - 80%%\n"));
    }
    if (effect == 43)
    {
        printf(("43 - Long Double Sharp Click Medium 3 - 60%%\n"));
    }
    if (effect == 44)
    {
        printf(("44 - Long Double Sharp Tick 1 - 100%%\n"));
    }
    if (effect == 45)
    {
        printf(("45 - Long Double Sharp Tick 2 - 80%%\n"));
    }
    if (effect == 46)
    {
        printf(("46 - Long Double Sharp Tick 3 - 60%%\n"));
    }
    if (effect == 47)
    {
        printf(("47 - Buzz 1 - 100%%\n"));
    }
    if (effect == 48)
    {
        printf(("48 - Buzz 2 - 80%%\n"));
    }
    if (effect == 49)
    {
        printf(("49 - Buzz 3 - 60%%\n"));
    }
    if (effect == 50)
    {
        printf(("50 - Buzz 4 - 40%%\n"));
    }
    if (effect == 51)
    {
        printf(("51 - Buzz 5 - 20%%\n"));
    }
    if (effect == 52)
    {
        printf(("52 - Pulsing Strong 1 - 100%%\n"));
    }
    if (effect == 53)
    {
        printf(("53 - Pulsing Strong 2 - 60%%\n"));
    }
    if (effect == 54)
    {
        printf(("54 - Pulsing Medium 1 - 100%%\n"));
    }
    if (effect == 55)
    {
        printf(("55 - Pulsing Medium 2 - 60%%\n"));
    }
    if (effect == 56)
    {
        printf(("56 - Pulsing Sharp 1 - 100%%\n"));
    }
    if (effect == 57)
    {
        printf(("57 - Pulsing Sharp 2 - 60%%\n"));
    }
    if (effect == 58)
    {
        printf(("58 - Transition Click 1 - 100%%\n"));
    }
    if (effect == 59)
    {
        printf(("59 - Transition Click 2 - 80%%\n"));
    }
    if (effect == 60)
    {
        printf(("60 - Transition Click 3 - 60%%\n"));
    }
    if (effect == 61)
    {
        printf(("61 - Transition Click 4 - 40%%\n"));
    }
    if (effect == 62)
    {
        printf(("62 - Transition Click 5 - 20%%\n"));
    }
    if (effect == 63)
    {
        printf(("63 - Transition Click 6 - 10%%\n"));
    }
    if (effect == 64)
    {
        printf(("64 - Transition Hum 1 - 100%%\n"));
    }
    if (effect == 65)
    {
        printf(("65 - Transition Hum 2 - 80%%\n"));
    }
    if (effect == 66)
    {
        printf(("66 - Transition Hum 3 - 60%%\n"));
    }
    if (effect == 67)
    {
        printf(("67 - Transition Hum 4 - 40%%\n"));
    }
    if (effect == 68)
    {
        printf(("68 - Transition Hum 5 - 20%%\n"));
    }
    if (effect == 69)
    {
        printf(("69 - Transition Hum 6 - 10%%\n"));
    }
    if (effect == 70)
    {
        printf(("70 - Transition Ramp Down Long Smooth 1 - 100 to 0%%\n"));
    }
    if (effect == 71)
    {
        printf(("71 - Transition Ramp Down Long Smooth 2 - 100 to 0%%\n"));
    }
    if (effect == 72)
    {
        printf(("72 - Transition Ramp Down Medium Smooth 1 - 100 to 0%%\n"));
    }
    if (effect == 73)
    {
        printf(("73 - Transition Ramp Down Medium Smooth 2 - 100 to 0%%\n"));
    }
    if (effect == 74)
    {
        printf(("74 - Transition Ramp Down Short Smooth 1 - 100 to 0%%\n"));
    }
    if (effect == 75)
    {
        printf(("75 - Transition Ramp Down Short Smooth 2 - 100 to 0%%\n"));
    }
    if (effect == 76)
    {
        printf(("76 - Transition Ramp Down Long Sharp 1 - 100 to 0%%\n"));
    }
    if (effect == 77)
    {
        printf(("77 - Transition Ramp Down Long Sharp 2 - 100 to 0%%\n"));
    }
    if (effect == 78)
    {
        printf(("78 - Transition Ramp Down Medium Sharp 1 - 100 to 0%%\n"));
    }
    if (effect == 79)
    {
        printf(("79 - Transition Ramp Down Medium Sharp 2 - 100 to 0%%\n"));
    }
    if (effect == 80)
    {
        printf(("80 - Transition Ramp Down Short Sharp 1 - 100 to 0%%\n"));
    }
    if (effect == 81)
    {
        printf(("81 - Transition Ramp Down Short Sharp 2 - 100 to 0%%\n"));
    }
    if (effect == 82)
    {
        printf(("82 - Transition Ramp Up Long Smooth 1 - 0 to 100%%\n"));
    }
    if (effect == 83)
    {
        printf(("83 - Transition Ramp Up Long Smooth 2 - 0 to 100%%\n"));
    }
    if (effect == 84)
    {
        printf(("84 - Transition Ramp Up Medium Smooth 1 - 0 to 100%%\n"));
    }
    if (effect == 85)
    {
        printf(("85 - Transition Ramp Up Medium Smooth 2 - 0 to 100%%\n"));
    }
    if (effect == 86)
    {
        printf(("86 - Transition Ramp Up Short Smooth 1 - 0 to 100%%\n"));
    }
    if (effect == 87)
    {
        printf(("87 - Transition Ramp Up Short Smooth 2 - 0 to 100%%\n"));
    }
    if (effect == 88)
    {
        printf(("88 - Transition Ramp Up Long Sharp 1 - 0 to 100%%\n"));
    }
    if (effect == 89)
    {
        printf(("89 - Transition Ramp Up Long Sharp 2 - 0 to 100%%\n"));
    }
    if (effect == 90)
    {
        printf(("90 - Transition Ramp Up Medium Sharp 1 - 0 to 100%%\n"));
    }
    if (effect == 91)
    {
        printf(("91 - Transition Ramp Up Medium Sharp 2 - 0 to 100%%\n"));
    }
    if (effect == 92)
    {
        printf(("92 - Transition Ramp Up Short Sharp 1 - 0 to 100%%\n"));
    }
    if (effect == 93)
    {
        printf(("93 - Transition Ramp Up Short Sharp 2 - 0 to 100%%\n"));
    }
    if (effect == 94)
    {
        printf(("94 - Transition Ramp Down Long Smooth 1 - 50 to 0%%\n"));
    }
    if (effect == 95)
    {
        printf(("95 - Transition Ramp Down Long Smooth 2 - 50 to 0%%\n"));
    }
    if (effect == 96)
    {
        printf(("96 - Transition Ramp Down Medium Smooth 1 - 50 to 0%%\n"));
    }
    if (effect == 97)
    {
        printf(("97 - Transition Ramp Down Medium Smooth 2 - 50 to 0%%\n"));
    }
    if (effect == 98)
    {
        printf(("98 - Transition Ramp Down Short Smooth 1 - 50 to 0%%\n"));
    }
    if (effect == 99)
    {
        printf(("99 - Transition Ramp Down Short Smooth 2 - 50 to 0%%\n"));
    }
    if (effect == 100)
    {
        printf(("100 - Transition Ramp Down Long Sharp 1 - 50 to 0%%\n"));
    }
    if (effect == 101)
    {
        printf(("101 - Transition Ramp Down Long Sharp 2 - 50 to 0%%\n"));
    }
    if (effect == 102)
    {
        printf(("102 - Transition Ramp Down Medium Sharp 1 - 50 to 0%%\n"));
    }
    if (effect == 103)
    {
        printf(("103 - Transition Ramp Down Medium Sharp 2 - 50 to 0%%\n"));
    }
    if (effect == 104)
    {
        printf(("104 - Transition Ramp Down Short Sharp 1 - 50 to 0%%\n"));
    }
    if (effect == 105)
    {
        printf(("105 - Transition Ramp Down Short Sharp 2 - 50 to 0%%\n"));
    }
    if (effect == 106)
    {
        printf(("106 - Transition Ramp Up Long Smooth 1 - 0 to 50%%\n"));
    }
    if (effect == 107)
    {
        printf(("107 - Transition Ramp Up Long Smooth 2 - 0 to 50%%\n"));
    }
    if (effect == 108)
    {
        printf(("108 - Transition Ramp Up Medium Smooth 1 - 0 to 50%%\n"));
    }
    if (effect == 109)
    {
        printf(("109 - Transition Ramp Up Medium Smooth 2 - 0 to 50%%\n"));
    }
    if (effect == 110)
    {
        printf(("110 - Transition Ramp Up Short Smooth 1 - 0 to 50%%\n"));
    }
    if (effect == 111)
    {
        printf(("111 - Transition Ramp Up Short Smooth 2 - 0 to 50%%\n"));
    }
    if (effect == 112)
    {
        printf(("112 - Transition Ramp Up Long Sharp 1 - 0 to 50%%\n"));
    }
    if (effect == 113)
    {
        printf(("113 - Transition Ramp Up Long Sharp 2 - 0 to 50%%\n"));
    }
    if (effect == 114)
    {
        printf(("114 - Transition Ramp Up Medium Sharp 1 - 0 to 50%%\n"));
    }
    if (effect == 115)
    {
        printf(("115 - Transition Ramp Up Medium Sharp 2 - 0 to 50%%\n"));
    }
    if (effect == 116)
    {
        printf(("116 - Transition Ramp Up Short Sharp 1 - 0 to 50%%\n"));
    }
    if (effect == 117)
    {
        printf(("117 - Transition Ramp Up Short Sharp 2 - 0 to 50%%\n"));
    }
    if (effect == 118)
    {
        printf(("118 - Long buzz for programmatic stopping - 100%%\n"));
    }
    if (effect == 119)
    {
        printf(("119 - Smooth Hum 1 (No kick or brake pulse) - 50%%\n"));
    }
    if (effect == 120)
    {
        printf(("120 - Smooth Hum 2 (No kick or brake pulse) - 40%%\n"));
    }
    if (effect == 121)
    {
        printf(("121 - Smooth Hum 3 (No kick or brake pulse) - 30%%\n"));
    }
    if (effect == 122)
    {
        printf(("122 - Smooth Hum 4 (No kick or brake pulse) - 20%%\n"));
    }
    if (effect == 123)
    {
        printf(("123 - Smooth Hum 5 (No kick or brake pulse) - 10%%\n"));
    }
}

Adafruit_DRV2605 drv;
