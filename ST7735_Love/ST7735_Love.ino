#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>

// ST7735: CS=D10, DC=D9, RST=D8, MOSI=D11, SCK=D13
Adafruit_ST7735 tft(10, 9, 8);

// 5x7 bitmap glyphs for "Я ТЕБЯ ЛЮБЛЮ" (columns, top bit first)
const uint8_t YA[5] = {0x46,0x29,0x19,0x09,0x7F};
const uint8_t TE[5] = {0x01,0x01,0x7F,0x01,0x01};
const uint8_t E_[5] = {0x7F,0x49,0x49,0x49,0x41};
const uint8_t BE[5] = {0x7F,0x49,0x49,0x49,0x31};
const uint8_t LE[5] = {0x40,0x3E,0x01,0x01,0x7F};
const uint8_t YU[5] = {0x7F,0x08,0x3E,0x41,0x3E};

void glyph(int x, int y, const uint8_t *bits, uint16_t color, int scale) {
  for (int col = 0; col < 5; ++col)
    for (int row = 0; row < 7; ++row)
      if (bits[col] & (1 << row))
        tft.fillRect(x + col * scale, y + row * scale, scale, scale, color);
}

void phrase(int x, int y, uint16_t color, int scale) {
  // Я ТЕБЯ
  const uint8_t *top[] = {YA, TE, E_, BE, YA};
  int pos = x;
  for (int i = 0; i < 5; ++i) {
    if (i == 1) pos += 3 * scale;
    glyph(pos, y, top[i], color, scale);
    pos += 6 * scale;
  }
  // ЛЮБЛЮ
  const uint8_t *bottom[] = {LE, YU, BE, LE, YU};
  pos = x;
  for (int i = 0; i < 5; ++i) {
    glyph(pos, y + 11 * scale, bottom[i], color, scale);
    pos += 6 * scale;
  }
}

void heart(int cx, int cy, int size, uint16_t color) {
  int r = size / 4;
  tft.fillCircle(cx - r, cy - r / 2, r, color);
  tft.fillCircle(cx + r, cy - r / 2, r, color);
  tft.fillTriangle(cx - 2 * r, cy - r / 2,
                   cx + 2 * r, cy - r / 2,
                   cx, cy + size, color);
}

void setup() {
  tft.initR(INITR_BLACKTAB);
  tft.setRotation(1);
}

void loop() {
  for (int s = 0; s < 2; ++s) {
    tft.fillScreen(ST77XX_BLACK);
    phrase(48, 12, ST77XX_WHITE, 2);
    heart(80, 99, s == 0 ? 19 : 23, ST77XX_RED);
    delay(450);
  }
}
