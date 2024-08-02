//#include "pitches.h"
//#define piezo 6
const int activePin=5;
const int passivePin=6;
int tones[]={261,295,330,392,440,494,523};

void setup() {
  // put your setup code here, to run once:
  pinMode(activePin,OUTPUT);
  pinMode(passivePin,OUTPUT);
  //digitalWrite(activePin,HIGH);
  //delay(500);
  //digitalWrite(activePin,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<512;i++){
    analogWrite(passivePin,i);
    //tone(passivePin,tones[i]);
    delay(500);
  }
  for(int i=0;i<8;i++){
    tone(passivePin,tones[i]);
    delay(500);
  }

  noTone(passivePin);
  delay(2000);
}
