#ifndef DHT_H
#define DHT_H

#include "Arduino.h"

#define PRINT(...)\
  {Serial.print(__VA_ARGS__);}
#define PRINTLN(...)\
  {Serial.println(__VA_ARGS__);}

typedef enum DEBUG_MODE
{
  DEBUG_ON = 0,
  DEBUG_OFF = 1,
}mode;

typedef struct DHT_VALUE
{
  bool is_flag;
  float temperature;
  float humidity;
};

class DHT11{
public:
  DHT11(uint8_t pin);
  void Begin(DEBUG_MODE debug);
  DHT_VALUE ReadDHT();

private:
  uint8_t _pin;
  mode _debug_mode;
  uint16_t raw_humidity=0;
  uint16_t raw_temperature=0;  
  uint8_t check_sum=0;

  void DecToBin(int n);
  void DecToBin8(int n);
  void StartSignal();
  bool Read();
  bool CheckSum();
};

#endif