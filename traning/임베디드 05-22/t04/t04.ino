#include "DS1302.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>



#define buttonPin 9
#define Xinp  A0
#define Yinp  A1

const int clk=7;
const int dat=6;
const int rst=5;

LiquidCrystal_I2C Lcd(0x27, 16, 2);

int _current_menu=0;
char* menui[]={
  "Alram setting",
  "Time setting",
  "Exit"
};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DS1302 RTC");
  rtc.runningMode(false);
  rtc.writeProtect(false);

  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(Xinp,INPUT);
  pinMode(Yinp,INPUT);

  Lcd.init();
  Lcd.backlight();
  Lcd.createChar(menui[0]);
  Lcd.createChar(menui[1]);
  Lcd.createChar(menui[2]);

  rtc.setWeek(MONDAY);
  rtc.setTime(13, 20, 0);
  rtc.setDate(2023, 5, 22);  
}

void SetAlram(){

}
void SetTime(){

}
void Exit(){
  
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0;i<3;i++){
    Lcd.wrtie(menui[i]);
  }
}
