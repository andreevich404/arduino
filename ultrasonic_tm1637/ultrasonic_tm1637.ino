// Arduino Nano + HC-SR04 + TM1637 using GyverSegment
// HC-SR04: TRIG D9, ECHO D10
// TM1637: CLK D2, DIO D3
// Install GyverSegment and GyverIO libraries.

#include <GyverSegment.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define CLK_PIN 2
#define DIO_PIN 3

// GyverSegment expects DIO first, CLK second.
Disp1637Colon display(DIO_PIN, CLK_PIN, false);

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  display.brightness(5);
  display.clear();
  display.update();
  Serial.begin(9600);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);

  display.clear();
  if (duration > 0) {
    int distance = duration * 0.0343 / 2;
    if (distance >= 2 && distance <= 400) {
      display.setCursorEnd();
      display.printRight(true);
      display.print(distance);
      display.printRight(false);
      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");
    } else {
      display.print("----");
      Serial.println("Out of range");
    }
  } else {
    display.print("----");
    Serial.println("No signal");
  }

  display.update();
  delay(200);
}
