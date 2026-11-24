#pragma once
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>



extern bool inGame;   // legătură cu variabila globală din main.ino
extern int jocCurent;


void loopJoc2(Adafruit_SSD1306 &display);