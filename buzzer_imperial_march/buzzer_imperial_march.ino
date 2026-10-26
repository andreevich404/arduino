// Arduino Nano: Imperial March (short recognizable theme)
// Passive buzzer: GND -> GND, VCC -> 5V, I/O -> D6
// Active buzzers cannot reproduce different pitches.

const byte BUZZER = 6;
struct Note { int hz; int ms; };

const Note melody[] = {
  {392, 450}, {392, 450}, {392, 450},
  {311, 320}, {466, 130}, {392, 450},
  {311, 320}, {466, 130}, {392, 650},
  {587, 450}, {587, 450}, {587, 450},
  {622, 320}, {466, 130}, {370, 450},
  {311, 320}, {466, 130}, {392, 650},
  {784, 450}, {392, 300}, {392, 130},
  {784, 450}, {740, 320}, {698, 130},
  {659, 130}, {622, 130}, {659, 450},
  {415, 320}, {554, 130}, {523, 450},
  {494, 320}, {466, 130}, {440, 450},
  {466, 320}, {311, 130}, {370, 450},
  {311, 320}, {466, 130}, {392, 650}
};

void setup() {
  pinMode(BUZZER, OUTPUT);
}

void loop() {
  for (unsigned int i = 0; i < sizeof(melody) / sizeof(melody[0]); ++i) {
    tone(BUZZER, melody[i].hz, melody[i].ms * 9 / 10);
    delay(melody[i].ms);
    noTone(BUZZER);
  }
  delay(2500);
}
