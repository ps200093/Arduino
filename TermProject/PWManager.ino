#include <EEPROM.h>
#include "ROM_ADDRESS.h"

const int MAX_PASSWORD_LENGTH = 8;	//	설정할 수 있는 비밀번호의 최대 길이
String userPassword = "0000";	//	사용자가 설정한 비밀번호

void ComparePassword(String inputPassword)
{
	if (userPassword == inputPassword)  //  비밀번호가 같은지 비교
	{
		OpenDoor();   //  문 열림
	}

	else
	{
		//	비밀번호 틀렸으니 부저로 소리내는 것을 작성하는 부분
		CloseDoor();
	}

}

void SavePassword()
{
	char key;
	String password = "";
	ChangeLcdDisplay(1, 0);

	while (true)	//	사용자로부터 비밀번호 입력이 종료될 때까지 무한루프
	{
		key = keypad.getKey();
		if (key) {
			push_Bt();
			if (key >= '0' && key <= '9')	//	입력은 숫자만 처리
			{
				password = password + key;
			}

			else if (key == '#')	//	사용자가 '#' 을 눌러 비밀번호 입력을 종료함
			{
				userPassword = password;
				break;
			}
		}
	}

	ChangeLcdDisplay(1, 1);
	EEPROM.put(USER_PASSWORD_ADDRESS, userPassword);
	regLock();
	delay(3000);	//	비밀번호 저장 후 3초간 대기
	ChangeLcdDisplay(0, 0);
}

bool ReadPassword() //  ROM에서 저장된 비밀번호를 가져오는 함수
{
	EEPROM.get(USER_PASSWORD_ADDRESS, userPassword);

	if (userPassword == "")
		return false;
  
	return true;
}
