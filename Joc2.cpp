#include "Joc2.h"
#include"Music.h"
int mu=0;


/* arduino uno
const int Buttons = 6;
const int Buttonj =5;
const int Buttond =3;
const int Buttonst =4;
const int meniuu =7;
*/
//esp32 c3
const int Buttons = 6;
const int Buttonj =7;
const int Buttond =9;
const int Buttonst =10;
const int meniuu =20;



void loopJoc2(Adafruit_SSD1306 &display) {



if (digitalRead(Buttons) == LOW) {
      mu--;
      if (mu < 0) mu = 3 - 1;
      delay(200);
    }

if (digitalRead(Buttonj) == LOW) {
      mu++;
      if (mu >= 3) mu = 0;
      delay(200);
    }

   display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(10, 10);
    display.println("Selecteaza jocul:");
    display.setCursor(20, 30);
    display.println(mu == 0 ? "> Muzica1" : "  Muzica1");
    display.setCursor(20, 40);
    display.println(mu == 1 ? "> Muzica2" : "  Muzica2");
    display.setCursor(20, 50);
    display.println(mu == 2 ? "> Muzica3" : "  Muzica3");
    display.display();


  display.display();

if(digitalRead(Buttond) == LOW){
startMelody(mu);
   delay(200);  
}
if (digitalRead(meniuu) == LOW) {
    inGame = false;     // ieșim din joc
    jocCurent = -1;     // revenim la meniu
    
    stopMelody();       // (opțional) oprim muzica dacă vrei
    delay(300);         // anti-bouncing pentru buton
    return;             // ieșim imediat din funcția jocului
}


updateMelody();
  delay(100);
}