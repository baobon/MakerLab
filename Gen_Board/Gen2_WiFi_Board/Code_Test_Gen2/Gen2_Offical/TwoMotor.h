#ifndef _TwoMotor_H_
#define _TwoMotor_H_
#include "Vietduino_DCmotor.h"

#define TWO_MOTOR_UP            (1)
#define TWO_MOTOR_DOWN          (0)

class TwoMotor{
  public:
  Vietduino_DCmotor * dcMotorL;
  Vietduino_DCmotor * dcMotorR;
  unsigned long timeOut;
  
  TwoMotor(Vietduino_DCmotor * _motorL,Vietduino_DCmotor * _motorR, unsigned long _timeOut);
  void up(unsigned char _speedInPercent_L,unsigned char _speedInPercent_R);
  void down(unsigned char _speedInPercent_L,unsigned char _speedInPercent_R);
};

#endif
