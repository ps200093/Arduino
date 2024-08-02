int _alarm_location[5] = {2, 5, 6, 8, 9};
int _month_digit1, _month_digit2;
int _day_digit1, _day_digit2;
int _hour_digit1, _hour_digit2;
int _min_digit1, _min_digit2;

void AlarmSetting(){
  Serial.println("AlarmSetting");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write((byte)5);
  lcd.setCursor(2, 0);
  lcd.print("Alarm Setting");
  lcd.setCursor(2, 1);
  lcd.print(AmToPm(alarm_hour));
  lcd.setCursor(3, 1);
  lcd.print("M"); 
  lcd.setCursor(5, 1);
  lcd.print(alarm_hour%12);
  lcd.setCursor(7, 1);
  lcd.print(":"); 
  lcd.setCursor(8, 1);
  lcd.print(alarm_min); 

  int current_cursor = 0;

  if(alarm_hour > 12){
    ampm = "P";
    _hour_digit1 = 0;
    _hour_digit2 = alarm_hour - 12;
  }
  else{
    ampm = "A";
    _hour_digit1 = 1;
    _hour_digit2 = alarm_hour;
  }

  _min_digit1 = alarm_min / 10;
  _min_digit2 = alarm_min % 10;

  while(1){
    lcd.setCursor(_alarm_location[current_cursor], 1);
    lcd.cursor();
    delay(250);

    current_cursor = CursorMove(current_cursor);
    if(current_cursor == -1)  current_cursor = 4;
    if(current_cursor == 5)  current_cursor = 0;
    if(AlarmSetValue(current_cursor)) break;

    int pushBtn = digitalRead(btn_pin);
    if(pushBtn == LOW){
      AlarmSave();
      break;
    }

    lcd.noCursor();
    delay(250);
  }

  MenuDisplay();  
}

void AlarmSave(){
  int save_hour = (_hour_digit1 * 10) + _hour_digit2;
  int save_min = (_min_digit1 * 10) + _min_digit2;
  
  if(ampm.equals("P")) save_hour = save_hour + 12;
  if(ampm.equals("A") && save_hour == 12) save_hour = 0;
  EEPROM_Save(save_hour, save_min);

  lcd.noCursor();
  lcd.setCursor(12, 1);
  lcd.print("SAVE");
  delay(3000);

  alarm_hour = save_hour;
  alarm_min = save_min;
}

bool AlarmSetValue(int cursor){
  int yAxis = analogRead(yAxis_pin);

  if(yAxis >= 0 && yAxis <= 300){
    switch(cursor){
      case 0:
        Set0();
        break;
      case 1:
        Set1();
        break;
      case 2:
        Set2("+");
        break;
      case 3:
        Set3("+");
        break;
      case 4:
        Set4("+");
        break;
    }
  }
  if(yAxis >= 800 && yAxis <= 1023){
    switch(cursor){
      case 0:
        Set0();
        break;
      case 1:
        Set1();
        break;
      case 2:
        Set2("-");
        break;
      case 3:
        Set3("-");
        break;
      case 4:
        Set4("-");
        break;
    }
  }
}

void Set0(){
  lcd.setCursor(2, 1);
  if(ampm.equals("A")){
    lcd.print("P");
    ampm="P";
  }
  else{
    lcd.print("A");
    ampm = "A";
  }
}

void Set1(){
  lcd.setCursor(5, 1);
  if(_hour_digit1 == 0){
    lcd.print("1");
    _hour_digit1 = 1;

    if(_hour_digit2 > 2){
      lcd.setCursor(6, 1);
      _hour_digit2 = 0;
      lcd.print(_hour_digit2);
    }
  }
  else{
    lcd.print("0");
    _hour_digit1 = 0;
  }
}

void Set2(String flag){
  if(flag.equals("+")){
    _hour_digit2++;
    if(_hour_digit1 == 1 && _hour_digit2 > 2) _hour_digit2 = 0;
    if(_hour_digit1 == 0 && _hour_digit2 > 9) _hour_digit2 = 0;
  }
  else{
    _hour_digit2--;
    if(_hour_digit1 == 1 && _hour_digit2 < 0) _hour_digit2 = 0;
    if(_hour_digit2 == 0 && _hour_digit2 < 1) _hour_digit2 = 1;
  }
  lcd.setCursor(6, 1);
  lcd.print(_hour_digit2);  
}

void Set3(String flag){
  if(flag.equals("+")){
    _min_digit1++;
    if(_min_digit1 > 5) _min_digit1 = 0;
  }
  else{
    _min_digit1--;
    if(_min_digit1 < 0) _min_digit1 = 0;
  }
  lcd.setCursor(8, 1);
  lcd.print(_min_digit1);  

}
void Set4(String flag){
  if(flag.equals("-")){
    _min_digit2++;
    if(_min_digit2 > 9 ) _min_digit2 = 0;
  }
  else{
    _min_digit2--;
    if(_min_digit2 < 0) _min_digit2 = 9;
  }
  lcd.setCursor(9, 1);
  lcd.print(_min_digit2);  
}

