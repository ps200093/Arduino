#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void LcdInit()	//	Lcd 초기화
{
	lcd.init();
	lcd.backlight();
	lcd.clear();
}

void ChangeLcdDisplay(int screenType, int lcdState) //  lcd 화면을 바꾸고 싶을 때 사용하는 함수
{
	switch (screenType)
	{
	case 0:	//	main 화면
		LcdMainDisplay(lcdState);
		break;
	case 1:	//	password 저장 화면
		LcdSavePasswordDisplay(lcdState);
		break;
	case 2:	//	tag 저장 화면
		LcdSaveTagDisplay(lcdState);
		break;
	}
}

void LcdMainDisplay(int dispType)	//	main 화면, 열린 경우 출력문 -> 0, 닫힌 경우 -> 0
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Smart Door Lock");
	lcd.setCursor(0, 1);

	switch (dispType)
	{
	case 0:
		lcd.print("- Door Open - ");
		break;
	case 1:
		lcd.print("- Door Locked - ");
		break;
	case 2:
		lcd.print("Unauthorized tag");
		break;
	}
}

void LcdSavePasswordDisplay(int dispType)	//	비밀번호 저장 화면, 비밀번호 입력 출력문 -> 0, 저장 완료 출력문 -> 1
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("Password Setting");
	lcd.setCursor(0, 1);
	
	switch (dispType)
	{
	case 0:
		lcd.print("STEP.1:InputPW");
		break;
	case 1:
		lcd.print("STEP.2:SAVE OK");
		break;
	}

}

void LcdSaveTagDisplay(int dispType)	//	태그 저장 화면, 태그 입력 출력문 -> 0, 저장 완료 출력문 -> 1
{
	lcd.clear();
	lcd.setCursor(0, 0);
	lcd.print("TAG Register");
	lcd.setCursor(0, 1);

	switch (dispType)
	{
	case 0:
		lcd.print("STEP.1:Tagging");
		break;
	case 1:
		lcd.print("STEP.2:SAVE OK");
		break;
	}
}