#pragma once
#include <Adafruit_SSD1306.h>
#include "Music.h"



extern bool inGame;   // legătură cu variabila globală din main.ino
extern int jocCurent; 

// Inițializare joc
void meniu(Adafruit_SSD1306 &display);
