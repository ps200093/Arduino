#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "DHT11.h"
#include "hertani.h"
#include "menu.h"
#include "prog.h"


#define DHT_PIN 8
#define buttonPin 9
#define Xinp  A0
#define Yinp  A1

LiquidCrystal_I2C Lcd(0x27, 16, 2);

int _current_menu=0;
bool _isSelect=false;
char* menui[]={
  "Heart ani     ",
  "Progress bar  ",
  "Temp/Humi     "
};

DHT11 dht(DHT_PIN);
bool is_sens;

void setup(){
  Serial.begin(9600);
  pinMode(buttonPin,INPUT_PULLUP);
  pinMode(Xinp,INPUT);
  pinMode(Yinp,INPUT);
  Lcd.init();
  Lcd.backlight();
  Lcd.createChar(0,h0);
  Lcd.createChar(1,h1);

  Lcd.createChar(2,arr0);
  Lcd.createChar(3,arr1);

  Lcd.createChar(4,menui[0]);
  Lcd.createChar(5,menui[1]);
  Lcd.createChar(6,menui[2]);

  Lcd.createChar(7,p20);
  Lcd.createChar(8,p40);
  Lcd.createChar(9,p60);
  Lcd.createChar(10,p80);
  Lcd.createChar(11,p100);

  dht.Begin(DEBUG_ON);
}

void Heart(){
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(menui[_current_menu]);
  for(int t=0;t<11;t++){
    for(int h=0;h<2;h++){
      delay(100);
      Lcd.setCursor(0,1);
      Lcd.write(h);
      delay(500);
    }
  }    
}


void ProgressBar(){
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(menui[_current_menu]);

  Lcd.setCursor(0,1);
  for(int i=0;i<16;i++){
      for(int j=7;j<12;j++){
        Lcd.setCursor(i,1);
        Lcd.write(j);
        delay(100);
      }
  }
  Lcd.clear();
}

void Dht(){
  Lcd.clear();
  Lcd.clear();
  Lcd.setCursor(0, 0);
  Lcd.print(menui[_current_menu]);

  Lcd.setCursor(0,1);
  
  DHT_VALUE dhtValue;
  delay(2000);
  dhtValue=dht.ReadDHT();
  float dvt=dhtValue.temperature;
  float dvh=dhtValue.humidity;
  Lcd.setCursor(0, 1);
  Lcd.print("t : ");
  Lcd.write(dvt);
  Lcd.print("h : ");
  Lcd.write(dvh);
  delay(2000);
}

void mi(){
  Lcd.setCursor(0,0);
  Lcd.print("Arduino MENU");
  for(int r=2;r<4;r++){
    Lcd.setCursor(0,1);
    Lcd.write(r);
    delay(250);
  }
}

void loop(){
  int Xposi=analogRead(Xinp);
  int Yposi=analogRead(Yinp);
  int buttonstate=digitalRead(buttonPin);
  Serial.println(buttonstate);

  if(Yposi<200){
    Serial.println("up");
    _current_menu++;
    if(_current_menu==3){
      _current_menu=0;
    }    
  }
  else if(Yposi>900){
    Serial.println("down");
    _current_menu--;
    if(_current_menu==-1){
      _current_menu=2;
    }    
  }
  Lcd.clear();
  Lcd.setCursor(1, 1);
  Lcd.print(menui[_current_menu]);
  mi();

  
  if(buttonstate==0){
    switch(_current_menu){
      case 0:
        Heart();
        Lcd.clear();
        break;
      case 1:
        ProgressBar();
        Lcd.clear();
        break;
      case 2:
        Dht();
        Lcd.clear();
        break;
    }
  }

}