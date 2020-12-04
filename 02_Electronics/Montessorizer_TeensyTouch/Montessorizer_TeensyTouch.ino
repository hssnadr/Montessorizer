#include "Arduino.h"
#include "Utilities.h"
#include "Sensor.h"
// #include "Ledstrip.h"

// --------------------------------------------------------------------------------
//                            VARIABLES DECLARATION
// --------------------------------------------------------------------------------
// SENSORS
#define DATAWINDOW 3
unsigned int gate = 0;

float dataWindow[DATAWINDOW];
int curWindowIndex = 0;
float maxWindow = -666666.6f;
float threshold = -666666.6f;
float threshold0 = -666666.6f;
float dThreshold = 0.0f;
float dThreshold0 = 0.0f;
boolean isTouch = false;

Sensor sensor1 = Sensor(0);
Sensor sensor2 = Sensor(1);
Sensor sensor3 = Sensor(23);
int curSensor = -1; // Current sensor index
int nSensors = 4;

//LED STRIP
// Ledstrip stripA = Ledstrip();
int progression = 0;

// --------------------------------------------------------------------------------
//                                   MAIN
// --------------------------------------------------------------------------------
void setup()
{
  // SENSORS
  sensor1.begin(); // useless ?
  sensor2.begin();
  sensor3.begin();
  for (int i = 0; i < DATAWINDOW; i++)
  {
    dataWindow[i] = 0;
  }

  // LEDSTRIP
  // strip.begin(); // This initializes the NeoPixel library.
  // strip.show(); // Initialize all pixels to 'off'

  Serial.begin(57600);
}

void loop()
{
  // SENSORS
  if (millis() % 100 == 0 && millis() != gate)
  {
    gate = millis();

    sensor1.update();
    sensor2.update();
    sensor3.update();

    float __sensX[3] = {sensor1.getSensorVal(), sensor2.getSensorVal(), sensor3.getSensorVal()};
    float __sumX = sumArray(__sensX, 3);

    // FILL DATA WINDOW (with sensX)
    dataWindow[curWindowIndex] = __sumX;
    curWindowIndex++;
    if (curWindowIndex >= DATAWINDOW)
    {
      maxWindow = getFloatsMax(dataWindow, DATAWINDOW); // get max on data window
      curWindowIndex = 0;
    }

    // Update threshold
    if (threshold < maxWindow)
    {
      threshold0 = threshold;
      threshold = maxWindow;

      if ((threshold > 0 && threshold0 > 0) || threshold > abs(2 * threshold0))
      {
        dThreshold0 = dThreshold;
        dThreshold = threshold - threshold0;
      }
    }

    // Compare value & treshold
    if (dThreshold > dThreshold0 && dThreshold0 > 0)
    {
      if (dThreshold - dThreshold0 > 5)
      {
        isTouch = true;
      }
    }

    // Reset threshold
    if (threshold - maxWindow > 100 || maxWindow < -0.5 * threshold)
    {
      threshold = maxWindow;
      threshold0 = 0;  // force value
      dThreshold = 0;  // force value
      dThreshold0 = 0; // force value
      isTouch = false;
    }

    // CHECK SENSORS & UPDATE CURRENT INDEX
    if (isTouch)
    {
      int curMax_ = getMaxIndex(__sensX, 3);
      if (curSensor != curMax_)
      {
        curSensor = curMax_;
      }
    }
    else
    {
      curSensor = -1;
    }

    // Serial.print(__sensX[0]);
    // Serial.print('\t');
    // Serial.print(__sensX[1]);
    // Serial.print('\t');
    // Serial.print(__sensX[2]);
    // Serial.print('\t');

    Serial.print(dThreshold0);
    Serial.print('\t');
    Serial.print(dThreshold);
    Serial.print('\t');

    // Serial.print(maxWindow);
    // Serial.print('\t');
    // Serial.print(threshold);
    // Serial.print('\t');
    // Serial.print(-0.5 * threshold);
    // Serial.print('\t');

    Serial.print(curSensor + 1);
    Serial.print('\t');

    int __isTch = -20;
    if (isTouch)
    {
      __isTch = 20;
    }

    Serial.print(__isTch);
    Serial.print('\t');

    Serial.println();
  }

  // LEDSTRIP
  // curSensor++;
  // curSensor = curSensor % nSensors;
  // if(progression >= part2){
  //   curSensor += nSensors;
  // }
  
  // setLightPath(progression, blue);
  // strip.show();
  // delay(5);
}
