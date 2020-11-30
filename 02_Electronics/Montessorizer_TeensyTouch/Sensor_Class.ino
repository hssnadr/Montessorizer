// ----------------------------------------------------------------------
// -----------------------      SENSOR CLASS      -----------------------
// ----------------------------------------------------------------------

Sensor::Sensor(int pinSens_)
{
  this->pinSens = pinSens_;
}

void Sensor::begin()
{
  for (int i = 0; i < NRAW; i++)
  {
    this->dataCollect[i] = 0;
  }
  for (int i = 0; i < NMEAN; i++)
  {
    this->meanCollect[i] = 0;
  }
  for (int i = 0; i < DATAWINDOW; i++)
  {
    this->dataWindow[i] = 0;
  }
}

void Sensor::update()
{

  int sens_ = touchRead(this->pinSens);

  // UPDATE RAW COLLECTION
  for (int i = 0; i < NRAW - 1; i++)
  {
    this->dataCollect[i] = this->dataCollect[i + 1];
  }
  this->dataCollect[NRAW - 1] = sens_;
  this->rangeDataCollect = getArrayRange(this->dataCollect, NRAW);

  // MOVING MEAN
  float mean_ = 0;
  for (int i = 0; i < NRAW; i++)
  {
    mean_ += this->dataCollect[i];
  }
  mean_ /= NRAW;

  // UPDATE MEAN COLLECTION
  for (int i = 0; i < NMEAN - 1; i++)
  {
    meanCollect[i] = meanCollect[i + 1];
  }
  meanCollect[NMEAN - 1] = mean_;

  // FILL DATA WINDOW (with mean values)
  this->dataWindow[this->curWindowIndex] = mean_;
  this->curWindowIndex++;
  if(this->curWindowIndex >= DATAWINDOW){
    this->curWindowIndex = 0;
  }
}

float Sensor::getSensorVal() {
  float __val = this->meanCollect[NMEAN-1] - this->meanCollect[0];
  return __val;
}

float Sensor::getSensorRange() {
  float __range = getArrayRange(this->dataWindow, DATAWINDOW);
  return __range;
}