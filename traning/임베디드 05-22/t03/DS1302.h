/*
  Create by F.O.X
  Create date : 23.05.20
  File Name : DS1302.h
  Triple digital communication
*/

#ifndef DS1302_h
#define DS1302_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

#define PRINT(...) \
  { Serial.print(__VA_ARGS__); }
#define PRINTLN(...) \
  { Serial.println(__VA_ARGS__); }

#define FORMAT_SHORT  1
#define FORMAT_LONG   2

#define FORMAT_LITTLE_ENDIAN  1
#define FORMAT_BIG_ENDIAN     2
#define FORMAT_MIDDLE_ENDIAN  3

#define MONDAY    1
#define TUESDAY   2
#define WEDNESDAY 3
#define THURSDAY  4
#define FRIDAY    5
#define SATURDAY  6
#define SUNDAY    7

#define TCR_D1R2K 165
#define TCR_D1R4K 166
#define TCR_D1R8K 167
#define TCR_D2R2K 169
#define TCR_D2R4K 170
#define TCR_D2R8K 171
#define TCR_OFF   92

class Time{
public:
  uint16_t  year;
  uint8_t   month;
  uint8_t   day;
  uint8_t   hour;
  uint8_t   min;
  uint8_t   sec;

  uint8_t   week;

  Time();
};

class DS1302_RAM{
public:
  byte  cell[31];
  DS1302_RAM();
};

class DS1302{
public:
  DS1302(uint8_t ce_pin, uint8_t data_pin, uint8_t sclk_pin);

  Time getTime();

  void setTime(uint8_t hour, uint8_t min, uint8_t sec);
  void setDate(uint16_t year, uint8_t month, uint8_t day);
  void setWeek(uint8_t week);

  char *getTimeStr(uint8_t format=FORMAT_LONG);
  char *getDateStr(uint8_t slFormat=FORMAT_LONG, uint8_t eFormat=FORMAT_LITTLE_ENDIAN, char divider='.');
  char *getWeekStr(uint8_t format=FORMAT_LONG);
  char *getMonthStr(uint8_t format=FORMAT_LONG);

  void runningMode(bool enable);
  void writeProtect(bool enable);
  void setTCR(uint8_t value);

  void writeBuffer(DS1302_RAM r);
  DS1302_RAM readBuffer();
  void poke(uint8_t addr, uint8_t value);
  uint8_t peek(uint8_t addr);

private:
  uint8_t _ce_pin;
  uint8_t _data_pin;
  uint8_t _sclk_pin;
  uint8_t _burstArray[8];

  uint8_t _readByte();
  uint8_t _readRegister(uint8_t reg);
  void _burstRead();
  void _writeRegister(uint8_t reg, uint8_t value);
  void _writeByte(uint8_t value);

  uint8_t _encode(uint8_t value);
  uint8_t _decode(uint8_t value);
  uint8_t _decodeH(uint8_t value);
  uint8_t _decodeY(uint8_t value);
};

#endif
