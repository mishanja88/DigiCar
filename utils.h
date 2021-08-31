#ifndef UTILS_H
#define UTILS_H

#include <Arduino.h>

class Adafruit_NeoPixel;

void fillStrip(Adafruit_NeoPixel *strip, uint32_t c=0, uint16_t first=0, uint16_t count=0);

void blackenByModulo(Adafruit_NeoPixel *strip, uint16_t first, uint16_t modulo);

//бегущий пиксель
void runPix(Adafruit_NeoPixel *strip, uint8_t cicles, uint8_t wait);

//эффект пламени
void flame(Adafruit_NeoPixel *strip, uint8_t cicles, uint8_t wait);

// плавное наростание яркости любого цвета
void rgbFade(Adafruit_NeoPixel *strip, uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);

// //заполнение ленты пиксель за пикселем
void colorWipe(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait);

//радуга
void rainbow(Adafruit_NeoPixel *strip, uint8_t wait);

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel *strip, uint8_t wait);

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait);

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel *strip, uint8_t wait);

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel *strip, byte WheelPos);

#endif // UTILS_H
