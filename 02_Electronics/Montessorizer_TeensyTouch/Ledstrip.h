#ifndef _LEDSTRIP_H_
#define _LEDSTRIP_H_

#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 30
#define NPIXA 171 // number of pixel in letter A

class Ledstrip
{
public:
  Ledstrip(int pinStrip_, int nPix_);
  void begin();
  void show();
  void setLightPath(int prog_, uint32_t col_);

private:
  int pinStrip;
  int nPix;
  Adafruit_NeoPixel strip;
  int stripColor;

  const int part1 = 52;
  const int part2 = 73;
  const int part3 = 88;
  const int part4 = 100;

  const int outside1 = 61; // 61 leds on first part of the A
  const int inside1 = 53;
  const int outside2 = 0;
  const int inside2 = 13;
  const int outside3 = 25;
  const int inside3 = 0;
  const int outside4 = 7;
  const int inside4 = 12;
  void setPixel(int pix_, int col_);
};

#endif /* _LEDSTRIP_H_ */