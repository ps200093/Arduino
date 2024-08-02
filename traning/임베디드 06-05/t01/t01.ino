#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#include "DS1302.h"
#include "imageList.h"



const int clk=7;
const int dat=6;
const int rst=5;

const int buz_pin = 10;

const int xAxis_pin = A0;
const int yAxis_pin = A1;
const int btn_pin = 9;

DS1302 rtc(rst,dat,clk);
LiquidCrystal_I2C lcd(0x27,16,2);

int year, month, day, hour, min, sec;
int alarm_hour, alarm_min;

int isMenu = 0;//0->time, 1-> menu
bool isSubMenu=false;
bool isAlarm=false;
String ampm;


void setup() {
  Serial.begin(9600);
  Serial.println("Alarm timer starting...");
  rtc.runningMode(false);
  rtc.writeProtect(false);

  pinMode(xAxis_pin,INPUT);
  pinMode(yAxis_pin,INPUT);
  pinMode(btn_pin,INPUT_PULLUP);
  pinMode(buz_pin,OUTPUT);

  lcd.init();
  lcd.backlight();

  lcd.createChar(0, p20);
  lcd.createChar(1, p40);
  lcd.createChar(2, p60);
  lcd.createChar(3, p80);
  lcd.createChar(4, p100);
  lcd.createChar(5, menu);
  lcd.createChar(6, clock);
  
  //Loading(); 
  Read_setValue();
}

void loop() {
  switch(isMenu){
    case 0:
      TimeDisplay();
      delay(750);
      break;
    case 1:
      SelectMenu();
      break;
  }

  SelectBtn();
  delay(250);
  /*
  Serial.print("X pos : ");
  Serial.println(xAxis_pin);
  Serial.print("Y pos : ");
  Serial.println(yAxis_pin);
  Serial.print("Btn state : ");
  Serial.println(btn_pin);
  */
}
