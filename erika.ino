// Simplified instrumental approximation of "Erika".
// Arduino Nano: buzzer signal D8, VCC 5V, GND GND.
// A passive buzzer is recommended for changing pitch.
#include "pitches.h"

#define BUZZER_PIN 8
const int tempo = 115;

const int melody[] = {
  NOTE_G4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_B4, NOTE_A4, NOTE_G4, REST,

  NOTE_G4, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5,
  NOTE_D5, NOTE_B4, NOTE_C5, REST,

  NOTE_E5, NOTE_E5, NOTE_E5,
  NOTE_D5, NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_G5, NOTE_F5, NOTE_E5, NOTE_D5, REST,

  NOTE_C5, NOTE_D5, NOTE_E5,
  NOTE_D5, NOTE_C5, NOTE_B4,
  NOTE_A4, NOTE_B4, NOTE_C5
};

const int durations[] = {
  8, 4, 8, 8,
  8, 4, 8, 4,
  8, 8, 2, 4,

  8, 4, 8, 8,
  8, 4, 8, 4,
  8, 8, 2, 4,

  8, 8, 8,
  8, 8, 8, 4,
  8, 8, 8, 2, 4,

  8, 8, 8,
  8, 8, 8,
  8, 8, 2
};

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  const int noteCount = sizeof(melody) / sizeof(melody[0]);
  const long wholeNote = 240000L / tempo;

  for (int i = 0; i < noteCount; i++) {
    const int duration = wholeNote / durations[i];
    if (melody[i] != REST) {
      tone(BUZZER_PIN, melody[i], duration * 9 / 10);
    }
    delay(duration);
    noTone(BUZZER_PIN);
  }
  delay(3000);
}
