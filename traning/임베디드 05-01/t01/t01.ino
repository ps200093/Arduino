#define ledPin 3
char data;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    data=Serial.read();
    if(data=='1'){
      digitalWrite(ledPin,HIGH);
      Serial.println("LED ON");
    }
    else if(data=='0'){
      digitalWrite(ledPin,LOW);
      Serial.println("LED OFF");
    }
  }
}
