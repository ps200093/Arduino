#include <Keypad.h>

const int ROWS = 4;  // 가로 개수
const int COLS = 3;  // 세로 개수
byte pinRows[ROWS] = { 9, 8, 7, 6 };  // 4x4 핀
byte pinCols[COLS] = { 5, 4, 3 };  //디지털 핀 모자랄 경우 아날로그 핀으로 대체
char keyMap[ROWS][COLS] = {
		{'1','2','3'},
		{'4','5','6'},
		{'7','8','9'},
		{'*','0','#'}};	//	초기화에 사용하는 keyMap 배열

Keypad keypad = Keypad(makeKeymap(keyMap), pinRows, pinCols, ROWS, COLS);
char currentKey = keypad.getKey();

void CheckPressedKeypad()
{
	char key = keypad.getKey();
	String password = "";

	if (key)
	{
		push_Bt();
		if (key == '*' && !isDoorOpen)	//	문이 닫힌 상태에서 비밀번호를 입력하면?
		{
			while (true)	//	사용자로부터 비밀번호 입력이 종료될 때까지 무한루프
			{
				key = keypad.getKey();

				if (key >= '0' && key <= '9')	//	입력은 숫자만 처리
				{
					password = password + key;
				}

				else if (key == '#')	//	사용자가 '#' 을 눌러 비밀번호 입력을 종료함
				{
					//	설정해놓은 비밀번호와 일치하는지 비교하는 부분
					ComparePassword(password);
					break;
				}
			}
		}

		else if ((key == '*' || key == '#') && isDoorOpen)	//	문이 열린 상태에서 '*' or '#' 을 5번 연속으로 누르면 비밀번호 or 태그 저장
		{
			int pressCnt = 1;
			char baseKey = key;

			while (true)
			{
				key = keypad.getKey();

				if (key)
				{
					if (baseKey == key)
					{
						pressCnt += 1;

						if (pressCnt >= 5)	//	5번 이상 눌렀을 때
						{
							if (baseKey == '*')		//	기준 키가 '*' 이면 ROM에 비밀번호 저장
							{
								SavePassword();
								break;
							}

							else if (baseKey == '#')	//	기준 키가 '#' 이면 ROM에 태그 저장
							{
								SaveTagId();
								break;
							}
						}
					}

					else	//	중간에 다른 문자를 누른 경우 비밀번호 설정 취소
					{
						fail_Lock();
						break;
					}
				}
			}
		}
	}
}
