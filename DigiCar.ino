#include "utils.h"
#include "keyes.h"

Keyes keyes(1); // 1 - пин в аналоговой нумерации

#include <Adafruit_NeoPixel.h>

#define NUM_PIX 32
#define colorSaturation 128

// three element pixels, in different order and speeds
Adafruit_NeoPixel strip0 = Adafruit_NeoPixel(NUM_PIX, 0, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUM_PIX, 1, NEO_GRB + NEO_KHZ800);

Adafruit_NeoPixel *strips[] = { &strip0, &strip1, NULL };

// the setup routine runs once when you press reset:
void setup() {

  // this resets all the neopixels to an off state
  for (int i = 0; strips[i] != NULL; ++i)
  {
    strips[i]->begin();
    strips[i]->show();
  }
}

void turningLights(bool isLeft)
{
  int pix_begin = isLeft ? (NUM_PIX / 2) : 0;

  for (int count = 0; count < 3; ++count)
  {
    for (int i = 0; i < 511; ++i)
    {
      int c = 255 - abs(255 - i);

      for (int id = 0; strips[id] != NULL; ++id)
      {
        fillStrip(strips[id], strips[id]->Color(c, c, 0), pix_begin, NUM_PIX / 2);
        strips[id]->show();
      }
      delay(2);
    }
  }
}

void rearLights()
{
  colorWipe(strips[1], strips[1]->Color(255, 0, 0), 50);
}

void frontLights()
{
  colorWipe(strips[0], strips[0]->Color(255, 140, 140), 50);
}

int modeIteration = 0;

enum Modes
{
  MODE_SIMPLE,
  MODE_BLINK,
  MODE_RAINBOW,
  MODE_POLICE,
  MODE_PINK_SUPERHERO,
  MODE_FIRE,
  MODE_MAX
};

int curMainMode = MODE_SIMPLE;

void toggleMainMode()
{
  curMainMode = (curMainMode + 1) % MODE_MAX;
  modeIteration = 0;
}

void showMainMode()
{
  switch (curMainMode)
  {
    case MODE_SIMPLE:
      {
        int toggleCount = modeIteration / 8;
        for(int id = 0; strips[id] != NULL; ++id)
        {        
          int modulo = id ? 3 : 2;
          uint32_t c = (id == 0) ? strips[0]->Color(128, 128, 128) : strips[1]->Color(128, 0, 0);
          uint32_t bl = strips[id]->Color(0, 0, 0);
          for(int i = 0; i < strips[id]->numPixels(); ++i)
          {
            strips[id]->setPixelColor(i, ((i + toggleCount) % modulo) ? bl : c); 
          }
          strips[id]->show();
        }
      }
      break;

    case MODE_BLINK:
      {
        if (modeIteration % 10 == 0)
        {
          uint8_t c = ((modeIteration / 10) & 1) ? 0 : 128;
          colorWipe(strips[0], strips[0]->Color(c, c, c), 50);
          colorWipe(strips[1], strips[0]->Color(c, 0, 0), 50);
        }
      }
      break;

    case MODE_RAINBOW:
      {
        for (int id = 0; strips[id] != NULL; ++id)
        {
          for (int i = 0; i < strips[id]->numPixels(); i++)
          {
            strips[id]->setPixelColor(i, Wheel(strips[id], (i + modeIteration) & 255));
          }
          strips[id]->show();
        }
      }
      break;

    case MODE_POLICE:
      {
        int it = modeIteration % 32;
        int toggle = 16 - abs(16 - it);
        bool isReverse = modeIteration & 0x10;
        int r = isReverse ? 0 : (toggle * 16);
        int b = isReverse ? (toggle * 16) : 0;
        for (int id = 0; strips[id] != NULL; ++id)
        {
          fillStrip(strips[id], strips[id]->Color(r, 0, b), 0, strips[id]->numPixels() / 2);
          fillStrip(strips[id], strips[id]->Color(b, 0, r), strips[id]->numPixels() / 2, strips[id]->numPixels() / 2);
          strips[id]->show();
        }
      }
      break;

    case MODE_PINK_SUPERHERO:
      {
        for (int id = 0; strips[id] != NULL; ++id)
        {
          for (int i = 0; i < strips[id]->numPixels(); i++)
          {
            strips[id]->setPixelColor(i, Wheel(strips[id], 128 + 64 + abs(64 - ((i + modeIteration) & 127))));
          }
          strips[id]->show();
        }
      }
      break;

    case MODE_FIRE:
      {
        for (int id = 0; strips[id] != NULL; ++id)
        {
          for (int i = 0; i < strips[id]->numPixels(); i++)
          {
            strips[id]->setPixelColor(i, strips[id]->Color(random(150, 254), random(0, 45), 0));
          }
          strips[id]->setBrightness(random(151, 254));
          strips[id]->show();
        }
      }
      break;
  }

  modeIteration++;
}

char prevBtn = keyes.read();

// the loop routine runs over and over again forever:
void loop() {
  char btn = keyes.read();
  if (prevBtn != btn)
  {
    prevBtn = btn;
    switch (btn)
    {
      case 'U': case 'D': turningLights(btn == 'U'); break; //

      case 'L': rearLights(); break; // синий
      case 'R': frontLights(); break; //
      case 'S': toggleMainMode(); break; //
      default: break;
    }
  }

  showMainMode();
  delay(80);
}
