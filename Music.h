#ifndef MUSIC_H
#define MUSIC_H

#include <Arduino.h>

#define BUZZER_PIN 21 // Poți schimba pinul aici

void startMelody(uint8_t melodyID);
void updateMelody();
void playMoveBeep1();
 void stopMelody();

#endif