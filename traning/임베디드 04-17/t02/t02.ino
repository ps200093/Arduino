#include <Servo.h>

#define servoPin 3
#define temPin A0

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
  pinMode(temPin,INPUT);
}

void loop() {
  int val=analogRead(temPin);
  float v=(val*5.0)/1024.0;
  float temp =v*100;
  //float temp=24;
  float value = map(temp,0, 40, 165,15);
  Serial.print("temp : ");
  Serial.print(temp);
  Serial.println("ºC");
/*  
  Serial.print("angle : ");
  Serial.print(value);
  Serial.println("º");
  */
  myServo.write(value);  
  delay(100);
}
