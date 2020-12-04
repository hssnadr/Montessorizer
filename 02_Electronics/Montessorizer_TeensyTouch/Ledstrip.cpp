#include "Ledstrip.h"

Ledstrip::Ledstrip(int pinStrip_, int nPix_) {
  this->pinStrip = pinStrip_;
  this->nPix = nPix_;
  this->strip = Adafruit_NeoPixel(this->nPix, this->pinStrip, NEO_GRB + NEO_KHZ800);
}

void Ledstrip::begin() {
  this->strip.setBrightness(BRIGHTNESS);
  this->strip.begin(); // This initializes the NeoPixel library.
  this->strip.show(); // Initialize all pixels to 'off'
}

void Ledstrip::setPixel(int pix_, int col_) {
  // Set color for one pixel using its index number
  this->strip.setPixelColor(pix_, col_);
}

void Ledstrip::show() {
  this->strip.show();
}

void Ledstrip::setLightPath(int prog_, uint32_t col_){
  prog_ = constrain(prog_, 0, 100);
  int ledprog_ = 0;
  int progPix_ = 0;

  for(int i=0;i<this->nPix;i++){
     this->setPixel(i, BLACK);
  }

  // PART 1 ------------------------------------------------------
  // OUTSIDE
  progPix_ = this->outside1*prog_/float(this->part1);
  progPix_ = constrain(progPix_,0, this->outside1);
  for(int i=0; i<progPix_;i++){
   this->setPixel(ledprog_ + i, col_);
  }
  ledprog_ += this->outside1;
  
  // INSIDE
  progPix_ = this->inside1*prog_/float(this->part1);
  progPix_ = constrain(progPix_,0,this->inside1);
  for(int i=0; i<progPix_;i++){
   this->setPixel(ledprog_ + this->inside1 - i - 1, col_);
  }
  ledprog_ += this->inside1;
    
  // PART 2 ------------------------------------------------------
  if(prog_ > this->part1){
    // INSIDE
    progPix_ = this->inside2*(prog_-this->part1)/float(this->part2-this->part1);
    progPix_ = constrain(progPix_,0,this->inside2);
    for(int i=0; i<progPix_;i++){
     this->setPixel(ledprog_ + this->inside2 - i - 1, col_);
    }
    ledprog_ += this->inside2;
  }

  // PART 3 ------------------------------------------------------
  if(prog_ > this->part2){
    // OUTSIDE
    progPix_ = this->outside3*(prog_-this->part2)/float(this->part3-this->part2);
    progPix_ = constrain(progPix_,0,this->outside3);
    for(int i=0; i<progPix_;i++){
     this->setPixel(ledprog_ + this->inside4 + this->outside4 + this->outside3 - i - 1, col_);
    }
    //ledprog_ += this->outside3;

    // INSIDE
    progPix_ = this->inside3*(prog_-this->part2)/float(this->part3-this->part2);
    // progPix_ = constrain(progPix_,0,this->inside4);
    for(int i=0; i<progPix_;i++){
     this->setPixel(ledprog_ + this->inside4 + this->outside4 + this->outside3 + i, col_);
    }
  }

  // PART 4 ------------------------------------------------------
  if(prog_ > this->part3){
    // OUTSIDE
    progPix_ = this->outside4*(prog_-this->part3)/float(this->part4-this->part3);
    // progPix_ = constrain(progPix_,0,this->outside4);
    for(int i=0; i<=progPix_;i++){
     this->setPixel(ledprog_ + this->inside4 + this->outside4 - i - 1, col_);
    }

    // INSIDE
    progPix_ = this->inside4*(prog_-this->part3)/float(this->part4-this->part3);
    // progPix_ = constrain(progPix_,0,this->inside4);
    for(int i=0; i<=progPix_;i++){
     this->setPixel(ledprog_ + i, col_);
    }
  }
}