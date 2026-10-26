// Arduino Nano + HC-SR04 + passive buzzer: "wee-woo" proximity siren
// HC-SR04: VCC->5V, GND->GND, TRIG->D9, ECHO->D10
// Buzzer: VCC->5V, GND->GND, I/O->D6
// HC-SR04 typically works up to 400 cm, not 500 cm.

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 6

const int ALARM_DISTANCE = 400;

float getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.0343 / 2.0;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  noTone(BUZZER_PIN);
  Serial.begin(9600);
}

void loop() {
  float distance = getDistance();

  if (distance > 0 && distance <= ALARM_DISTANCE) {
    // WEE: rising pitch
    for (int freq = 500; freq <= 1800; freq += 30) {
      tone(BUZZER_PIN, freq);
      delay(8);
    }
    // WOO: falling pitch
    for (int freq = 1800; freq >= 500; freq -= 30) {
      tone(BUZZER_PIN, freq);
      delay(8);
    }
  } else {
    noTone(BUZZER_PIN);
    delay(100);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
}
