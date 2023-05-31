#ifndef _display_h
#define _display_h
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <pins.hpp>


Adafruit_SSD1306 Display_INIT();
void Display_WRITE(Adafruit_SSD1306 display, float et, float bt, float ror, int min,int second);
class SCREEN;

#endif