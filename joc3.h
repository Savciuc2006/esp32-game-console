#pragma once
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>

#include "Character.h"
#include "enemy.h"
#include "Music.h"



extern bool inGame;   // legătură cu variabila globală din main.ino
extern int jocCurent; 

// Inițializare joc


// Loop joc
void loopJoc3(Adafruit_SSD1306 &display);