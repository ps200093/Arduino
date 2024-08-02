#define redPin 3
#define yelPin 4
#define bluPin 5
char data;

int redVal=0;
int yelVal=0;
int blueVal=0;


void setup() {
  // put your setup code here, to run once:
  pinMode(redPin,OUTPUT);
  pinMode(yelPin,OUTPUT);
  pinMode(bluPin,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()>0){
    String req=Serial.readStringUntil('\r');
    req.replace("\n","");
    Serial.println(req);

    int comPos=req.indexOf(',');
    Serial.print("Comma Index : ");
    Serial.println(comPos);

    String color=req.substring(0,comPos);
    Serial.print("COLOR : ");
    Serial.println(color);

    String cmd=req.substring(comPos+1,req.length());
    Serial.print("COMMAND : ");
    Serial.println(cmd);

    if(color=="RED"){
      if(cmd=="ON"){
        digitalWrite(redPin,HIGH);
      }
      else if(cmd=="OFF"){
        digitalWrite(redPin,LOW);
      }
    }
    if(color=="YEL"){
      if(cmd=="ON"){
        digitalWrite(yelPin,HIGH);
      }
      else if(cmd=="OFF"){
        digitalWrite(yelPin,LOW);
      }
    }
    if(color=="BLUE"){
      if(cmd=="ON"){
        digitalWrite(bluPin,HIGH);
      }
      else if(cmd=="OFF"){
        digitalWrite(bluPin,LOW);
      }
    }
  }
}
