#include "Joc1.h"
#include <Arduino.h>

//arduino uno
/*#define JOY_X A0
#define JOY_Y A1*/

//esp32 c3
#define JOY_X 2
#define JOY_Y 3

#define JOY_DEADZONE1 3500

#define JOY_DEADZONE  700



/* arduino uno
const int Buttons = 6;
const int Buttonj =5;
const int Buttond =3;
const int Buttonst =4;
const int meniuu =7;*/


//esp32 c3
const int Buttons = 6;
const int Buttonj =7;
const int Buttond =9;
const int Buttonst =10;
const int meniuu =20;
//3
int randx;
int randy;
int healthx=40;

// Character

 enemy myenemy[3]{

    enemy(20,0),
    enemy(60,0),
    enemy(100,0),
 };
Character myChar(60, 28);

void setupJoc1(Adafruit_SSD1306 &display) {
    pinMode(Buttonj, INPUT_PULLUP);
    pinMode(Buttons, INPUT_PULLUP);
    pinMode(Buttond, INPUT_PULLUP);
    pinMode(Buttonst, INPUT_PULLUP);
    pinMode(meniuu, INPUT_PULLUP);

    pinMode(JOY_X, INPUT);
    pinMode(JOY_Y, INPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while(true);
    }

    display.clearDisplay();
    display.display();
    startMelody(1);
      //myChar.loadFromSD("character.txt");
}

void loopJoc1(Adafruit_SSD1306 &display) {
  

    updateMelody(); 
    display.fillRect(0, 0, healthx,10 , WHITE);
    int xVal = analogRead(JOY_X);
    int yVal = analogRead(JOY_Y);

    int dx = 0, dy = 0;
    int ex=0, ey=0;

     ey=2;
    if (xVal < 512 - 300 || digitalRead(Buttonst) == LOW){ dx = 2; playMoveBeep1();}
    else if (xVal > 512 + 3500|| digitalRead(Buttond) == LOW){ dx = -2; playMoveBeep1();}

    if (yVal < 512 - 300 || digitalRead(Buttonj) == LOW){ dy = -2; playMoveBeep1();}
    else if (yVal > 512 + 3000 || digitalRead(Buttons) == LOW) {dy = 2; playMoveBeep1();}

    myChar.move(dx, dy, 128, 64);

    myenemy[0].move(0,ey,140,70);
    myenemy[1].move(0,ey,140,70);
    myenemy[2].move(0,ey,140,70);


    display.clearDisplay();

    myChar.draw(display);
    myenemy[0].draw(display);
    myenemy[1].draw(display);
    myenemy[2].draw(display);
       display.fillRect(0, 0, healthx,10 , WHITE);
   
    display.display();
    

if (digitalRead(meniuu) == LOW) {
    inGame = false;     // ieșim din joc
    jocCurent = -1;     // revenim la meniu
    
    stopMelody();       // (opțional) oprim muzica dacă vrei
    delay(300);         // anti-bouncing pentru buton
    return;             // ieșim imediat din funcția jocului
}


    delay(50);
}