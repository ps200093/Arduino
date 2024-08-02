#include <Servo.h>
#define OPEN_DOOR_DEGREE 0 //  도어락 열렸을 때 각도 값
#define CLOSE_DOOR_DEGREE 90 //  도어락 닫힌 상태 각도 값
#define ps_bt A1  //도어락 센서 저항은 꼭 GND에 연결

const int servoPin = A0;	//	pin 정의
bool isDoorOpen = false;	//	문 열림 여부
Servo motor;	//	모터 객체

void InitMotor()
{
  motor.attach(servoPin);
  pinMode(ps_bt, INPUT);
}

bool getDoorState()	//	문이 열려있으면 참을 닫힌 상태면 거짓 반환
{
  if (isDoorOpen)
    return true;
  else
    return false;
}

void OpenDoor()  //  doorlock 열림
{
    open_Lock();
    motor.write(OPEN_DOOR_DEGREE);
    isDoorOpen = true;
    ChangeLcdDisplay(0, 0);
}

void CloseDoor() //  doorlock 닫힘
{
    close_Lock();
    motor.write(CLOSE_DOOR_DEGREE);
    isDoorOpen = false;
    ChangeLcdDisplay(0, 1);
}

void DoorLockSwitch() {
    if (digitalRead(ps_bt) == LOW)  //상승 엣지 검출(먼저 초기에 LOW레벨 여부 확인, 버튼 누르기 전)
    {
        delay(10); //10ms 딜레이
        if (digitalRead(ps_bt) == HIGH) //HIGH레벨 여부 확인 (버튼이 눌러진 상태)
        {
            delay(10);  //10ms 딜레이
            while (digitalRead(ps_bt) == HIGH) //버튼이 떨어질 때까지 대기
            {
                delay(1);
            }
            CloseDoor();
        }
    }
}