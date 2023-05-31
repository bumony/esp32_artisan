#include <Arduino.h>
#include "pins.hpp"
#include <display.hpp>
#include <max31865.hpp>

int min = (millis() / 1000) / 60;
int second = (millis() / 1000) % 60;
Adafruit_SSD1306 display = Display_INIT();

SCREEN screen;
TEMP temp;

void setup()
{
  // put your setup code here, to run once:

  // 时间
}

void loop()
{
  // put your main code here, to run repeatedly:
  // Display_WRITE(display, et, bt, ror, min, second);
}