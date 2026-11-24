#ifndef CHARACTER_H
#define CHARACTER_H

#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class Character {
  public:
 // byte character_bitmap[8];
    Character(int startX, int startY);
    //void loadFromSD(const char* filename);
    void move(int dx, int dy, int screenWidth, int screenHeight);
    void draw(Adafruit_SSD1306 &display);

  public:
    int x, y;
};

#endif