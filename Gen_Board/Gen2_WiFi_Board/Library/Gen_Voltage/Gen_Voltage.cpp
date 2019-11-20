#include "Gen_Voltage.h"

Gen_Voltage::Gen_Voltage() {

}

void Gen_Voltage::begin(){
  pinMode(inputPin,INPUT);
}


float Gen_Voltage::readV() {
  if (millis() - timer_VoltRaw >= timer_VoltRaw_max)
  {
    float val = 0;
    timer_VoltRaw = millis();
    total = total - readings[readIndex];
    // read from the sensor:
    readings[readIndex] = analogRead(inputPin);
    // add the reading to the total:
    total = total + readings[readIndex];
    // advance to the next position in the array:
    readIndex = readIndex + 1;
    tem_readIdex++;
    // if we're at the end of the array...
    if (readIndex >= numReadings)
    {
      // ...wrap around to the beginning:
      readIndex = 0;
    }
    if (tem_readIdex >= numReadings)
    {
      tem_readIdex = numReadings;
    }
    average = total / tem_readIdex;
    last_Volt = average / 1023 * VALUECHANGE;
  }
  return last_Volt;
}
