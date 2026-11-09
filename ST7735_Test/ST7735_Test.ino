#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// Arduino Nano (ATmega328P) -> ST7735
// SCL=D13, SDA=D11, RES=D8, DC=D9, CS=D10
// GND=GND, VCC=3V3, BL=not connected initially.
// WARNING: Nano GPIO outputs 5V; ST7735 uses 3.3V logic.
// Direct wiring may damage the display. Level shifting is recommended.
// Nano 3V3 output may not supply enough current for the display/backlight.

constexpr uint8_t TFT_CS = 10;
constexpr uint8_t TFT_DC = 9;
constexpr uint8_t TFT_RST = 8;

Adafruit_ST7735 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);

  tft.fillScreen(ST77XX_RED);
  delay(1000);
  tft.fillScreen(ST77XX_GREEN);
  delay(1000);
  tft.fillScreen(ST77XX_BLUE);
  delay(1000);

  tft.fillScreen(ST77XX_BLACK);
  tft.setTextColor(ST77XX_WHITE);
  tft.setTextSize(2);
  tft.setCursor(15, 30);
  tft.println("HELLO!");
  tft.setCursor(15, 60);
  tft.println("Arduino");
}

void loop() {}
