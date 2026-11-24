#include "meniu.h"
#include "Music.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

const int Buttons = 6;
const int Buttonj =7;
const int Buttond =9;
const int Buttonst =10;
const int meniuu =20;

int mun=0;



void meniu(Adafruit_SSD1306 &display){
if (digitalRead(Buttons) == LOW) {
      mun--;
      if (mun < 0) mun = 3 - 1;
      delay(200);
    }

if (digitalRead(Buttonj) == LOW) {
      mun++;
      if (mun >= 3) mun = 0;
      delay(200);
    }

   display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 10);
    display.println("Selecteaza jocul:");
    display.setCursor(20, 30);
    display.println(mun == 0 ? "> Resume" : "  Resume");
    display.setCursor(20, 40);
    display.println(mun == 1 ? "> Setings" : "  Setings");
    display.setCursor(20, 50);
    display.println(mun == 2 ? "> Quit" : "  Quit");
    display.display();

  if(digitalRead(Buttond) == LOW && mun==2){

  inGame = false;     // ieșim din joc
    jocCurent = -1;     // revenim la meniu
    
    stopMelody();       // (opțional) oprim muzica dacă vrei
    delay(300);         // anti-bouncing pentru buton
    return;   


  }




}