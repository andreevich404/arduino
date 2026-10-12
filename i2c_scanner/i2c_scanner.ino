#include <Wire.h>

void setup() {
  Wire.begin();
  Serial.begin(9600);

  delay(1000);
  Serial.println("I2C Scanner");
}

void loop() {
  byte count = 0;

  for (byte address = 1; address < 127; address++) {
    Wire.beginTransmission(address);

    if (Wire.endTransmission() == 0) {
      Serial.print("Found: 0x");
      if (address < 16) Serial.print("0");
      Serial.println(address, HEX);
      count++;
    }
  }

  if (count == 0) {
    Serial.println("No I2C devices found");
  }

  delay(3000);
}
