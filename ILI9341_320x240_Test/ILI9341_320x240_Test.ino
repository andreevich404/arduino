#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>

// Experimental test for 3.2" 240x320 SPI TFT (controller not confirmed).
// Arduino Nano: CS=D10, DC=D9, RESET=D8, MOSI=D11, SCK=D13.
// TFT VCC=3V3, GND=GND; LED unconnected initially.
// WARNING: classic Nano GPIO is 5V, TFT may only tolerate 3.3V signals.
// Level shifting is recommended. Nano 3V3 may lack sufficient current.

#define TFT_CS  10
#define TFT_DC   9
#define TFT_RST  8

Adafruit_ILI9341 tft(TFT_CS, TFT_DC, TFT_RST);

void setup() {
  tft.begin();
  tft.setRotation(1);

  tft.fillScreen(ILI9341_RED);
  delay(1000);
  tft.fillScreen(ILI9341_GREEN);
  delay(1000);
  tft.fillScreen(ILI9341_BLUE);
  delay(1000);

  tft.fillScreen(ILI9341_BLACK);
  tft.setTextColor(ILI9341_WHITE);
  tft.setTextSize(3);
  tft.setCursor(40, 80);
  tft.println("HELLO!");
  tft.setTextSize(2);
  tft.setCursor(40, 125);
  tft.println("Arduino Nano");
}

void loop() {}
