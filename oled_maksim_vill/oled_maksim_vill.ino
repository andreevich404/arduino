#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <string.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1

Adafruit_SSD1306 display(
  SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET
);

void centerText(const char* text, int y, int size) {
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);

  int width = strlen(text) * 6 * size;
  display.setCursor((128 - width) / 2, y);
  display.print(text);
}

void setup() {
  Wire.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    while (true) {
      delay(1000);
    }
  }
}

void loop() {
  display.clearDisplay();
  centerText("MAKSIM", 12, 2);
  display.display();
  delay(1000);

  display.clearDisplay();
  centerText("VILL", 12, 3);
  display.display();
  delay(1000);

  display.clearDisplay();
  centerText("NA PARE", 25, 2);
  display.display();
  delay(1200);

  for (int i = 0; i < 4; i++) {
    display.clearDisplay();
    centerText("MAKSIM VILL", 10, 1);
    centerText("NA PARE", 30, 2);
    display.display();
    delay(350);

    display.clearDisplay();
    display.display();
    delay(200);
  }
}
