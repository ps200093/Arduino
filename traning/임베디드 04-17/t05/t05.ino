#include <Stepper.h>
const int step=2048;

Stepper stepMotor(step,8,9,10,11);

void setup() {
  // put your setup code here, to run once:
  stepMotor.setSpeed(14);
}

void loop() {
  // put your main code here, to run repeatedly:
  stepMotor.setSpeed(14);
}
