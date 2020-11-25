#define NSMOOTH 80 // number of input to compute moving mean
// #define NSMOOTH2 50
#define DATAWINDOW 50

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

private:
  int pinSens;
  int dataCollect[NSMOOTH];
  float rangeDataCollect = 0;

  int dataWindow[DATAWINDOW];
  int curWindowIndex = 0;
  float meanWindow = 0.0f;
  int maxWindow = 700; //1024; // init at max
  // int maxWindow = 0;    // init at min
  float threshold = 700; //1024.0f;

  float curMean = 0;
  float oldMean = 0;

  int offset = 3;
  float curOffsetMean = 0;
  float oldOffsetMean = 0;
  // int timerDeriv = 0; // use to calculate derivate
  boolean getTouched();
};

// ----------------------------------------------------------------------
// -------------------------      MAIN       ----------------------------
// ----------------------------------------------------------------------

Sensor sensor1 = Sensor(0);
Sensor sensor2 = Sensor(1);
Sensor sensor3 = Sensor(23);

void setup()
{
  sensor1.begin(); // useless ?
  sensor2.begin();
  sensor3.begin();

  Serial.begin(57600);
}

void loop()
{
  if (millis() % 20 == 0)
  {
    sensor1.update();
    Serial.print('\t');
    
    sensor2.update();
    Serial.print('\t');
    
    sensor3.update();
    Serial.print('\t');
    
    Serial.println();
  }
}
