#ifndef _SENSORSMANAGER_H_
#define _SENSORSMANAGER_H_

#include "Utilities.h"
#include "Sensor.h"

#define DATAWINDOW 3
#define STEPSENSORS 30 // TO CHAA----------------------AAAANGE

class SensorsManager
{
public:
  SensorsManager();
  ~SensorsManager();
  void begin();
  void update();
  float getProgression();

private:
  float dataWindow[DATAWINDOW];
  int curWindowIndex = 0;
  float maxWindow = -666666.6f;
  float threshold = -666666.6f;
  float threshold0 = -666666.6f;
  float dThreshold = 0.0f;
  float dThreshold0 = 0.0f;
  boolean isTouch = false;
  boolean isTouchGate = false;

  int sensorPath[STEPSENSORS];
  int curSensPathIndex = 0;
  Sensor sensor1 = Sensor(15);
  Sensor sensor2 = Sensor(16);
  Sensor sensor3 = Sensor(17);
  int curSensor = -1; // Current sensor index
};

SensorsManager::SensorsManager()
{
}

SensorsManager::~SensorsManager()
{
}

void SensorsManager::begin()
{
  this->sensor1.begin(); // useless ?
  this->sensor2.begin();
  this->sensor3.begin();
  for (int i = 0; i < DATAWINDOW; i++)
  {
    this->dataWindow[i] = 0;
  }
}

void SensorsManager::update()
{

  this->sensor1.update();
  this->sensor2.update();
  this->sensor3.update();

  float __sensX[3] = {this->sensor1.getSensorVal(), this->sensor2.getSensorVal(), this->sensor3.getSensorVal()};
  float __sumX = sumArray(__sensX, 3);

  // FILL DATA WINDOW (with sensX)
  this->dataWindow[this->curWindowIndex] = __sumX;
  this->curWindowIndex++;
  if (this->curWindowIndex >= DATAWINDOW)
  {
    this->maxWindow = getFloatsMax(this->dataWindow, DATAWINDOW); // get max on data window
    this->curWindowIndex = 0;
  }

  // Update this->threshold
  if (this->threshold < this->maxWindow)
  {
    this->threshold0 = this->threshold;
    this->threshold = this->maxWindow;

    if ((this->threshold > 0 && this->threshold0 > 0) || this->threshold > abs(2 * this->threshold0))
    {
      this->dThreshold0 = this->dThreshold;
      this->dThreshold = this->threshold - this->threshold0;
    }
  }

  // Compare value & treshold
  if (this->dThreshold > this->dThreshold0 && this->dThreshold0 > 0)
  {
    if (this->dThreshold - this->dThreshold0 > 5)
    {
      this->isTouch = true;
    }
  }

  // Reset this->threshold
  if (this->threshold - this->maxWindow > 100 || this->maxWindow < -0.5 * this->threshold)
  {
    this->threshold = this->maxWindow;
    this->threshold0 = 0;  // force value
    this->dThreshold = 0;  // force value
    this->dThreshold0 = 0; // force value
    this->isTouch = false;
  }

  // CHECK SENSORS & UPDATE CURRENT INDEX
  if (this->isTouch)
  {
    int curMax_ = getMaxIndex(__sensX, 3);
    if (this->curSensor != curMax_)
    {
      this->curSensor = curMax_;
    }
  }
  else
  {
    this->curSensor = -1;
  }

  // SENSOR PATH INDEX
  if (this->isTouch != this->isTouchGate)
  {
    this->isTouchGate = this->isTouch;

    if (this->isTouch)
    {
      this->curSensPathIndex++;
      this->curSensPathIndex = this->curSensPathIndex % STEPSENSORS;
    }
    else
    {
      this->curSensPathIndex = 0;
    }
  }

  // Serial.print(__sensX[0]);
  // Serial.print('\t');
  // Serial.print(__sensX[1]);
  // Serial.print('\t');
  // Serial.print(__sensX[2]);
  // Serial.print('\t');

  Serial.print(this->dThreshold0);
  Serial.print('\t');
  Serial.print(this->dThreshold);
  Serial.print('\t');

  // Serial.print(this->maxWindow);
  // Serial.print('\t');
  // Serial.print(this->threshold);
  // Serial.print('\t');
  // Serial.print(-0.5 * this->threshold);
  // Serial.print('\t');

  Serial.print(this->curSensor + 1);
  Serial.print('\t');

  int __isTch = -20;
  if (this->isTouch)
  {
    __isTch = 20;
  }

  Serial.print(__isTch);
  Serial.print('\t');

  Serial.println();
}

float SensorsManager::getProgression()
{
  float __prog = 0.0f;
  // SENSOR PATH PROGRESSION
  if (this->curSensor == this->sensorPath[this->curSensPathIndex])
  {
    __prog = 100.0f * (float(this->curSensPathIndex) / STEPSENSORS);
  }
  else
  {
    __prog = 0;
  }

  return __prog;
}

#endif /* _SENSORSMANAGER_H_ */