#include "DHT11.h"

DHT11::DHT11(uint8_t pin){
  _pin = pin;
}

void DHT11::Begin(DEBUG_MODE debug){
  _debug_mode=debug;
  if(_debug_mode == DEBUG_ON){
    PRINTLN("Debug mode : ON");
  }
  else{
    PRINTLN("Debug mode : OFF")
  }
}

void DHT11::DecToBin(int n){
  int i;
  int j;
  for(i=15;i>=0;i--){
    j=n>>1;
    if(j&1){
      PRINT("1");
    }
    else{
      PRINT("0");
    }
  }
}
void DHT11::DecToBin8(int n){
  int i;
  int j;
  for(i=7;i>=0;i--){
    j=n>>1;
    if(j&1){
      PRINT("1");
    }
    else{
      PRINT("0");
    }
  }
}

void DHT11::StartSignal(){
  pinMode(_pin,OUTPUT);
  digitalWrite(_pin,HIGH);
  delay(10);
  digitalWrite(_pin,LOW);
  delay(18);
  digitalWrite(_pin,HIGH);
  delayMicroseconds(40);
  pinMode(_pin,INPUT_PULLUP);
}

bool DHT11::Read(){
  uint16_t data=0;
  unsigned long start_time;
  
  StartSignal();

  for(int8_t i=-3;i<80;i++){
    byte live;
    start_time=micros();

    do{
      live = (unsigned long)(micros() - start_time);
      if(live > 90){
        PRINTLN("ERROR TIME OUT");
        return false;
      }
    }
    while(digitalRead(_pin) == (i & 1) ? HIGH : LOW);

    switch(i){
      case 31:
        raw_humidity=data;
        break;
      case 63:
        raw_temperature=data;
        break;
      case 79:
        check_sum=data;
        data=0;
        break;
    }
  }
  return true;
}

DHT_VALUE DHT11::ReadDHT(){
  uint8_t humi, humid;
  uint8_t temp, tempd;
  float value=NAN;

  PRINTLN("Humidity : ");
  DHT_VALUE dhtValue;
  dhtValue.is_flag=false;

  if(Read()){
    DecToBin(raw_humidity);
    PRINT("\t");
    humi=raw_humidity>>8;
    DecToBin8(humi);
    raw_humidity=raw_humidity<<8;
    humid=raw_humidity>>8;
    DecToBin8(humid);
    PRINT("\t");
    PRINT(humi);PRINT(".");PRINT(humid);
    PRINTLN("");
    PRINTLN("Temperature : ");
    DecToBin(raw_temperature);
    PRINT("\t");
    temp=raw_temperature>>8;
    DecToBin8(temp);
    raw_temperature=raw_temperature<<8;
    tempd=raw_temperature>>8;
    DecToBin8(tempd);
    PRINT("\t");
    PRINT(temp);PRINT(".");PRINT(tempd);
    PRINTLN("");

    PRINTLN("Checksum byte : ");
    PRINT("RECV : ");
    DecToBin8(check_sum);
    PRINTLN("");
    PRINT("CALL : ");
    DecToBin8(temp+tempd+humi+humid);
    PRINTLN("");

    if((byte)check_sum==(byte)(temp+tempd+humi+humid)){
      PRINTLN("Check : SUCCESS");
    }
    else{
      PRINTLN("Check : FAIL");      
    }

    PRINTLN("");PRINTLN("");
    dhtValue.is_flag=true;
    dhtValue.temperature=temp+(tempd*0.1);
    dhtValue.humidity=humi+(humid*0.1);
    
  }else{
    PRINTLN("ERROR");
      }
  return dhtValue;
}