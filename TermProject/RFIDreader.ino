#include <SPI.h>
#include <MFRC522.h>
#include <EEPROM.h>
#include "ROM_ADDRESS.h"

#define SS_PIN 12
#define RST_PIN 11
#define MAX_SAVE_TAG_COUNT 3     //  최대 저장할 수 있는 TAG 개수 3개로 제한
#define TAG_LENGTH 4    //  태그 ID 리스트의 최대 길이

class TagID
{
private:
    byte id[4];

public:
    //TagID() { id = nullptr; }

public:
    //  타겟 id와 비교했을 때 동일한 태그면 1, 아니면 0 반환
    bool CompareToTagId(byte *target)
    {
        if (id[0] != target[0] || id[1] != target[1] ||
            id[2] != target[2] || id[3] != target[3])
        {
            return true;
        }

        else
        {
            return false;
        }
    }

    void setId(byte *id, int len)
    {
        for (int i = 0; i < len; i++)
        {
            this->id[i] = id[i];
        }
    }
    
    byte* getId()
    {
        return id;
    }
};

TagID tag;  //  ROM에 읽은 태그 값을 저장할 객체

MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class
MFRC522::MIFARE_Key MFkey; 
byte readId[TAG_LENGTH];

void RFIDInit() {
    SPI.begin();
    rfid.PCD_Init();
}

bool isSavedTag()   //  저장된 태그 id면 1, 없는 태그면 0 반환
{
    if (tag.CompareToTagId(readId))
        return true;

    return false;
}

void CheckTagId()   //  아두이노 main루프에서 돌릴 tagging 확인용 함수
{
    //  새 카드 접촉이 있을 때만 넘어감
    if (!rfid.PICC_IsNewCardPresent())
        return;
    //  카드 읽힘이 제대로 됐으면 넘어감
    if (!rfid.PICC_ReadCardSerial())
        return;
    if (isDoorOpen) //  문이 열린 상태면 태그 체크 X
        return;

    MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);  //카드 태그
    push_Bt();  //  버튼 누르는 소리

    if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
        piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
        piccType != MFRC522::PICC_TYPE_MIFARE_4K &&
        piccType != MFRC522::PICC_TYPE_ISO_14443_4)
    {
        //  지원하지 않는 태그일 때 처리 부분
        return;
    }

    else
    {
        if (rfid.uid.uidByte[0] != readId[0] ||
            rfid.uid.uidByte[1] != readId[1] ||
            rfid.uid.uidByte[2] != readId[2] ||
            rfid.uid.uidByte[3] != readId[3])
        {
            //  이전에 인식한 카드와 다른 카드가 인식됨
            for (byte i = 0; i < TAG_LENGTH; i++)
            {
                readId[i] = rfid.uid.uidByte[i];
            }

            //  여기에 ROM에 저장된 태그와 위에 readId와 비교
            if (isSavedTag())
            {
                OpenDoor();
                return;
            }

            else
            {
                ChangeLcdDisplay(0, 2); //  미등록 카드 화면 출력
                lockDown(); //  틀렸을 때 사이렌 소리 남, 약 10초..?
                delay(3000);    //  3초간 대기
                ChangeLcdDisplay(0, 1); //  문 닫힘 화면으로 돌아감
                return;
            }
        }

        else
        {
            //  이미 인식한 카드인 경우 처리
            rfid.PICC_HaltA();
            rfid.PCD_StopCrypto1();
            return;
        }
    }
}

void SaveTagId()
{
    ChangeLcdDisplay(2, 0); //  lcd화면 태깅 화면으로 바꿈

    while (true)
    {
        //  새 카드 접촉이 있을 때만 넘어감
        if (!rfid.PICC_IsNewCardPresent())
            continue;
        //  카드 읽힘이 제대로 됐으면 넘어감
        if (!rfid.PICC_ReadCardSerial())
            continue;

        MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);  //카드 태그
        push_Bt();  //  버튼 누르는 소리

        if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&
            piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
            piccType != MFRC522::PICC_TYPE_MIFARE_4K &&
            piccType != MFRC522::PICC_TYPE_ISO_14443_4)
        {
            //  지원하지 않는 태그일 때 처리 부분
            continue;
        }

        else
        {
            //  지원하는 태그라면 readId 배열에 id값 저장 후 무한 루프 탈출
            for (byte i = 0; i < TAG_LENGTH; i++)
                readId[i] = rfid.uid.uidByte[i];
            break;
        }
    }

    ChangeLcdDisplay(2, 1); //  저장 완료 화면 출력
    tag.setId(readId, TAG_LENGTH);   //  tag 객체에 읽은 태그 값 저장
    EEPROM.put(USER_RFIDCARD__ADDRESS, tag);   //  ROM에 현재 읽은 태그 객체 저장
    regLock();  //  등록할 때 소리 출력
    delay(3000);	//	비밀번호 저장 후 3초간 대기
    ChangeLcdDisplay(0, 0); //  초기 화면으로 돌아감
}

bool ReadTagId()
{
    EEPROM.get(USER_RFIDCARD__ADDRESS, tag);

    return true;
}