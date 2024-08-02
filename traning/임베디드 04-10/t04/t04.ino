#define buttonPin 3
#define Xinp  A0
#define Yinp  A1


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(Xinp,INPUT);
  pinMode(Yinp,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int Xposi=analogRead(Xinp);
  int Yposi=analogRead(Yinp);
  int buttonstate=digitalRead(buttonPin);

  Serial.print("X : ");
  Serial.println(Xposi);

  Serial.print("Y : ");
  Serial.println(Yposi);

  Serial.print("BUTTON : ");
  Serial.println(buttonstate);

  delay(500);
}
