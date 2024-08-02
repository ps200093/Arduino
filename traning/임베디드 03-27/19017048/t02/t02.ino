#define VAR_RES A0


void setup(){
  Serial.begin(9600);
pinMode(VAR_RES,INPUT);
}

void loop(){
  int val_var_res=analogRead(VAR_RES);
  float ang=val_var_res/3.78;
  Serial.print("Variable Resistor : ");
  Serial.println(val_var_res);
  Serial.print("DEG : ");
  Serial.println(ang);
  delay(500);
}