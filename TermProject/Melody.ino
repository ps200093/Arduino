#include "pitches.h"
#define piezoPin  A2

void push_Bt() {//버튼 누르는 소리
    tone(piezoPin, NOTE_E6, 50);
}

void open_Lock() { //문 열리는 소리
    int note[] = { NOTE_C6, NOTE_E5, NOTE_G5,NOTE_C6 };
    int melody[] = { 100, 35, 45, 100 };
    for (int i = 0; i < 4; i++) {
        tone(piezoPin, note[i], melody[i]);
        delay(melody[i] * 5);
    }
}

void close_Lock() { //문 닫히는 소리
    int note[] = { NOTE_C6, NOTE_C6, NOTE_G5, NOTE_E5 };
    int melody[] = { 100, 30, 40, 100 };
    for (int i = 0; i < 4; i++) {
        tone(piezoPin, note[i], melody[i]);
        delay(melody[i] * 5);
    }
}

void fail_Lock() { // 틀렸을 때 소리
    tone(piezoPin, NOTE_FS6, 60);
    delay(150);
    tone(piezoPin, NOTE_FS6, 60);
}

void lockDown() {  // 사이렌 소리
    for (int t = 0; t < 10; t++) {
        for (int i = 610; i < 690; i = i + 10) {
            tone(piezoPin, i, 50);
            delay(60);
        }
        for (int j = 690; j > 610; j = j - 10) {
            tone(piezoPin, j, 50);
            delay(60);
        }
    }
    //  delay(30000);
}

void regLock() { //등록할 때 소리
    int note[] = { NOTE_E5, NOTE_B6, NOTE_G5, NOTE_E5 };
    int melody[] = { 60, 40, 30, 100 };
    for (int i = 0; i < 4; i++) {
        tone(piezoPin, note[i], melody[i]);
        delay(melody[i] * 5);
    }
}


