#include <EEPROM.h>
int _write_value=2023;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  /*
  Serial.print("EEPROM read address : 0, Value : ");
  Serial.println(EEPROM.read(0));
  EEPROM.write(0, 15);
  Serial.print("EEPROM read address : 0, Value : ");
  Serial.println(EEPROM.read(0));
*/
  Serial.println("Write value : "+String(_write_value));

  byte hiByte=highByte(_write_value);
  byte loByte=lowByte(_write_value);

  EEPROM.write(1,hiByte);
  EEPROM.write(2,loByte);

  hiByte=EEPROM.read(1);
  loByte=EEPROM.read(2);

  Serial.print("HI : ");Serial.print(hiByte);
  Serial.print(", LOW : ");Serial.println(loByte);

  int readValue=word(hiByte,loByte);
  Serial.print("READ VALUE : ");Serial.println(readValue);
}

void loop() {
  // put your main code here, to run repeatedly:

}
