#define Trigpin 2
#define Echopin 3
#define Piezopin 4
long dur=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(Trigpin,OUTPUT);
  pinMode(Echopin,INPUT);
  pinMode(Piezopin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(Trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(Trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(Trigpin,LOW);

  dur=pulseIn(Echopin,HIGH);
  long dis_cm=0;
  dis_cm=distance(dur);
  Serial.print("Distance = ");
  Serial.print(dis_cm);
  Serial.println("cm");

  if(dis_cm<15.1){

      digitalWrite(Piezopin,HIGH);
  }
  else if(dis_cm<20.1){
    digitalWrite(Piezopin,HIGH);
    delay(150);
    digitalWrite(Piezopin,LOW);
    delay(150);    
  }
  else if(dis_cm<40.1){
    digitalWrite(Piezopin,HIGH);
    delay(300);
    digitalWrite(Piezopin,LOW);
    delay(300);     
  }
  //delay(250);
}

long distance(long time){
  long distanceCalc;
  distanceCalc  =((time*0.034)/2);
  return distanceCalc;
  }
