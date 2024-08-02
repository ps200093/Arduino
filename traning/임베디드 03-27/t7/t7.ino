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
 
  for(int i=2;i<6;i++){
    lc.setRow(0,i,B00111100);
  }
  
}
  