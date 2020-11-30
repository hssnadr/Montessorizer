#define NRAW 40 // number of input to compute moving mean
#define NMEAN 3
#define DATAWINDOW 3

// ----------------------------------------------------------------------
// -----------------------      CLASS DEF       -------------------------
// ----------------------------------------------------------------------

class Sensor
{
public:
  Sensor(int pinSens_);
  void begin();
  void update();
  boolean isTouched = false;
  float getSensorVal();
  float getSensorRange();

private:
  int pinSens;
  int dataCollect[NRAW];
  float rangeDataCollect = 0;
  float meanCollect[NRAW];

  int dataWindow[DATAWINDOW];
  int curWindowIndex = 0;
  float meanWindow = 0.0f;
  int maxWindow = 700; //1024; // init at max
  // int maxWindow = 0;    // init at min
  float threshold = 700; //1024.0f;

  boolean getTouched();
};

// ----------------------------------------------------------------------
// -------------------------      MAIN       ----------------------------
// ----------------------------------------------------------------------

int gate = 0;

float dataWindow[DATAWINDOW];
int curWindowIndex = 0;
float maxWindow = -666666.6f;
float threshold = -666666.6f;
boolean isTouch = false;

Sensor sensor1 = Sensor(0);
Sensor sensor2 = Sensor(1);
Sensor sensor3 = Sensor(23);

void setup()
{
  sensor1.begin(); // useless ?
  sensor2.begin();
  sensor3.begin();

  for (int i = 0; i < DATAWINDOW; i++)
  {
    dataWindow[i] = 0;
  }

  Serial.begin(57600);
}

void loop()
{
  if (millis() % 100 == 0 && millis() != gate)
  {
    gate = millis();

    sensor1.update();
    Serial.print('\t');

    sensor2.update();
    Serial.print('\t');

    sensor3.update();
    Serial.print('\t');

    float __sens1 = sensor1.getSensorVal();
    float __sens2 = sensor2.getSensorVal();
    float __sens3 = sensor3.getSensorVal();

    float __sensX = __sens1 + __sens2 + __sens3;
    // Serial.print(__sensX);
    // Serial.print('\t');
    
    // FILL DATA WINDOW (with sensX)
    dataWindow[curWindowIndex] = __sensX;
    curWindowIndex++;
    if (curWindowIndex >= DATAWINDOW)
    {
      maxWindow = getFloatsMax(dataWindow, DATAWINDOW);
      curWindowIndex = 0;
    }

    // Update threshold
    if(threshold < maxWindow) {
      threshold = maxWindow;
    }
    // Reset threshold
    if(threshold - maxWindow > 100 || maxWindow < -0.5*threshold) {
      threshold = maxWindow;
      isTouch = false;
    }

    // Compare value & treshold
    if(maxWindow > 10 * threshold) {
      isTouch = true;
    }
    
    Serial.print(maxWindow);
    Serial.print('\t');
    Serial.print(threshold);
    Serial.print('\t');
    // Serial.print(-0.5*threshold);
    // Serial.print('\t');
    // if(isTouch) {
    //   Serial.print(1.5*threshold);
    // } else {
    //   Serial.print(-1.5*threshold);
    // }
    Serial.print(isTouch == true);
    Serial.print('\t');
    

    //  float __rang1 = sensor1.getSensorRange();
    //  float __rang2 = sensor2.getSensorRange();
    //  float __rang3 = sensor3.getSensorRange();
    //  float __rangX = sqrt(pow(__rang1,2) + pow(__rang2,2) + pow(__rang3,2));
    //  Serial.print(__rangX);

    Serial.println();
  }
}
