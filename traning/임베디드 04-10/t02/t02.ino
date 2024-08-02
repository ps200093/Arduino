#define IRpin A0
#define LED 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(IRpin,INPUT);
  pinMode(LED,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int i=analogRead(IRpin);
  Serial.println(i);
  if(i>400){
      digitalWrite(LED,HIGH);
  }
  else{
    digitalWrite(LED,LOW);
  }
  //delay(250);
}
