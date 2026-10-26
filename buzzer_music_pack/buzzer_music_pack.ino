// Arduino Nano music pack for a PASSIVE buzzer
// GND -> GND, VCC -> 5V, I/O -> D6
// Plays three short themes in sequence and repeats.
// Active buzzers only produce fixed-pitch beeps.

#include <Arduino.h>
const byte BUZZER = 6;

struct Note { uint16_t hz; uint16_t ms; };
#define N(hz,ms) {hz,ms}
#define REST(ms) {0,ms}

// Tetris / Korobeiniki (opening)
const Note tetris[] = {
 N(659,250),N(494,125),N(523,125),N(587,250),N(523,125),N(494,125),
 N(440,250),N(440,125),N(523,125),N(659,250),N(587,125),N(523,125),
 N(494,375),N(523,125),N(587,250),N(659,250),N(523,250),N(440,250),
 N(440,250),REST(125)
};

// Pirates of the Caribbean (short motif)
const Note pirates[] = {
 N(440,180),N(523,180),N(587,360),N(587,360),N(587,180),
 N(659,180),N(698,360),N(698,360),N(698,180),
 N(784,180),N(659,360),N(659,360),N(587,180),
 N(523,180),N(523,180),N(587,360),REST(180)
};

// Happy Birthday (traditional)
const Note birthday[] = {
 N(392,180),N(392,180),N(440,360),N(392,360),N(523,360),N(494,720),
 N(392,180),N(392,180),N(440,360),N(392,360),N(587,360),N(523,720),
 N(392,180),N(392,180),N(784,360),N(659,360),N(523,360),N(494,360),N(440,720),
 N(698,180),N(698,180),N(659,360),N(523,360),N(587,360),N(523,720)
};

template <size_t COUNT>
void play(const Note (&song)[COUNT]) {
  for (size_t i = 0; i < COUNT; ++i) {
    if (song[i].hz) tone(BUZZER, song[i].hz, song[i].ms * 9 / 10);
    else noTone(BUZZER);
    delay(song[i].ms);
    noTone(BUZZER);
  }
  delay(1200);
}

void setup() { pinMode(BUZZER, OUTPUT); }

void loop() {
  play(tetris);
  play(pirates);
  play(birthday);
  delay(2000);
}
