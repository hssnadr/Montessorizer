// ----------------------------------------------------------------------
// -----------------------      SENSOR CLASS      -----------------------
// ----------------------------------------------------------------------

Sensor::Sensor(int pinSens_)
{
  this->pinSens = pinSens_;
}

void Sensor::begin()
{
  for (int i = 0; i < NSMOOTH; i++)
  {
    dataCollect[i] = 0;
  }
}

void Sensor::update()
{

  int sens_ = touchRead(this->pinSens);

  // FILL DATA WINDOW
  this->dataWindow[this->curWindowIndex] = sens_;
  this->curWindowIndex++;
  if (curWindowIndex > DATAWINDOW)
  {
    // get window range then reset
    this->meanWindow = getArrayMean(this->dataWindow, DATAWINDOW);
    this->maxWindow = getArrayMax(this->dataWindow, DATAWINDOW);
    this->threshold = 2.0 * (this->maxWindow - this->meanWindow + 1) + this->meanWindow; // add +1 to manage case max = mean
    this->curWindowIndex = 0;
  }

  // UPDATE COLLECTION
  for (int i = 0; i < NSMOOTH - 1; i++)
  {
    dataCollect[i] = dataCollect[i + 1];
  }
  dataCollect[NSMOOTH - 1] = sens_;
  this->rangeDataCollect = getArrayRange(this->dataCollect, NSMOOTH);

  // MOVING MEAN
  float mean_ = 0;
  for (int i = 0; i < NSMOOTH - this->offset; i++)
  {
    mean_ += dataCollect[i];
  }
  mean_ /= (NSMOOTH - this->offset);
  this->oldMean = this->curMean;
  this->curMean = mean_;

  // MOVING MEAN OFFSET
  mean_ = 0;
  for (int i = this->offset; i < NSMOOTH; i++)
  {
    mean_ += dataCollect[i];
  }
  mean_ /= (NSMOOTH - this->offset);
  this->oldOffsetMean = this->curOffsetMean;
  this->curOffsetMean = mean_;

//  // Calculate derivate
//  if (millis() % 50 == 0) {
//    float derivate_ = (sens_ - oldVal) / float(millis() - timerDeriv);
//    oldVal = curVal;
//    curVal = sens_;
//    timerDeriv = millis();
//    Serial.print(derivate_);
//  }

  // GOOD
  Serial.print(this->curMean);
  Serial.print('\t');
  Serial.print(this->curOffsetMean);
  // Serial.print('\t');

  // Serial.print(this->rangeDataCollect + 600);
  // Serial.print('\t');

  // Serial.print(this->meanWindow);
  // Serial.print('\t');
  // Serial.print(this->threshold);
  // Serial.print('\t');

  // RESULT
  if (this->getTouched())
  {
    // Serial.print(750);

    // Serial.print(this->pinSens);

    // this->meanWindow = getArrayMean(this->dataWindow, this->curWindowIndex);
    // this->maxWindow = getArrayMax(this->dataWindow, this->curWindowIndex);
    // this->threshold = 1.0 * (this->maxWindow - this->meanWindow) + this->meanWindow;
    this->curWindowIndex = 0; // reset window
  }
  else
  {
    // Serial.print(640);
    // Serial.print(-1);
  }
}

boolean Sensor::getTouched()
{
  boolean isTch_ = false;
  if (this->rangeDataCollect > 5)
  {
    if (this->oldOffsetMean < this->oldMean && this->curMean <= this->curOffsetMean)
    {
      isTch_ = true;
    }
  }
  return isTch_;
}
