#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void drawHeart(int cx, int cy, float scale) {
  int r = 10 * scale;
  int offset = 10 * scale;
  display.fillCircle(cx - offset, cy, r, SSD1306_WHITE);
  display.fillCircle(cx + offset, cy, r, SSD1306_WHITE);
  display.fillTriangle(
    cx - 20 * scale, cy,
    cx + 20 * scale, cy,
    cx, cy + 25 * scale,
    SSD1306_WHITE
  );
}

void setup() {
  Wire.begin();
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) delay(1000);
  }
  display.clearDisplay();
  display.display();
}

void loop() {
  for (int i = 0; i < 60; i++) {
    float scale = 0.85 + 0.15 * sin(i * 0.105);
    display.clearDisplay();
    drawHeart(64, 19, scale);
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(35, 54);
    display.print("For you <3");
    display.display();
    delay(30);
  }
}
