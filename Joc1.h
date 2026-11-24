#pragma once
#include <Adafruit_SSD1306.h>
#include "Character.h"
#include "enemy.h"
#include "Music.h"



extern bool inGame;   // legătură cu variabila globală din main.ino
extern int jocCurent; 

// Inițializare joc
void setupJoc1(Adafruit_SSD1306 &display);

// Loop joc
void loopJoc1(Adafruit_SSD1306 &display);