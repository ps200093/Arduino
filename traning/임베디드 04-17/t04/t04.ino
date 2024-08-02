#define step 4096
int pinArray[4] = {11,10,9,8};
int cw[] = {0b1000,0b1100, 0b0100,0b0110, 0b0010,0b0011, 0b0001,0b1001};
int ccw[] = {0b0001,0b1001, 0b0001,0b0011, 0b0010,0b0110, 0b0100, 0b1100};

void setup() {
  // put your setup code here, to run once:
  for(int i = 0; i < 4; i++)
    pinMode(pinArray[i], OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  int tmp;
  for(int i = 0; i < step; i++){
    tmp = i % 8;
    digitalWrite(pinArray[0], bitRead(cw[tmp], 0));
    digitalWrite(pinArray[1], bitRead(cw[tmp], 1));
    digitalWrite(pinArray[2], bitRead(cw[tmp], 2));
    digitalWrite(pinArray[3], bitRead(cw[tmp], 3));
    delay(3);
  }
  for(int i = 0; i < step; i++){
    tmp = i % 8;
    digitalWrite(pinArray[0], bitRead(ccw[tmp], 0));
    digitalWrite(pinArray[1], bitRead(ccw[tmp], 1));
    digitalWrite(pinArray[2], bitRead(ccw[tmp], 2));
    digitalWrite(pinArray[3], bitRead(ccw[tmp], 3));
    delay(3);
  }
  delay(1000);
}