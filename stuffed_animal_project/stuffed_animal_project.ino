#include <MovingAverageFilter.hpp>

#define MAX_ANALOG_INPUT_VAL 600
#define MIN_ANALOG_INPUT_VAL 400

int pinOutLED= 11;
int pinInFSR= A0;
int sensorValue= 0;
int mappedValue= 0;

MovingAverageFilter _movingAverageFilter(10);

void setup() {
  Serial.begin(9600);
  pinMode(pinOutLED, OUTPUT);
  pinMode(pinInFSR, INPUT);
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
  Serial.println(mappedValue);
  delay(100); 
}
