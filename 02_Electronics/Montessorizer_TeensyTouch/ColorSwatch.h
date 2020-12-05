#ifndef _COLORSWATCH_
#define _COLORSWATCH_

#include <Adafruit_NeoPixel.h>

// COLOR SWATCH
#define BLACK ((0 << 16) | (0 << 8) | 0) // = ((RED << 16) | (GREEN << 8) | BLUE)
#define WHITE ((255 << 16) | (255 << 8) | 255)
#define RED ((255 << 16) | (5 << 8) | 5)
#define GREEN ((0 << 16) | (250 << 8) | 30)
#define YELLOW ((200 << 16) | (175 << 8) | 0)
const uint32_t BLUE = ((0 << 16) | (0 << 8) | 255);
#define MAGENTA ((220 << 16) | (0 << 8) | 220)

#endif // _COLORSWATCH_
