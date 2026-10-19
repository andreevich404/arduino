// Arduino Nano + HC-SR04 + TM1637 (Seeed Grove TM1637 library)
// HC-SR04: TRIG D9, ECHO D10, VCC 5V, GND GND
// TM1637: CLK D2, DIO D3, VCC 5V, GND GND

#include <TM1637.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define CLK_PIN 2
#define DIO_PIN 3

TM1637 display(CLK_PIN, DIO_PIN);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  display.init();
  display.set(BRIGHT_TYPICAL);
  display.clearDisplay();

  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  if (duration == 0) {
    display.clearDisplay();
    Serial.println("No signal");
  } else {
    int distance = duration * 0.0343 / 2;

    if (distance >= 2 && distance <= 400) {
      display.display(0, distance / 1000 % 10);
      display.display(1, distance / 100 % 10);
      display.display(2, distance / 10 % 10);
      display.display(3, distance % 10);

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    } else {
      display.clearDisplay();
      Serial.println("Out of range");
    }
  }

  delay(200);
}
