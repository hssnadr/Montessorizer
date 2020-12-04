#ifndef _LEDSTRIP_H_
#define _LEDSTRIP_H_

#include <Adafruit_NeoPixel.h>

#define BRIGHTNESS 255
#define NPIXA 171       // number of pixel in letter A

#define BLACK ((0 << 16) | (0 << 8) | 0) // = ((RED << 16) | (GREEN << 8) | BLUE)
#define WHITE ((255 << 16) | (255 << 8) | 255)
#define RED ((255 << 16) | (5 << 8) | 5)
#define GREEN ((0 << 16) | (250 << 8) | 30)
#define YELLOW ((200 << 16) | (175 << 8) | 0)
#define BLUE ((0 << 16) | (0 << 8) | 255)
#define MAGENTA ((220 << 16) | (0 << 8) | 220)

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
  int part1 = 52;
  int part2 = 73;
  int part3 = 88;
  int part4 = 100;

  int outside1 = 61; // 61 leds on first part of the A
  int inside1 = 53;
  int outside2 = 0;
  int inside2 = 13;
  int outside3 = 25;
  int inside3 = 0;
  int outside4 = 7;
  int inside4 = 12;
  void setPixel(int pix_, int col_);
};

#endif /* _LEDSTRIP_H_ */