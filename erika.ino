// Erika - simplified melody for Arduino Nano
// Buzzer: I/O -> D8, VCC -> 5V, GND -> GND
// Requires a passive buzzer for accurate pitches.

#define BUZZER_PIN 8

#define C4 262
#define D4 294
#define E4 330
#define F4 349
#define G4 392
#define A4 440
#define B4 494
#define C5 523
#define D5 587
#define E5 659
#define F5 698
#define G5 784
#define REST 0

const int melody[] = {
  G4, C5, C5, C5, D5, E5, D5, C5,
  B4, A4, G4, REST,
  G4, C5, C5, C5, D5, E5, D5, C5,
  D5, B4, C5, REST,
  E5, E5, E5, D5, C5, D5, E5,
  G5, F5, E5, D5, REST,
  C5, D5, E5, D5, C5, B4,
  A4, B4, C5
};

const int durations[] = {
  8, 4, 8, 8, 8, 4, 8, 4,
  8, 8, 2, 4,
  8, 4, 8, 8, 8, 4, 8, 4,
  8, 8, 2, 4,
  8, 8, 8, 8, 8, 8, 4,
  8, 8, 8, 2, 4,
  8, 8, 8, 8, 8, 8,
  8, 8, 2
};

const int tempo = 120;

void setup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  const int count = sizeof(melody) / sizeof(melody[0]);
  const int wholeNote = 60000L * 4 / tempo;

  for (int i = 0; i < count; i++) {
    const int duration = wholeNote / durations[i];

    if (melody[i] != REST) {
      tone(BUZZER_PIN, melody[i], duration * 9 / 10);
    }

    delay(duration);
    noTone(BUZZER_PIN);
  }

  delay(3000);
}
