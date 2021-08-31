#include "utils.h"

#include <Adafruit_NeoPixel.h>

void fillStrip(Adafruit_NeoPixel *strip, uint32_t c, uint16_t first, uint16_t count)
{
  for(uint16_t i = first; i < first + count; ++i)
      strip->setPixelColor(i, c); 
}

void blackenByModulo(Adafruit_NeoPixel *strip, uint16_t first, uint16_t modulo)
{
  uint16_t except = first % modulo;
  for(uint16_t i = 0; i < strip->numPixels(); ++i)
  {
    if(i % modulo != except)
      strip->setPixelColor(i, strip->Color(0,0,0)); 
  }
}

//бегущий пиксель
void runPix(Adafruit_NeoPixel *strip, uint8_t cicles, uint8_t wait)
{
  strip->setBrightness(255);
  for (int c = 0; c < cicles; c++)
  {
    for (int i = 0; i < strip->numPixels(); i++)
    {
      strip->setPixelColor(i, strip->Color(0, 0, 255));
      strip->show();
      strip->setPixelColor(i, strip->Color(0, 0, 0));
      delay(wait);
    }
  }
}

//эффект пламени
void flame(Adafruit_NeoPixel *strip, uint8_t cicles, uint8_t wait)
{
  strip->setBrightness(255);
  for (int i = 0; i < cicles; i++)
  {
    for (int i = 0; i < strip->numPixels(); i++)
    {
      strip->setPixelColor(i, strip->Color(random(150, 254), random(0, 45), 0));
    }
    strip->setBrightness(random(151, 254));
    strip->show(); // This sends the updated pixel color to the hardware.
    delay(random(wait));
  }
}

// плавное наростание яркости любого цвета
void rgbFade(Adafruit_NeoPixel *strip, uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
  strip->setBrightness(255);
  for (uint8_t b = 0; b < 255; b++)
  {
    for (uint8_t i = 0; i < strip->numPixels(); i++)
    {
      strip->setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    }
    strip->show();
    delay(wait);
  }
  delay(500);

  for (uint8_t b = 255; b > 0; b--)
  {
    for (uint8_t i = 0; i < strip->numPixels(); i++)
    {
      strip->setPixelColor(i, red * b / 255, green * b / 255, blue * b / 255);
    }
    strip->show();
    delay(wait);
  }
  strip->setBrightness(0);
  strip->show();
  delay(200);
}

// //заполнение ленты пиксель за пикселем
void colorWipe(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait)
{
  strip->setBrightness(255);
  for (uint16_t i = 0; i < strip->numPixels(); i++)
  {
    strip->setPixelColor(i, c);
    strip->show();
    delay(wait);
  }
}

//радуга
void rainbow(Adafruit_NeoPixel *strip, uint8_t wait)
{
  uint16_t i, j;

  strip->setBrightness(255);
  for (j = 0; j < 256; j++) {
    for (i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel(strip, (i + j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(Adafruit_NeoPixel *strip, uint8_t wait)
{
  uint16_t i, j;

  strip->setBrightness(255);
  for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
    for (i = 0; i < strip->numPixels(); i++) {
      strip->setPixelColor(i, Wheel(strip, ((i * 256 / strip->numPixels()) + j) & 255));
    }
    strip->show();
    delay(wait);
  }
}

//Theatre-style crawling lights.
void theaterChase(Adafruit_NeoPixel *strip, uint32_t c, uint8_t wait)
{
  strip->setBrightness(255);
  for (int j = 0; j < 10; j++) { //do 10 cycles of chasing
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip->numPixels(); i = i + 3) {
        strip->setPixelColor(i + q, c);  //turn every third pixel on
      }
      strip->show();

      delay(wait);

      for (int i = 0; i < strip->numPixels(); i = i + 3) {
        strip->setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

//Theatre-style crawling lights with rainbow effect
void theaterChaseRainbow(Adafruit_NeoPixel *strip, uint8_t wait)
{
  strip->setBrightness(255);
  for (int j = 0; j < 256; j++) {   // cycle all 256 colors in the wheel
    for (int q = 0; q < 3; q++) {
      for (int i = 0; i < strip->numPixels(); i = i + 3) {
        strip->setPixelColor(i + q, Wheel(strip, (i + j) % 255)); //turn every third pixel on
      }
      strip->show();

      delay(wait);

      for (int i = 0; i < strip->numPixels(); i = i + 3) {
        strip->setPixelColor(i + q, 0);      //turn every third pixel off
      }
    }
  }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(Adafruit_NeoPixel *strip, byte WheelPos)
{
  strip->setBrightness(255);
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip->Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else if (WheelPos < 170) {
    WheelPos -= 85;
    return strip->Color(0, WheelPos * 3, 255 - WheelPos * 3);
  } else {
    WheelPos -= 170;
    return strip->Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  }
}
