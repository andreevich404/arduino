#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>
#include <U8g2_for_Adafruit_GFX.h>

// Arduino Nano: SCK D13, MOSI D11, CS D10, DC D9, RST D8.
// WARNING: classic Nano outputs 5V logic; ST7735 typically uses 3.3V logic.
Adafruit_ST7735 tft(10, 9, 8);
U8G2_FOR_ADAFRUIT_GFX text;

const char nameText[] = "Марина Симонова косячница";
const char punchline[] = "КОСЯЧНИЦА!";
const uint16_t colors[] = {
  ST77XX_CYAN, ST77XX_YELLOW, ST77XX_MAGENTA, ST77XX_GREEN
};

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1); // 160x128
  tft.fillScreen(ST77XX_BLACK);
  text.begin(tft);
  text.setFont(u8g2_font_6x13_t_cyrillic);
  text.setFontMode(1); // transparent background
}

void loop() {
  const int16_t width = text.getUTF8Width(nameText);
  const int16_t baseline = 65;

  for (int16_t x = tft.width(); x > -width; x -= 2) {
    tft.fillScreen(ST77XX_BLACK);
    text.setForegroundColor(colors[((tft.width() - x) / 30) % 4]);
    text.setCursor(x, baseline);
    text.print(nameText);
    delay(35);
  }

  // Flashing center message
  for (uint8_t i = 0; i < 6; ++i) {
    tft.fillScreen(i % 2 ? ST77XX_BLACK : ST77XX_MAGENTA);
    text.setForegroundColor(i % 2 ? ST77XX_YELLOW : ST77XX_WHITE);
    const int16_t w = text.getUTF8Width(punchline);
    text.setCursor((tft.width() - w) / 2, 65);
    text.print(punchline);
    delay(300);
  }
}
