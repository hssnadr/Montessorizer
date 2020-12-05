#include "ColorSwatch.h"
#include "SensorsManager.h"
#include "Ledstrip.h"

SensorsManager sensorsManager = SensorsManager();
Ledstrip stripA = Ledstrip(12, NPIXA);

float progression = 0.0f;
unsigned int gateTimeSensors = 0;
unsigned int gateTimeLedstrip = 0;

// --------------------------------------------------------------------------------
//                                   MAIN
// --------------------------------------------------------------------------------
void setup()
{
  sensorsManager.begin();
  stripA.begin();
  Serial.begin(57600);
}
void loop()
{
  // SENSORS
  if (millis() % 100 == 0 && millis() != gateTimeSensors)
  {
    gateTimeSensors = millis();
    sensorsManager.update();
    progression = sensorsManager.getProgression();
  } 

  progression = 50;   

  // LEDSTRIP
  if (millis() % 5 == 0 && millis() != gateTimeLedstrip)
  {
    gateTimeLedstrip = millis() ;
    stripA.setLightPath(progression, BLUE);
    stripA.show();
  }
}
