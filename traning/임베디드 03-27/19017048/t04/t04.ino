#define VAR_RES A0
#define RED_P 3
#define GRE_P 5
#define BLE_P 6
const int led[3]={3,5,6};

   
void setup(){
  Serial.begin(9600);
  pinMode(VAR_RES,INPUT);
  pinMode(RED_P,OUTPUT);
  pinMode(GRE_P,OUTPUT);
  pinMode(BLE_P,OUTPUT);
  //analogWrite(RED_P,46);
  //analogWrite(GRE_P,93);
  //analogWrite(BLE_P,154);
}

void loop(){
  int val=analogRead(VAR_RES);
  int cout=map(val,0,1024,0,4);
  cout=constrain(cout,0,4);
  for(int i=0;i<4;i++){
    if(i<cout){
      digitalWrite(led[i],HIGH);
    }
    else{
      digitalWrite(led[i],LOW);
    }
  }
  delay(50);
}