#include "joc3.h"
#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

// Joystick ESP32-C3
#define JOY_X 2
#define JOY_Y 3
#define JOY_DEADZONE 700

// Butoane
const int ButtonUp    = 6;
const int ButtonDown  = 7;
const int ButtonLeft  = 9;
const int ButtonRight = 10;
const int meniuu      = 20;

// Buzzer
#define BUZZER_PIN 5

// Structura gloanțe
struct Bullet {
  int x, y, dx, dy;
  bool active;
};

// Maximum obiecte pe ecran
#define MAX_BULLETS 5
#define MAX_ENEMIES 6

// Variabile globale
int healthx1 = 40;
int score1   = 0;
int level1   = 1;

Character myChar1(60, 50);
enemy myenemy1[MAX_ENEMIES] = {
  enemy(20,0),
  enemy(60,0),
  enemy(100,0),
  enemy(40,-20),
  enemy(80,-40),
  enemy(120,-60)
};
int enemyCount = 1; // doar 1 inamic la start
Bullet bullets[MAX_BULLETS];

// ---- Sunete ----
void soundShoot() { tone(BUZZER_PIN, 1000, 80); }
void soundHit()   { tone(BUZZER_PIN, 300, 100); }
void soundKill()  { tone(BUZZER_PIN, 800, 150); }
void soundLevel() { tone(BUZZER_PIN, 1500, 200); }

// ---- Setup Joc ----
void setupJoc3(Adafruit_SSD1306 &display) {
  pinMode(ButtonUp, INPUT_PULLUP);
  pinMode(ButtonDown, INPUT_PULLUP);
  pinMode(ButtonLeft, INPUT_PULLUP);
  pinMode(ButtonRight, INPUT_PULLUP);
  pinMode(meniuu, INPUT_PULLUP);

  pinMode(JOY_X, INPUT);
  pinMode(JOY_Y, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) while (true);

  display.clearDisplay();
  display.display();

  for (int i=0;i<MAX_BULLETS;i++) bullets[i].active=false;
  startMelody(1);
}

// ---- Creează glonț ----
void shootBullet(int dx,int dy){
  for(int i=0;i<MAX_BULLETS;i++){
    if(!bullets[i].active){
      bullets[i].x=myChar1.x;
      bullets[i].y=myChar1.y;
      bullets[i].dx=dx;
      bullets[i].dy=dy;
      bullets[i].active=true;
      soundShoot();
      break;
    }
  }
}

// ---- Loop Joc ----
void loopJoc3(Adafruit_SSD1306 &display){
  static unsigned long lastUpdate = 0;
  if(millis() - lastUpdate < 50) return;
  lastUpdate = millis();

  updateMelody();
  int dx=0,dy=0;

  // Butoane mișcare
  if(digitalRead(ButtonLeft)==LOW) dx=-2;
  if(digitalRead(ButtonRight)==LOW) dx=2;
  if(digitalRead(ButtonUp)==LOW) dy=-2;
  if(digitalRead(ButtonDown)==LOW) dy=2;

  myChar1.move(dx, dy, 128, 64);

  // Joystick pentru împușcare
  int xVal = analogRead(JOY_X);
  int yVal = analogRead(JOY_Y);

  int bdx=0,bdy=0;
  if(xVal < 2048 - JOY_DEADZONE) bdx=-3;
  else if(xVal > 2048 + JOY_DEADZONE) bdx=3;
  if(yVal < 2048 - JOY_DEADZONE) bdy=-3;
  else if(yVal > 2048 + JOY_DEADZONE) bdy=3;

  if(bdx!=0 || bdy!=0) shootBullet(bdx,bdy);

  // Actualizare gloanțe
  for(int i=0;i<MAX_BULLETS;i++){
    if(bullets[i].active){
      bullets[i].x+=bullets[i].dx;
      bullets[i].y+=bullets[i].dy;
      if(bullets[i].x<0||bullets[i].x>127||bullets[i].y<0||bullets[i].y>63)
        bullets[i].active=false;
    }
  }

  // Inamici
  for(int i=0;i<enemyCount;i++){
    myenemy1[i].move(0,level1,128,64);

    // coliziune cu jucător
    if(abs(myenemy1[i].x-myChar1.x)<5 && abs(myenemy1[i].y-myChar1.y)<5){
      healthx1-=5;
      soundHit();
      myenemy1[i].y=0;
    }

    // coliziune cu gloanțe
    for(int b=0;b<MAX_BULLETS;b++){
      if(bullets[b].active && abs(myenemy1[i].x-bullets[b].x)<5 && abs(myenemy1[i].y-bullets[b].y)<5){
        bullets[b].active=false;
        myenemy1[i].y=0;
        score1++;
        soundKill();

        if(score1%5==0){ // creștere dificultate
          level1++;
          if(enemyCount<MAX_ENEMIES) enemyCount++;
          soundLevel();
        }
      }
    }
  }

  // Desenare
  display.clearDisplay();
  myChar1.draw(display);
  for(int i=0;i<enemyCount;i++) myenemy1[i].draw(display);
  for(int i=0;i<MAX_BULLETS;i++) if(bullets[i].active) display.fillRect(bullets[i].x, bullets[i].y,2,2,WHITE);
  display.fillRect(0,0,healthx1,5,WHITE);
  display.setCursor(90,0);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("S:");
  display.print(score1);
  display.display();

  // Buton ieșire
  if(digitalRead(meniuu)==LOW){
    inGame=false;
    jocCurent=-1;
    stopMelody();
  }

  // Game over
  if(healthx1<=0){
    display.clearDisplay();
    display.setCursor(30,30);
    display.setTextSize(2);
    display.print("GAME OVER");
    display.display();
    delay(2000);
    inGame=false;
    jocCurent=-1;
    stopMelody();
  }
}
