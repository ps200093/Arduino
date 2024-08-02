#define CDS A0
#define LED 3


   
void setup(){
  Serial.begin(9600);
  pinMode(CDS,INPUT);
  pinMode(LED,OUTPUT);
}

void loop(){
  int val=analogRead(CDS);
  int cout=map(val,200,969,0,255);
  cout=constrain(cout,0,255);
  Serial.println(val);
  Serial.println(cout);
  analogWrite(LED,cout);
}