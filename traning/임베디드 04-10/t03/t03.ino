#define TMPpin A0
#define LED 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(TMPpin,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i=analogRead(TMPpin);
  //Serial.println(i);
  float Voltage=(i*5.0)/1024.0;
  Serial.print("RAW : ");
  Serial.println(Voltage);
  Serial.print("TEMP : ");
  Serial.println(Voltage*100);
  delay(250);
}
