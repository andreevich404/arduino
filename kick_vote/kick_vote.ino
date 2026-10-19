// Arduino Nano + LCD1602 I2C (0x27) + two 3-pin button modules
// LCD: SDA A4, SCL A5, VCC 5V, GND GND
// Green button: OUT D4; Red button: OUT D5
// Button modules: VCC 5V, GND GND
// Uses LiquidCrystal_I2C library.

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const byte GREEN_PIN = 4;  // Save
const byte RED_PIN = 5;    // Kick
const byte PRESSED = LOW;  // Most 3-pin button modules are active LOW
const unsigned long DEBOUNCE_MS = 40;
const unsigned long RESET_HOLD_MS = 2000;

LiquidCrystal_I2C lcd(0x27, 16, 2);

bool decided = false;
bool lastGreen = false;
bool lastRed = false;
unsigned long greenChangedAt = 0;
unsigned long redChangedAt = 0;
bool stableGreen = false;
bool stableRed = false;
unsigned long bothHeldAt = 0;

void showVote() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ivan Ivanov");
  lcd.setCursor(0, 1);
  lcd.print("Kick? YES / NO");
}

void showResult(bool kicked) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Ivan Ivanov");
  lcd.setCursor(0, 1);
  lcd.print(kicked ? "BALBES" : "SAVED");
  decided = true;
}

void setup() {
  pinMode(GREEN_PIN, INPUT_PULLUP);
  pinMode(RED_PIN, INPUT_PULLUP);
  lcd.init();
  lcd.backlight();
  showVote();
}

void loop() {
  unsigned long now = millis();
  bool green = digitalRead(GREEN_PIN) == PRESSED;
  bool red = digitalRead(RED_PIN) == PRESSED;

  if (green != lastGreen) greenChangedAt = now;
  if (red != lastRed) redChangedAt = now;
  lastGreen = green;
  lastRed = red;

  bool oldGreen = stableGreen;
  bool oldRed = stableRed;
  if (now - greenChangedAt >= DEBOUNCE_MS) stableGreen = green;
  if (now - redChangedAt >= DEBOUNCE_MS) stableRed = red;

  if (decided) {
    if (stableGreen && stableRed) {
      if (bothHeldAt == 0) bothHeldAt = now;
      if (now - bothHeldAt >= RESET_HOLD_MS) {
        decided = false;
        bothHeldAt = 0;
        showVote();
        // Wait for both buttons to be released before accepting a vote.
        while (digitalRead(GREEN_PIN) == PRESSED ||
               digitalRead(RED_PIN) == PRESSED) delay(10);
        stableGreen = stableRed = false;
        lastGreen = lastRed = false;
      }
    } else {
      bothHeldAt = 0;
    }
    return;
  }

  // Ignore simultaneous presses to avoid ambiguous votes.
  if (stableGreen && stableRed) return;
  if (!oldRed && stableRed) showResult(true);
  else if (!oldGreen && stableGreen) showResult(false);
}
