// #define NSMOOTH 40 // number of input to compute moving mean
// // #define NSMOOTH2 50
// #define DATAWINDOW 50

// // ----------------------------------------------------------------------
// // -----------------------      CLASS DEF       -------------------------
// // ----------------------------------------------------------------------

// class Sensor
// {
// public:
//   Sensor(int pinSens_);
//   void begin();
//   void update();
//   boolean isTouched = false;

// private:
//   int pinSens;
//   int dataCollect[NSMOOTH];
//   float rangeDataCollect = 0;

//   int dataWindow[DATAWINDOW];
//   int curWindowIndex = 0;
//   float meanWindow = 0.0f;
//   int maxWindow = 700; //1024; // init at max
//   // int maxWindow = 0;    // init at min
//   float threshold = 700; //1024.0f;

//   float curMean = 0;
//   float oldMean = 0;

//   int offset = 3;
//   float curOffsetMean = 0;
//   float oldOffsetMean = 0;
//   // int timerDeriv = 0; // use to calculate derivate
//   boolean getTouched();
// };

// // ----------------------------------------------------------------------
// // -------------------------      MAIN       ----------------------------
// // ----------------------------------------------------------------------

// Sensor sensor1 = Sensor(0);
// Sensor sensor2 = Sensor(1);
// Sensor sensor3 = Sensor(2);

// void setup()
// {
//   sensor1.begin(); // useless ?
//   sensor2.begin();
//   sensor3.begin();

//   Serial.begin(9600);
// }

// void loop()
// {
//   if (millis() % 50 == 0)
//   {
//     sensor1.update();
//     Serial.print('\t');
    
//     sensor2.update();
//     Serial.print('\t');
    
//     sensor3.update();
//     Serial.print('\t');
    
//     Serial.println();
//   }
// }

// // ----------------------------------------------------------------------
// // -----------------------      SENSOR CLASS      -----------------------
// // ----------------------------------------------------------------------

// Sensor::Sensor(int pinSens_)
// {
//   this->pinSens = pinSens_;
// }

// void Sensor::begin()
// {
//   for (int i = 0; i < NSMOOTH; i++)
//   {
//     dataCollect[i] = 0;
//   }
// }

// void Sensor::update()
// {

//   int sens_ = analogRead(this->pinSens);

//   // FILL DATA WINDOW
//   this->dataWindow[this->curWindowIndex] = sens_;
//   this->curWindowIndex++;
//   if (curWindowIndex > DATAWINDOW)
//   {
//     // get window range then reset
//     this->meanWindow = getArrayMean(this->dataWindow, DATAWINDOW);
//     this->maxWindow = getArrayMax(this->dataWindow, DATAWINDOW);
//     this->threshold = 2.0 * (this->maxWindow - this->meanWindow + 1) + this->meanWindow; // add +1 to manage case max = mean
//     this->curWindowIndex = 0;
//   }

//   // UPDATE COLLECTION
//   for (int i = 0; i < NSMOOTH - 1; i++)
//   {
//     dataCollect[i] = dataCollect[i + 1];
//   }
//   dataCollect[NSMOOTH - 1] = sens_;
//   this->rangeDataCollect = getArrayRange(this->dataCollect, NSMOOTH);

//   // MOVING MEAN
//   float mean_ = 0;
//   for (int i = 0; i < NSMOOTH - this->offset; i++)
//   {
//     mean_ += dataCollect[i];
//   }
//   mean_ /= (NSMOOTH - this->offset);
//   this->oldMean = this->curMean;
//   this->curMean = mean_;

//   // MOVING MEAN OFFSET
//   mean_ = 0;
//   for (int i = this->offset; i < NSMOOTH; i++)
//   {
//     mean_ += dataCollect[i];
//   }
//   mean_ /= (NSMOOTH - this->offset);
//   this->oldOffsetMean = this->curOffsetMean;
//   this->curOffsetMean = mean_;

//   // GOOD
//   // Serial.print(this->curMean);
//   // Serial.print('\t');
//   // Serial.print(this->curOffsetMean);
//   // Serial.print('\t');

//   // Serial.print(this->rangeDataCollect + 600);
//   // Serial.print('\t');

//   // Serial.print(this->meanWindow);
//   // Serial.print('\t');
//   // Serial.print(this->threshold);
//   // Serial.print('\t');

//   // RESULT
//   if (this->getTouched())
//   {
//     // Serial.print(750);

//     Serial.print(this->pinSens);

//     // this->meanWindow = getArrayMean(this->dataWindow, this->curWindowIndex);
//     // this->maxWindow = getArrayMax(this->dataWindow, this->curWindowIndex);
//     // this->threshold = 1.0 * (this->maxWindow - this->meanWindow) + this->meanWindow;
//     this->curWindowIndex = 0; // reset window
//   }
//   else
//   {
//     // Serial.print(640);
//     Serial.print(-1);
//   }
// }

// boolean Sensor::getTouched()
// {
//   boolean isTch_ = false;
//   if (this->rangeDataCollect > 5)
//   {
//     if (this->oldOffsetMean < this->oldMean && this->curMean <= this->curOffsetMean)
//     {
//       isTch_ = true;
//     }
//   }
//   return isTch_;
// }

// // ----------------------------------------------------------------------
// // -----------------------      UTILITIES      --------------------------
// // ----------------------------------------------------------------------

// int getArrayRange(int *array_, int size_)
// {
//   int range_ = getArrayMax(array_, size_) - getArrayMin(array_, size_);
//   return range_;
// }

// int getArrayMin(int *array_, int size_)
// {
//   int min_ = array_[0];
//   for (int i = 0; i < size_; i++)
//   {
//     if (array_[i] < min_)
//     {
//       min_ = array_[i];
//     }
//   }
//   return min_;
// }

// int getArrayMax(int *array_, int size_)
// {
//   int max_ = array_[0];
//   for (int i = 0; i < size_; i++)
//   {
//     if (array_[i] > max_)
//     {
//       max_ = array_[i];
//     }
//   }
//   return max_;
// }

// float getArrayMean(int *array_, int size_)
// {
//   float mean_ = 0.0f;
//   for (int i = 0; i < size_; i++)
//   {
//     mean_ += float(array_[i]) / size_;
//   }
//   return mean_;
// }