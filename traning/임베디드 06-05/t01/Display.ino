#include "Romvalue.h"

void TimeDisplay(){
  if(GetTimeDate()){
    lcd.setCursor(0, 0);
    lcd.print(AmToPm(hour));

    lcd.setCursor(1, 0);
    if(hour%12==0){
      lcd.print(12);      
    }
    else  LowThenTen(hour%12);
    //LowThenTen(hour%12);//lcd.print(hour);

    lcd.setCursor(3, 0);
    lcd.print(":  :  [  /  ]");

    lcd.setCursor(4, 0);
    LowThenTen(min);//lcd.print(min);

    lcd.setCursor(7, 0);
    LowThenTen(sec);//lcd.print(sec);

    lcd.setCursor(10, 0);
    LowThenTen(month);//lcd.print(month);

    lcd.setCursor(13, 0);
    LowThenTen(day);//lcd.print(day);
  }
}

void Read_setValue(){
  EEPROM_Read();

  lcd.setCursor(0, 1);
  lcd.print("Alarm");
  lcd.setCursor(6, 1);
  lcd.print(AmToPm(alarm_hour));
  lcd.setCursor(8, 1);
  lcd.print(alarm_hour%12);
  lcd.setCursor(10, 1);
  lcd.print(":");
  lcd.setCursor(11, 1);
  lcd.print(alarm_min);
}

String AmToPm(int hour){
  if(hour>=12){
    return "P";    
  }
  else return "A";  
}

void LowThenTen(int time){
  if(time<10){
    lcd.print("0");
    lcd.print(time%10);    
  }
  else{
    lcd.print(time);
  }
}

int CursorMove(int current){
  int xAxis = analogRead(xAxis_pin);

    if(xAxis >= 0 && xAxis <= 300){
      current--;
    }
    if(xAxis >= 800 && xAxis <= 1023){
      current++;
    }
    return current;    
}


bool GetTimeDate(){
  Serial.println(rtc.getDateStr());
  Serial.println(rtc.getTimeStr());

  String date = rtc.getDateStr();
  int div_1=date.indexOf(".");
  int div_2=date.indexOf(".",div_1 + 1);
  String _year = date.substring(0, div_1);
  String _month = date.substring(div_1 + 1, div_2);
  String _day = date.substring(div_2 + 1, date.length());
  year = _year.toInt();
  month = _month.toInt();
  day = _day.toInt();

  String time = rtc.getTimeStr();
  div_1 = time.indexOf(":");
  div_2 = time.indexOf(":",div_1 + 1);
  String _hour = time.substring(0, div_1);
  String _min = time.substring(div_1 + 1, div_2);
  String _sec = time.substring(div_2 + 1, time.length());
  hour = _hour.toInt();
  min = _min.toInt();
  sec = _sec.toInt();
  
  return true;
}

void Loading(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write(5);
  lcd.setCursor(1, 0);
  lcd.write(6);
  lcd.setCursor(2, 0);
  lcd.print("Alarm Loading...");

  for(int i = 0; i < 16; i++){
    for(int j = 0; j < 5; j++){
      lcd.setCursor(i, 1);
      lcd.write(j);
      delay(50);
    }
  }
  lcd.clear();
}