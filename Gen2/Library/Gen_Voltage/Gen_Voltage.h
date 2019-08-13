#ifndef _GEN_VOLTAGE_B_
#define _GEN_VOLTAGE_B_

#include "Arduino.h"

#define numReadings 20
#define inputPin A0
#define VALUECHANGE 14.14948225


class Gen_Voltage {
  public:
    Gen_Voltage();
    void begin();
    float readV();

    //Value
    unsigned char readIndex = 0; // the index of the current reading
    unsigned char tem_readIdex = 0;
    int readings[numReadings];
    unsigned long timer_VoltRaw_max = 100;
    unsigned long timer_VoltRaw = 0;
    float average = 0; // the average
    float last_Volt = 0;
    int total = 0;     // the running total
};

#endif
