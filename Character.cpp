#include "Character.h"
//#include <SD.h>
//#include <SPI.h>
// Un mic sprite 8x8 (bitmap) – exemplu simplu
const unsigned char character_bitmap [] PROGMEM = {
  0b00111100,
  0b01111110,
  0b11111111,
  0b11011011,
  0b11111111,
  0b01111110,
  0b01000010,
  0b10000001
};

Character::Character(int startX, int startY) {
  x = startX;
  y = startY;
}


/*void Character::loadFromSD(const char* filename) {
    File f = SD.open(filename);
    if (f) {
        int i = 0;
        while(f.available() && i < 8) {
            String line = f.readStringUntil('\n');
            line.trim();
            character_bitmap[i] = (byte) strtol(line.c_str(), NULL, 2); // convertim binar -> byte
            i++;
        }
        f.close();
        Serial.print("Sprite incarcat din: ");
        Serial.println(filename);
    } else {
        Serial.print("Fisier sprite nu exista: ");
        Serial.println(filename);
    }
}*/

void Character::move(int dx, int dy, int screenWidth, int screenHeight) {
  x += dx;
  y += dy;

  // Limitează mișcarea în ecran
  if (x < 0) x = 0;
  if (y < 0) y = 0;
  if (x > screenWidth - 8) x = screenWidth - 8;
  if (y > screenHeight - 8) y = screenHeight - 8;
}

void Character::draw(Adafruit_SSD1306 &display) {
  display.drawBitmap(x, y, character_bitmap, 8, 8, WHITE);
}