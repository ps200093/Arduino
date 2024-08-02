#define redPin 3
#define yelPin 4
#define bluePin 5
char data;

int redVal=0;
int yelVal=0;
int blueVal=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(redPin,OUTPUT);
  pinMode(yelPin,OUTPUT);
  pinMode(bluePin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    redVal=Serial.parseInt();
    yelVal=Serial.parseInt();
    blueVal=Serial.parseInt();

    if(Serial.read()=='\n'){
      if(redVal==0) digitalWrite(redPin,LOW);
      else if(redVal==1) digitalWrite(redPin,HIGH);

      if(yelVal==0) digitalWrite(yelPin,LOW);
      else if(yelVal==1) digitalWrite(yelPin,HIGH);

      if(blueVal==0) digitalWrite(bluePin,LOW);
      else if(blueVal==1) digitalWrite(bluePin,HIGH);
    }
  }
}
