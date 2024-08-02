#include "LedControl.h"


LedControl lc = LedControl(12,11,10,1);


void setup()
{
  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
}

void loop()
{
  for(int i=0;i<8;i++){
    lc.setLed(0,0,i,HIGH);
    delay(500);
    lc.setLed(0,0,i,LOW);
    delay(500);
  }

}
  