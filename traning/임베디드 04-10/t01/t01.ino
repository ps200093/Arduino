#include <IRremote.h>
#define IRpin 11
IRrecv irrecv(IRpin);
decode_results results;

String decodeType[19]={
  "UNKNOWN","UNUSED","RC5","RD6","NEC","SONY","PANASONIC","JVC","SAMSUNG",
  "WHYNTER","AIWA_RC_T501","LG","SANYO","MITSUBISHI","DISH","SHARP","DENON",
  "PRONTO","LOGO_PF"
};

void setup() {
  Serial.begin(9600);
  delay(3000);
  Serial.println(F("IR Recv Program"));
  irrecv.enableIRIn();
  irrecv.blink13(true);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irrecv.decode(&results)){
    Serial.print("Decode Type : ");
    Serial.println(decodeType[results.decode_type + 1]);
    Serial.print("Received data : 0x");
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
  delay(250);
}
