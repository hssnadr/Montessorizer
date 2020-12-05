#include "SensorsManager.h"
#include "Ledstrip.h"

// --------------------------------------------------------------------------------
//                            VARIABLES DECLARATION
// --------------------------------------------------------------------------------
// SENSORS
SensorsManager sensorsManager = SensorsManager();

//LED STRIP
Ledstrip stripA = Ledstrip(12, NPIXA);
int progression = 0;

// --------------------------------------------------------------------------------
//                                   MAIN
// --------------------------------------------------------------------------------
void setup()
{
  // SENSORS
  sensorsManager.begin();

  // LEDSTRIP
  stripA.begin();

  Serial.begin(57600);
}

void loop()
{
  // SENSORS
  sensorsManager.update();
  progression = sensorsManager.getProgression();

  // LEDSTRIP
  if (millis() % 5 == 0)
  {
    // curSensor++;
    // curSensor = curSensor % nSensors;
    // if(progression >= part2){
    //   curSensor += nSensors; ?????????????????????????????????????????????????
    // }

    // progression =

    progression = 0.5f;

    stripA.setLightPath(progression, BLUE);
    stripA.show();
  }
}
