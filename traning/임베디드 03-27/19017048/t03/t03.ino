#define VAR_RES A0
int led = 3;

void setup(){
  Serial.begin(9600);
  pinMode(VAR_RES,INPUT);
  pinMode(led,OUTPUT);
}

void loop(){
  int val=analogRead(VAR_RES);
  int ang=val/4;
  analogWrite(led,ang);
  delay(50);
}