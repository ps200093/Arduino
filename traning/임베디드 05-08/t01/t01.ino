#include <SoftwareSerial.h>

SoftwareSerial RFModule(3,2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  RFModule.begin(9600);
  RFModule.println("Start RF Module");
}

void loop() {
  // put your main code here, to run repeatedl
  if(RFModule.available()>0){
    String inString=RFModule.readStringUntil('\n');
    Serial.println(inString);
  }
  if(Serial.available()>0){
    String inString=Serial.readStringUntil('\n');
    RFModule.println(inString);
  }

}
#include <SoftwareSerial.h>

SoftwareSerial RFModule(3,2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  RFModule.begin(9600);
  RFModule.println("Start RF Module");
}

void loop() {
  // put your main code here, to run repeatedl
  if(RFModule.available()>0){
    String inString=RFModule.readStringUntil('\n');
    Serial.println(inString);
  }
  if(Serial.available()>0){
    String inString=Serial.readStringUntil('\n');
    RFModule.println(inString);
  }

}
#include <SoftwareSerial.h>

SoftwareSerial RFModule(3,2);


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  RFModule.begin(9600);
  RFModule.println("Start RF Module");
}

void loop() {
  // put your main code here, to run repeatedl
  if(RFModule.available()>0){
    String inString=RFModule.readStringUntil('\n');
    Serial.println(inString);
  }
  if(Serial.available()>0){
    String inString=Serial.readStringUntil('\n');
    RFModule.println(inString);
  }

}
