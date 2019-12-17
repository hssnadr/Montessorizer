Sensor::Sensor(int pinSens_) {
  this->pinSens = pinSens_;
}

void Sensor::begin() {
  for (int i = 0; i < NSMOOTH; i++) {
    dataCollect[i] = 0;
  }
}

void Sensor::update() {
  if (millis() % 25 == 0) {
    // Get value
    int sens_ = analogRead(this->pinSens);

    // Update data collection 1
    for (int i = 0; i < NSMOOTH - 1; i++) {
      dataCollect[i] = dataCollect[i + 1];
    }
    dataCollect[NSMOOTH - 1] = sens_;

    // Update data collection 2
    for (int i = 0; i < NSMOOTH2 - 1; i++) {
      dataCollect2[i] = dataCollect2[i + 1];
    }
    dataCollect2[NSMOOTH2 - 1] = sens_;

    // Calculate moving mean
    float mean_ = 0;
    for (int i = 0; i < NSMOOTH; i++) {
      mean_ += dataCollect[i];
    }
    mean_ /= NSMOOTH;
    this->curMean = mean_;

    mean_ = 0;
    for (int i = 0; i < NSMOOTH2; i++) {
      mean_ += dataCollect2[i];
    }
    mean_ /= NSMOOTH2;
    this->curMean2 = mean_;

    oldSmthVal1 = curSmthVal1;
    curSmthVal1 = this->curMean;

    oldSmthVal2 = curSmthVal2;
    curSmthVal2 = this->curMean2;

    // Calculate derivate
    //  if (millis() % 50 == 0) {
    //    float derivate_ = (sens_ - oldVal) / float(millis() - timerDeriv);
    //    oldVal = curVal;
    //    curVal = sens_;
    //    timerDeriv = millis();
    //    Serial.print(derivate_);
    //  }


    Serial.print(this->curMean);
    Serial.print('\t');
    Serial.print(this->curMean2);
    Serial.print('\t');

    if (this->isTouched()) {
      Serial.print(600);
    }
    else {
      Serial.print(500);
    }
  }
}

boolean Sensor::isTouched() {
  boolean isTch_ = false;
  if (this->oldSmthVal2 <= this->oldSmthVal1 && this->curSmthVal1 < this->curSmthVal2) {
    isTch_ = true;
  }
  return isTch_;
}
