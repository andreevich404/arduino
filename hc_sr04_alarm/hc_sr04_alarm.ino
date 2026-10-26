// Arduino Nano + HC-SR04 + buzzer: proximity alarm
// HC-SR04: VCC->5V, GND->GND, TRIG->D9, ECHO->D10
// Buzzer: VCC->5V, GND->GND, I/O->D6
// HC-SR04 typical reliable range is up to 400 cm, not 500 cm.

#define TRIG_PIN 9
#define ECHO_PIN 10
#define BUZZER_PIN 6

const int ALARM_DISTANCE = 400; // centimeters

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
  digitalWrite(BUZZER_PIN, LOW);
  Serial.begin(9600);
}

void loop() {
  float distance = getDistance();

  if (distance > 0 && distance <= ALARM_DISTANCE) {
    tone(BUZZER_PIN, 1500);
  } else {
    noTone(BUZZER_PIN);
  }

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  delay(100);
}
