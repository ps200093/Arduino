const int numRows=4;
const int numCols=4;

byte pinRows[numRows]={6,7,8,9};
byte pinCols[numCols]={5,4,3,2};

char KeyPad[numRows][numCols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

void setup(){
  Serial.begin(9600);
  for(int i=0;i<numRows;i++){
    pinMode(pinRows[i],INPUT_PULLUP);
  }
  for(int j=0;j<numCols;j++){
    pinMode(pinCols[j],OUTPUT);
    digitalWrite(pinCols[j],HIGH);
  }

}

void loop(){
  for(int i=0;i<numCols;i++){
    digitalWrite(pinCols[i],LOW);

    for(int j=0;j<numRows;j++){

      if(digitalRead(pinRows[j])==LOW){

        Serial.println(KeyPad[j][i]);
      }
    
    }
    digitalWrite(pinCols[i],HIGH);
  }
  delay(100);
}