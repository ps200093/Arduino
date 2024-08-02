
void setup() {
    // put your setup code here, to run once:
    Serial.begin(9600);
    InitMotor();
    LcdInit();
    RFIDInit();
    CloseDoor();
    //  if (!ReadPassword())
    //  {
	  //        Serial.println("초기 비밀번호 설정 실패");
    //  }
    //  if (!ReadTagId())
    //  {
    //        Serial.println("초기 태그 설정 실패");
    //  }
}

void loop() {
    CheckTagId();
    CheckPressedKeypad();

    if (getDoorState()) {
        DoorLockSwitch();
    }
}

