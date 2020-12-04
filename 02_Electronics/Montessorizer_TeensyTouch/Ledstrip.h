// #ifndef _LEDSTRIP_H_
// #define _LEDSTRIP_H_

// #include <Adafruit_NeoPixel.h>


// #define BRIGHTNESS 255
// #define NPIXA 255         // number of pixel in letter A

// class Ledstrip
// {
// private:
// //--------------------------------
// //------ COLOR N ANIMATION -------
// //--------------------------------
// // Led colors
//   Adafruit_NeoPixel strip;
//   int pinStrip ;
//   int nPix ;
//   int stripColor ;

//   int part1 = 52;
//   int part2 = 73;
//   int part3 = 88;
//   int part4 = 100;

//   int outside1 = 61; // 61 leds on first part of the A
//   int inside1 = 53;
//   int outside2 = 0;
//   int inside2 = 13;
//   int outside3 = 25;
//   int inside3 = 0;
//   int outside4 = 7;
//   int inside4 = 12;
//   void setLightPath(int prog_, uint32_t col_);  
//   void setPixColor(int pix_, int col_);

// public:
//   Ledstrip(int pinStrip_, int nPix_);
//   ~Ledstrip(); // destructor

//   const int BLACK = ((0 << 16) | (0 << 8) | 0); // = ((RED << 16) | (GREEN << 8) | BLUE)
//   const int WHITE = ((255 << 16) | (255 << 8) | 255);
//   const int RED = ((255 << 16) | (5 << 8) | 5);
//   const int GREEN = ((0 << 16) | (250 << 8) | 30);
//   const int YELLOW = ((200 << 16) | (175 << 8) | 0);
//   const int BLUE = ((0 << 16) | (0 << 8) | 255);
//   const int MAGENTA = ((220 << 16) | (0 << 8) | 220);
// };

// Ledstrip::~Ledstrip()
// {
// }

// #endif /* _LEDSTRIP_H_ */