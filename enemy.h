
#pragma once
#include <Arduino.h>
#include <Adafruit_SSD1306.h>

class enemy {
  public:
    enemy(int startX, int startY);
    void move(int dx, int dy, int screenWidth, int screenHeight);
    void draw(Adafruit_SSD1306 &display);

  public:
    int x, y;
};

