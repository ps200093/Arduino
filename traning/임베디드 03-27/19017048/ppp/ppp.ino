#define CDS A0
#define dgt 3


   
void setup(){
  Serial.begin(9600);
  pinMode(CDS,INPUT);
  pinMode(dgt,OUTPUT);
}

void loop(){
  int val=analogRead(CDS);
  int cout=map(val,0,1023,0,255);
  cout=constrain(cout,0,255);
  int i =0;
   if(i<cout){
     digitalWrite(dgt,HIGH);
   }
   else{
     digitalWrite(dgt,LOW);
   }
  
  delay(50);
}