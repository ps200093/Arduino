#include "DHT11.h"
#include <SoftwareSerial.h>
#define DHT_PIN 4

SoftwareSerial RFModule(3,2);
DHT11 dht(DHT_PIN);

void setup() {
  Serial.begin(9600);
  RFModule.begin(9600);
  dht.Begin(DEBUG_ON);
}

void loop() {
  DHT_VALUE dhtValue;
  delay(2000);
  dhtValue=dht.ReadDHT();

  if(dhtValue.is_flag==true){
    Serial.println(dhtValue.temperature);
    Serial.println(dhtValue.humidity);
    RFModule.print("t");
    RFModule.print(dhtValue.temperature);
    RFModule.print(", ");
    RFModule.print("h");
    RFModule.println(dhtValue.humidity);
  }
  else{
    RFModule.println("dht ERROR");
  }
}
