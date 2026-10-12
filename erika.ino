// Erika: approximate three-voice arrangement for Arduino Nano.
// Passive buzzers: signal D8 (melody), D9 (bass), D10 (harmony).
// All grounds connected to GND. 3-pin modules: VCC to 5V.
// Software square-wave generation: independent pitches without tone().
// NOTE: the melody is approximate, not an exact transcription.

#include "pitches.h"

const byte pins[3] = {8, 9, 10};
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

const byte durations[] = {
  8, 4, 8, 8, 8, 4, 8, 4, 8, 8, 2, 4,
  8, 4, 8, 8, 8, 4, 8, 4, 8, 8, 2, 4,
  8, 8, 8, 8, 8, 8, 4, 8, 8, 8, 2, 4,
  8, 8, 8, 8, 8, 8, 8, 8, 2
};

// Simple bass and harmony derived from the melody, not an original score.
void playChord(int lead, unsigned long lengthMs) {
  int notes[3] = {lead, REST, REST};
  if (lead != REST) {
    // Bass at half the melody frequency, harmony a fifth above.
    notes[1] = lead / 2;
    notes[2] = lead * 3 / 2;
  }

  unsigned long halfPeriod[3];
  unsigned long nextToggle[3];
  bool state[3] = {false, false, false};
  unsigned long start = micros();
  unsigned long endAt = start + lengthMs * 900UL; // 90% articulation

  for (byte i = 0; i < 3; i++) {
    halfPeriod[i] = notes[i] > 0 ? 500000UL / notes[i] : 0;
    nextToggle[i] = start;
    digitalWrite(pins[i], LOW);
  }

  while ((long)(micros() - endAt) < 0) {
    unsigned long now = micros();
    for (byte i = 0; i < 3; i++) {
      if (halfPeriod[i] && (long)(now - nextToggle[i]) >= 0) {
        state[i] = !state[i];
        digitalWrite(pins[i], state[i] ? HIGH : LOW);
        nextToggle[i] += halfPeriod[i];
      }
    }
  }

  for (byte i = 0; i < 3; i++) digitalWrite(pins[i], LOW);
  delay(lengthMs / 10);
}

void setup() {
  for (byte i = 0; i < 3; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
}

void loop() {
  const int count = sizeof(melody) / sizeof(melody[0]);
  const unsigned long wholeNote = 240000UL / tempo;
  for (int i = 0; i < count; i++) {
    playChord(melody[i], wholeNote / durations[i]);
  }
  delay(3000);
}
