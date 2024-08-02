#define CDS A0
#define LED 3


   
void setup(){
  Serial.begin(9600);
  pinMode(CDS,INPUT);
  pinMode(LED,OUTPUT);
}

void loop(){
  int val=analogRead(CDS);
  int cout=map(val,49,969,0,5);
  cout=constrain(cout,0,5);
  for(int i=0;i<1;i++){
    if(i<cout){
      digitalWrite(LED,HIGH);
    }
    else{
      digitalWrite(LED,LOW);
    }
  }
  delay(50);
}