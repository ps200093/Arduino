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
    for(int j=0;j<8;j++){
      lc.setLed(0,i,j,HIGH);
     delay(50);
     lc.setLed(0,i,j,LOW);
     delay(50);
    }
  }

}
  