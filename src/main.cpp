#include <Arduino.h>
#include <SSD1306.h>

SSD1306             display(0x3c, 4, 5, GEOMETRY_128_32);

void setup() {
  // put your setup code here, to run once:
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_16);
  display.drawString(10, 10, "Hello World");
  display.display();
}

void loop() {
  // put your main code here, to run repeatedly:
}