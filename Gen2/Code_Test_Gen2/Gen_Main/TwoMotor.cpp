#include "TwoMotor.h"

TwoMotor::TwoMotor(Vietduino_DCmotor * _motorL,Vietduino_DCmotor * _motorR, unsigned long _timeOut){
  dcMotorL = _motorL;
  dcMotorR = _motorR;
  timeOut = _timeOut;
}

void TwoMotor::up(unsigned char _speedInPercent_L,unsigned char _speedInPercent_R){
  this->dcMotorL->write(TWO_MOTOR_UP, _speedInPercent_L, this->timeOut);
  this->dcMotorR->write(TWO_MOTOR_UP, _speedInPercent_R, this->timeOut);
}

void TwoMotor::down(unsigned char _speedInPercent_L,unsigned char _speedInPercent_R){
  this->dcMotorL->write(TWO_MOTOR_DOWN, _speedInPercent_L, this->timeOut);
  this->dcMotorR->write(TWO_MOTOR_DOWN, _speedInPercent_R, this->timeOut);
}