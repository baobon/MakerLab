#ifndef _VIETDUINO_ULTRASONIC_H_
#define _VIETDUINO_ULTRASONIC_H_
#include "Arduino.h"
#include "SimpleKalmanFilter.h"

class Vietduino_Ultrasonic {
  public:
    // Vietduino_Ultrasonic(unsigned int port, unsigned long maxdistance);    // Bao
    Vietduino_Ultrasonic(unsigned int port);                                  // kxn
    Vietduino_Ultrasonic(unsigned int _trig_pin_, unsigned int _echo_pin_);        // kxn
    virtual ~Vietduino_Ultrasonic() {
      if (kalman) {
        delete kalman;
      }
    }
    byte port;
    unsigned long maxDisTance;
    unsigned long Time;
    float Measurement;
    float getMeasure();
    void setMaxDistance(uint16_t _maxDistanceValue_);
    bool begin();
    bool stop();
  // private :
    unsigned long lastTimeRead;         // kxn
    unsigned int  intervalTime;         // kxn
    uint8_t trig_pin;                   // kxn
    uint8_t echo_pin;                   // kxn
    uint16_t timeOutPulIn;
    SimpleKalmanFilter *kalman;
};


#endif
