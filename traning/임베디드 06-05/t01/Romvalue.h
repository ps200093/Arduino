#include <EEPROM.h>

bool EEPROM_Read(){
  byte hiByte = EEPROM.read(2);
  byte loByte = EEPROM.read(3);
  alarm_hour = word(hiByte, loByte);

  hiByte = EEPROM.read(4);
  loByte = EEPROM.read(5);
  alarm_min = word(hiByte, loByte);

  return true;
}

void EEPROM_Save(int hour, int min){
  byte hiByte = highByte(hour);
  byte loByte = lowByte(hour);
  EEPROM.write(2,hiByte);
  EEPROM.write(3,loByte);
  
  hiByte = highByte(min);
  loByte = lowByte(min);
  EEPROM.write(4,hiByte);
  EEPROM.write(5,loByte);
}