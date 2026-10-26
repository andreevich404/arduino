// Arduino Nano + 3-pin buzzer (GND, VCC, I/O)
// GND -> GND, VCC -> 5V, I/O -> D6
// Melody works only with a passive buzzer. Active buzzers play fixed-pitch beeps.

const int BUZZER = 6;
const int REST = 0;

// Ode to Joy (Beethoven), recognizable opening phrase
const int notes[] = {
  330, 330, 349, 392, 392, 349, 330, 294,
  262, 262, 294, 330, 330, 294, 294,
  330, 330, 349, 392, 392, 349, 330, 294,
  262, 262, 294, 330, 294, 262, 262
};

// Note durations: 4 = quarter, 2 = half
const int lengths[] = {
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 2,
  4, 4, 4, 4, 4, 4, 4, 4,
  4, 4, 4, 4, 4, 4, 2
};

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  const int beatMs = 380;
  const int count = sizeof(notes) / sizeof(notes[0]);

  for (int i = 0; i < count; i++) {
    int duration = beatMs * 4 / lengths[i];

    if (notes[i] != REST) {
      tone(BUZZER, notes[i], duration * 9 / 10);
    } else {
      noTone(BUZZER);
    }

    delay(duration);
    noTone(BUZZER);
  }

  delay(2500);
}
