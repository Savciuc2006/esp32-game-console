#include "Music.h"
#include "pitches.h"

// Melodii
const int melody1[] = { NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4 };
const int duration1[] = { 4, 4, 4, 4 };

const int melody2[] = { NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5 };
const int duration2[] = { 8, 8, 8, 8 };



const int melody3[] = {    NOTE_G4, NOTE_C4, NOTE_DS4
  
  };
const int duration3[] = {   8, 8, 16

};
  





// Listele de melodii
const int* melodies[] = { melody1, melody2,melody3};
const int* durations[] = { duration1, duration2, duration3};
const int melodyLengths[] = {
  sizeof(duration1) / sizeof(int),
  sizeof(duration2) / sizeof(int),
   sizeof(duration3) / sizeof(int)
};

// 🔐 Variabile interne (private pentru acest fișier)
static int currentMelodyID = -1;
static int melodyIndex = 0;
static unsigned long lastNoteTime = 0;
static int currentNoteDuration = 0;
static bool melodyPlaying = false;

void startMelody(uint8_t melodyID) {
  if (melodyID >= sizeof(melodies) / sizeof(melodies[0])) return;

  currentMelodyID = melodyID;
  melodyIndex = 0;
  lastNoteTime = millis();
  currentNoteDuration = 1000 / durations[melodyID][0];
  melodyPlaying = true;
}

void updateMelody() {
  if (!melodyPlaying || currentMelodyID < 0) return;

  unsigned long currentTime = millis();
  if (currentTime - lastNoteTime >= currentNoteDuration * 1.3) {
    if (melodyIndex < melodyLengths[currentMelodyID]) {
      int note = melodies[currentMelodyID][melodyIndex];
      currentNoteDuration = 1000 / durations[currentMelodyID][melodyIndex];

      if (note == 0) noTone(BUZZER_PIN);
      else tone(BUZZER_PIN, note, currentNoteDuration);

      lastNoteTime = currentTime;
      melodyIndex++;
    } else {
      noTone(BUZZER_PIN);
      melodyPlaying = false;
    }
  }
}


void playMoveBeep1(){

 tone(BUZZER_PIN, NOTE_C5, 100);

}
void stopMelody(){

  noTone(BUZZER_PIN);
}


