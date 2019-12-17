#define NSMOOTH 10  // number of input to compute moving mean
#define NSMOOTH2 50

class Sensor
{
  public:
    Sensor(int pinSens_);
    void begin();
    void update();
    boolean isTouched();

  private:
    int pinSens;
    int dataCollect[NSMOOTH];
    int dataCollect2[NSMOOTH2];
    int curSmthVal1 = 0;
    int oldSmthVal1 = 0;
    int curSmthVal2 = 0;
    int oldSmthVal2 = 0;
    float curMean = 0;
    float curMean2 = 0;
    int timerDeriv = 0; // use to calculate derivate
};

//Sensor sensor1 = Sensor(0);
//Sensor sensor2 = Sensor(1);
Sensor sensor3 = Sensor(2);

void setup() {
  //sensor1.begin(); // useless ?
  //sensor2.begin();
  sensor3.begin();

  Serial.begin(9600);
}

void loop() {
  //sensor1.update();
  //sensor2.update();
  sensor3.update();

  //  if(sensor1.isTouched()){
  //    Serial.print(600);
  //  }
  //  else{
  //    Serial.print(500);
  //  }


  Serial.println("");
}
