#include <Servo.h>

#define servoPin 3

Servo myServo;
int deg=0;
void setup() {
  Serial.begin(9600);
  myServo.attach(servoPin);
}

void loop() {

  for (deg=0;deg<40;deg++){
    float value = map(deg,0, 40, 165,15);
      myServo.write(value);  
      delay(50);
  }
    for (deg=0;deg<40;deg++){
    float value = map(deg,0, 40, 15,165);
      myServo.write(value);  
      delay(50);
  }
}
