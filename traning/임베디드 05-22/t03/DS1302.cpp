/*
  Create by F.O.X
  Create date : 23.05.20
  File Name : DS1302.cpp
  Triple digital communication
*/

#include "DS1302.h"

#define REG_SEC   0
#define REG_MIN   1
#define REG_HOUR  2
#define REG_DAY   3
#define REG_MONTH 4
#define REG_WEEK  5
#define REG_YEAR  6
#define REG_WP    7
#define REG_TCR   8

Time::Time(){
  this->year = 2023;
  this->month = 5;
  this->day = 20;
  this->hour = 0;
  this->min = 0;
  this->sec = 0;
  this->week = 6;
}

DS1302_RAM::DS1302_RAM(){
  for(int i = 0; i < 31; i++){
    cell[i] = 0;
  }
}

DS1302::DS1302(uint8_t ce_pin, uint8_t data_pin, uint8_t sclk_pin){
  _ce_pin = ce_pin;
  _data_pin = data_pin;
  _sclk_pin = sclk_pin;

  pinMode(_ce_pin, OUTPUT);
  pinMode(_sclk_pin, OUTPUT);
}

Time DS1302::getTime(){
  Time t;
  _burstRead();

  t.sec = _decode(_burstArray[0]);
  t.min = _decode(_burstArray[1]);
  t.hour = _decodeH(_burstArray[2]);
  t.day = _decode(_burstArray[3]);
  t.month = _decode(_burstArray[4]);
  t.week = _burstArray[5];
  t.year = _decodeY(_burstArray[6]) + 2000;

  return t;
}

void DS1302::setTime(uint8_t hour, uint8_t min, uint8_t sec){
  if(((hour >= 0) && (hour < 24)) && ((min >= 0) && (min < 60)) && ((sec >= 0) && (sec < 60))){
    _writeRegister(REG_HOUR, _encode(hour));
    _writeRegister(REG_MIN, _encode(min));
    _writeRegister(REG_SEC, _encode(sec));
  }else{
    PRINTLN("Argument Error : setTime(hour, min, sec)");
  }
}

void DS1302::setDate(uint16_t year, uint8_t month, uint8_t day){
  if(((day > 0) && (day <= 31)) && ((month > 0) && (month <= 12)) && ((year >= 2000) && (year < 3000))){
    year -= 2000;
    _writeRegister(REG_YEAR, _encode(year));
    _writeRegister(REG_MONTH, _encode(month));
    _writeRegister(REG_DAY, _encode(day));
  }else{
    PRINTLN("Argument Error : setDate(day, month, year)");
  }
}

void DS1302::setWeek(uint8_t week){
  if((week > 0) && (week < 8)){
    _writeRegister(REG_WEEK, week);
  }else{
    PRINTLN("Argument Error : setWeek(week)");
  }
}

char *DS1302::getTimeStr(uint8_t format){
  char *output = "xxxxxxxx";
  Time t;
  t = getTime();

  if(t.hour < 10){
    output[0] = 48;
  }else{
    output[0] = char((t.hour / 10) + 48);
  }

  output[1] = char((t.hour % 10) + 48);
  output[2] = 58;

  if(t.min < 10){
    output[3] = 48;
  }else{
    output[3] = char((t.min / 10) + 48);
  }

  output[4] = char((t.min % 10) + 48);
  output[5] = 58;

  if(format == FORMAT_SHORT){
    output[5] = 0;
  }else{
    if(t.sec < 10){
      output[6] = 48;
    }else{
      output[6] = char((t.sec / 10) + 48);
    }

    output[7] = char((t.sec % 10) + 48);
    output[8] = 0;
  }

  return output;
}

char *DS1302::getDateStr(uint8_t slFormat, uint8_t eFormat, char divider){
  char *output = "xxxxxxxxxx";  
  int iYear, offset;
  Time t;
  t = getTime();

  switch(eFormat){
    case FORMAT_LITTLE_ENDIAN:
      if(slFormat == FORMAT_SHORT){
        iYear = t.year - 2000;

        if(iYear < 10){
          output[0] = 48;
        }else{
          output[0] = char((iYear / 10) + 48);
        }
      }else{
        iYear = t.year;
        output[0] = char((iYear / 1000) + 48);
        output[1] = char(((iYear % 1000) / 100) + 48);
        output[2] = char(((iYear % 100) / 10) + 48);
        output[3] = char((iYear % 10) + 48);
        output[4] = divider;
      }

      if(t.month < 10){
        output[5] = 48;
      }else{
        output[5] = char((t.month / 10) + 48);
      }

      output[6] = char((t.month %10 ) + 48);
      output[7] = divider;

      if(t.day < 10){
        output[8] = 48;
      }else{
        output[8] = char((t.day / 10) + 48);
      }

      output[9] = char((t.day % 10) + 48);
      output[10] = 0;

      break;
    case FORMAT_BIG_ENDIAN:
      if(slFormat == FORMAT_SHORT){
        offset = 0;
      }else{
        offset = 2;
      }

      if(slFormat == FORMAT_SHORT){
        iYear = t.year - 2000;
        if(iYear < 10){
          output[0] = 48;
        }else{
          output[0] = char((iYear / 10) + 48);
        }

        output[1] = char((iYear % 10) + 48);
        output[2] = divider;
      }else{
        iYear = t.year;
        output[0] = char((iYear / 1000) + 48);
        output[1] = char(((iYear % 1000) / 100) + 48);
        output[2] = char(((iYear % 100) / 10) + 48);
        output[3] = char((iYear % 10) + 48);
        output[4] = divider;
      }

      if(t.month < 10){
        output[3 + offset] = 48;
      }else{
        output[3 + offset] = char((t.month / 10) + 48);
      }

      output[4 + offset] = char((t.month % 10) + 48);
      output[5 + offset] = divider;

      if(t.day < 10){
        output[6 + offset] = 48;
      }else{
        output[6 + offset] = char((t.day / 10) + 48);
      }

      output[7 + offset] = char((t.day % 10) + 48);
      output[8 + offset] = 0;

      break;

    case FORMAT_MIDDLE_ENDIAN:
      if(t.month < 10){
        output[0] = 48;
      }else{
        output[0] = char((t.month / 10) + 48);
      }

      output[1] = char((t.month % 10) + 48);
      output[2] = divider;

      if(t.day < 10){
        output[3] = 48;
      }else{
        output[3] = char((t.day / 10) + 48);
      }

      output[4] = char((t.day % 10) + 48);
      output[5] = divider;

      if(slFormat == FORMAT_SHORT){
        iYear = t.year - 2000;
        if(iYear < 10){
          output[6] = 48;
        }else{
          output[6] = char((iYear / 10) + 48);
        }

        output[7] = char((iYear % 10) + 48);
        output[8] = 0;
      }else{
        iYear = t.year;
        output[6] = char((iYear / 1000) + 48);
        output[7] = char(((iYear % 1000) / 100) + 48);
        output[8] = char(((iYear % 100) / 10) + 48);
        output[9] = char((iYear %10) + 48);
        output[10] = 0;
      }
      break;
  }

  return output;
}

char *DS1302::getWeekStr(uint8_t format){
  char *output = "xxxxxxxxx";
  Time t;
  t = getTime();

  switch(t.week){
    case MONDAY:
      output =  "Monday";
      break;
    case TUESDAY:
      output = "Tuesday";
      break;
    case WEDNESDAY:
      output = "Wednesday";
      break;
    case THURSDAY:
      output = "Thursday";
      break;
    case FRIDAY:
      output = "Friday";
      break;
    case SATURDAY:
      output = "Saturday";
      break;
    case SUNDAY:
      output = "Sunday";
      break;
  }

  if(format == FORMAT_SHORT){
    output[3] = 0;
  }

  return output;
}


char *DS1302::getMonthStr(uint8_t format){
  char *output = "xxxxxxxxx";
  Time t;
  t = getTime();

  switch(t.month){
    case 1:
      output = "January";
      break;
    case 2:
      output = "February";
      break;
    case 3:
      output = "March";
      break;
    case 4:
      output = "April";
      break;
    case 5:
      output = "May";
      break;
    case 6:
      output = "June";
      break;
    case 7:
      output = "July";
      break;
    case 8:
      output = "August";
      break;
    case 9:
      output = "September";
      break;
    case 10:
      output = "October";
      break;
    case 11:
      output = "November";
      break;
    case 12:
      output = "December";
      break;
  }

  if(format == FORMAT_SHORT){
    output[3] = 0;
  }

  return output;
}

void DS1302::runningMode(bool enable){
  uint8_t _reg = _readRegister(REG_SEC);
  _reg &= ~(1 << 7);
  _reg |= (enable << 7);
  _writeRegister(REG_SEC, _reg);
}

void DS1302::writeProtect(bool enable){
  uint8_t _reg = (enable << 7);
  _writeRegister(REG_WP, _reg);
}

void DS1302::setTCR(uint8_t value){
  _writeRegister(REG_TCR, value);
}


uint8_t DS1302::_readByte(){
  pinMode(_data_pin, INPUT);

  uint8_t value = 0;
  uint8_t currentBit = 0;

  for(int i = 0; i < 8; ++i){
    currentBit = digitalRead(_data_pin);
    value |= (currentBit << i);
    digitalWrite(_sclk_pin, HIGH);
    delayMicroseconds(1);
    digitalWrite(_sclk_pin, LOW);
  }

  return value;
}


void DS1302::_writeByte(uint8_t value){
  pinMode(_data_pin, OUTPUT);
  shiftOut(_data_pin, _sclk_pin, LSBFIRST, value);
}

uint8_t DS1302::_readRegister(uint8_t reg){
  uint8_t cmdByte = 129;
  cmdByte |= (reg << 1);
  uint8_t readValue;

  digitalWrite(_sclk_pin, LOW);
  digitalWrite(_ce_pin, HIGH);

  _writeByte(cmdByte);
  readValue = _readByte();

  digitalWrite(_ce_pin, LOW);

  return readValue;
}


void DS1302::_writeRegister(uint8_t  reg, uint8_t value){
  uint8_t cmdByte = (128 | (reg << 1));

  digitalWrite(_sclk_pin, LOW);
  digitalWrite(_ce_pin, HIGH);

  _writeByte(cmdByte);
  _writeByte(value);

  digitalWrite(_ce_pin, LOW);
}

void DS1302::_burstRead(){
  digitalWrite(_sclk_pin, LOW);
  digitalWrite(_ce_pin, HIGH);

  _writeByte(191);
  for(int i = 0; i < 8; i++){
    _burstArray[i] = _readByte();
  }

  digitalWrite(_ce_pin, LOW);
}

uint8_t DS1302::_decode(uint8_t value){
  uint8_t decoded = value & 127;
  decoded = (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);

  return decoded;
}

uint8_t DS1302::_decodeH(uint8_t value){
  if(value & 128){
    value = (value & 15) + (12 * ((value & 32) >> 5));
  }else{
    value = (value & 15) + (10 * ((value & 48) >> 4));
  }

  return value;
}

uint8_t DS1302::_decodeY(uint8_t value){
  uint8_t decoded = (value & 15) + 10 * ((value & (15 << 4)) >> 4);
  return decoded;
}

uint8_t DS1302::_encode(uint8_t value){
  uint8_t encoded = ((value / 10) << 4) + (value % 10);
  return encoded;
}

void DS1302::writeBuffer(DS1302_RAM r){
  digitalWrite(_sclk_pin, LOW);
  digitalWrite(_ce_pin, HIGH);

  _writeByte(254);
  for(int i = 0; i < 31; i++){
    _writeByte(r.cell[i]);
  }

  digitalWrite(_ce_pin,LOW);
}

DS1302_RAM DS1302::readBuffer(){
  DS1302_RAM r;

  digitalWrite(_sclk_pin, LOW);
  digitalWrite(_ce_pin, HIGH);

  _writeByte(255);
  for(int i = 0; i < 31; i++){
    r.cell[i] = _readByte();
  }

  digitalWrite(_ce_pin, LOW);

  return r;
}

void DS1302::poke(uint8_t addr, uint8_t value){
  if((addr >= 0) && (addr <= 30)){
    addr = (addr * 2) + 192;

    digitalWrite(_sclk_pin, LOW);
    digitalWrite(_ce_pin, HIGH);

    _writeByte(addr);
    _writeByte(value);

    digitalWrite(_ce_pin, LOW);
  }else{
    PRINTLN("poke() --> Error");
  }
}

uint8_t DS1302::peek(uint8_t addr){
  if((addr >= 0) && (addr <= 30)){
    addr = (addr * 2) + 193;

    uint8_t readValue;

    digitalWrite(_sclk_pin, LOW);
    digitalWrite(_ce_pin, HIGH);

    _writeByte(addr);
    readValue = _readByte();

    digitalWrite(_ce_pin, LOW);

    return readValue;
  }else{
    PRINTLN("peek() --> Error");
    return 0;
  }
}





























