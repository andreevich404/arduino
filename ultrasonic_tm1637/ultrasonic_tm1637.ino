// Arduino Nano parking sensor: HC-SR04 + TM1637 + active buzzer
// HC-SR04: TRIG D9, ECHO D10
// TM1637: CLK D2, DIO D3
// Buzzer module: I/O D6, VCC 5V, GND GND
// Libraries: GyverSegment and GyverIO

#include <GyverSegment.h>

#define TRIG_PIN 9
#define ECHO_PIN 10
#define CLK_PIN 2
#define DIO_PIN 3
#define BUZZER_PIN 6

// Typical 3-pin active buzzer modules trigger on LOW.
// If yours triggers on HIGH, swap these two values.
const byte BUZZER_ON = LOW;
const byte BUZZER_OFF = HIGH;

Disp1637Colon display(DIO_PIN, CLK_PIN, false);

const unsigned long MEASURE_INTERVAL = 100;
const unsigned long BEEP_LENGTH = 30; // Short, softer-sounding beep
unsigned long lastMeasure = 0;
unsigned long lastBeepStart = 0;
unsigned long beepStarted = 0;
unsigned long beepInterval = 0;
bool beeping = false;
bool firstMeasure = true;

void stopBuzzer() {
  digitalWrite(BUZZER_PIN, BUZZER_OFF);
  beeping = false;
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIG_PIN, LOW);

  digitalWrite(BUZZER_PIN, BUZZER_OFF);
  pinMode(BUZZER_PIN, OUTPUT);

  display.brightness(5);
  display.clear();
  display.update();
  Serial.begin(9600);
}

void loop() {
  unsigned long now = millis();

  if (firstMeasure || now - lastMeasure >= MEASURE_INTERVAL) {
    firstMeasure = false;
    lastMeasure = now;

    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    unsigned long duration = pulseIn(ECHO_PIN, HIGH, 30000UL);
    int distance = duration ? (int)(duration * 0.0343f / 2.0f) : -1;

    display.clear();
    if (distance >= 2 && distance <= 400) {
      display.setCursorEnd();
      display.printRight(true);
      display.print(distance);
      display.printRight(false);

      Serial.print("Distance: ");
      Serial.print(distance);
      Serial.println(" cm");

      if (distance > 100) beepInterval = 0;
      else if (distance > 50) beepInterval = 1500;
      else if (distance > 20) beepInterval = 700;
      else if (distance >= 10) beepInterval = 300;
      else beepInterval = 140;
    } else {
      display.print("----");
      beepInterval = 0;
      Serial.println("No signal / out of range");
    }
    display.update();
  }

  now = millis();
  if (beeping && now - beepStarted >= BEEP_LENGTH) {
    stopBuzzer();
  }

  if (beepInterval == 0) {
    if (beeping) stopBuzzer();
  } else if (!beeping && (lastBeepStart == 0 || now - lastBeepStart >= beepInterval)) {
    digitalWrite(BUZZER_PIN, BUZZER_ON);
    beeping = true;
    beepStarted = now;
    lastBeepStart = now;
  }
}
