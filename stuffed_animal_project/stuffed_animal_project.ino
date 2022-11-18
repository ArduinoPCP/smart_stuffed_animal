#include <MovingAverageFilter.hpp>

#define MAX_ANALOG_INPUT_VAL 600
#define MIN_ANALOG_INPUT_VAL 400

int pinInFSR= A0;
int sensorValue= 0;
int mappedValue= 0;

const int GREEN = 9;  
const int BLUE = 10;  
const int RED = 11;  

MovingAverageFilter _movingAverageFilter(10);

void setup() {

  Serial.begin(9600);
  pinMode(pinInFSR, INPUT);

  pinMode(GREEN, OUTPUT);  
  pinMode(BLUE, OUTPUT);  
  pinMode(RED, OUTPUT);  
}

void rgbFunction(int red, int green, int blue) {
    analogWrite(RED, red);
    analogWrite(GREEN, green);
    analogWrite(BLUE, blue);
}

void loop() {

  sensorValue= analogRead(pinInFSR); 
  _movingAverageFilter.add(sensorValue);
  int smoothedVal = _movingAverageFilter.getAverage();

  mappedValue= map(smoothedVal, MIN_ANALOG_INPUT_VAL, MAX_ANALOG_INPUT_VAL, 0, 255);
  if (mappedValue<=0)
    mappedValue=0;
  if (mappedValue>=255)
    mappedValue = 255;

  if (mappedValue<=85)
    rgbFunction(mappedValue, 0, 0);
  else if (mappedValue<=170)
    rgbFunction(0, mappedValue, 0);
  else
    rgbFunction(0, 0, mappedValue);

  Serial.println(mappedValue);
  delay(100); 
}
