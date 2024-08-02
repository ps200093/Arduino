const int numRows=4;
const int numCols=4;

int pinRows[numRows]={6,7,8,9};
int pinCols[numCols]={5,4,3,2};

void setup(){
  Serial.begin(9600);
  for(int i=0;i<numRows;i++){
    pinMode(pinRows[i],INPUT_PULLUP);
  }
  for(int i=0;i<numCols;i++){
    pinMode(pinCols[i],OUTPUT);
    digitalWrite(pinCols[i],HIGH);
  }

}

void loop(){
  for(int i=0;i<numCols;i++){
    digitalWrite(pinCols[i],LOW);
    for(int j=0;j<numRows;j++){
      if(digitalRead(pinRows[j])==LOW){
        Serial.print("Press anyKeys");
        Serial.print(j);
        Serial.print("Press anyKeys");
        Serial.print(i);
      }
    
    }
    digitalWrite(pinCols[i],HIGH);
  }
  delay(100);
}