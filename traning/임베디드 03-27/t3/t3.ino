#include "LedControl.h"


LedControl lc = LedControl(12,11,10,1);


void setup()
{

  lc.shutdown(0,false);
  lc.setIntensity(0,8);
  lc.clearDisplay(0);
  lc.setLed(0,5,5,HIGH);
  lc.setLed(0,5,2,HIGH);
  
  
}

void loop()
{

}
  