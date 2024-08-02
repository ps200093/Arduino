int _current_menu = 0;
char* _menu_list[] = {"Alarm Setting", "Time Setting", "Exit"};

void SelectBtn(){
  int pushBtn = digitalRead(btn_pin);

  if(pushBtn == LOW && isMenu ==0){
    isMenu = 1;
    MenuDisplay();
  }
}

void MenuDisplay(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(" - MENU - ");
  lcd.setCursor(0, 1);
  lcd.write((byte)5);
  lcd.setCursor(2, 1);
  lcd.print(_menu_list[_current_menu]);
}

void SelectMenu(){
  while(isMenu == 1){
    int yAxis = analogRead(yAxis_pin);

    if(yAxis >= 0 && yAxis <= 300){
      _current_menu++;
      if(_current_menu == 3){
        _current_menu = 0;
      }
      MenuDisplay();
    }
    if(yAxis >= 800 && yAxis <= 1023){
      _current_menu--;
      if(_current_menu == -1){
        _current_menu = 2;
      }
      MenuDisplay();
    }

    delay(250);

    int pushBtn = digitalRead(btn_pin);
    if(pushBtn == LOW){
      switch(_current_menu){
        case 0:
          AlarmSetting();
          break;
        case 1:
          break;
        case 2:
          break;
      }
    }
  }
}
