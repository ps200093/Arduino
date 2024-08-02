#include "DS1302.h"

const int clk=7;
const int dat=6;
const int rst=5;

DS1302 rtc(rst,dat,clk);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("DS1302 RTC");
  rtc.runningMode(false);
  rtc.writeProtect(false);

  //rtc.setWeek(MONDAY);
  //rtc.setTime(13, 20, 0);
  //rtc.setDate(2023, 5, 22);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(rtc.getWeekStr());Serial.print(" ");
  Serial.print(rtc.getDateStr());Serial.print(" ");  
  Serial.println(rtc.getTimeStr());
  delay(1000);
}
