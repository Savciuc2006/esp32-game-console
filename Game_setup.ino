#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//#include <SD.h>
//#include <SPI.h>

#include "Joc1.h"
#include "Joc2.h"
#include "joc3.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//#define SD_CS 9  // pinul CS 

// butoane arduino uno
/*#define BTN_UP     6
#define BTN_DOWN   5
#define BTN_SELECT 4
#define meniu 7*/

//esp32 c3
#define BTN_UP     6
#define BTN_DOWN   7
#define BTN_SELECT 9
#define meniu 20



int cursor = 0;       // ce opțiune e selectată
int numarJocuri = 3;  // câte jocuri ai
 bool inGame = false;
int jocCurent = -1;   // -1 = meniu, altfel = joc selectat

void setup() {
  Serial.begin(9600);
  Wire.begin(5, 4);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(meniu, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(BTN_SELECT, INPUT_PULLUP);
 if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("Eroare OLED"));
    while (true);
  }

/*if (!SD.begin(SD_CS)) {
    Serial.println("Eroare la initializarea SD-ului!");
    while(true);
  }
  Serial.println("SD initializat cu succes!");*/


  
   display.clearDisplay();
  display.display();

setupJoc1(display);

  
}

void loop() {



     
  if (!inGame) {
    // === Meniu principal ===
    if (digitalRead(BTN_UP) == LOW) {
      cursor--;
      if (cursor < 0) cursor = numarJocuri - 1;
      delay(200);
    }
    if (digitalRead(BTN_DOWN) == LOW) {
      cursor++;
      if (cursor >= numarJocuri) cursor = 0;
      delay(200);
    }
    if (digitalRead(BTN_SELECT) == LOW) {
      inGame = true;
      jocCurent = cursor;
      delay(200);
    }

    // afișează meniul
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 5);
    display.println("Selecteaza jocul:");
    display.setCursor(20, 25);
    display.println(cursor == 0 ? "> Joc1" : "  Joc1");
    display.setCursor(20, 35);
    display.println(cursor == 1 ? "> Joc2" : "  Joc2");
    display.setCursor(20, 45);
    display.println(cursor == 2 ? "> Joc3" : "  Joc3");
    display.display();
  } else {
    // === Ruleaza jocul selectat ===
    switch (jocCurent) {
      case 0: loopJoc1(display); break;
      case 1: loopJoc2(display); break;
      //case 2: loopJoc3(display); break;
      
    }
  }
}