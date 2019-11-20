#include "Gen_IO.h"

#ifndef _MY_MOTOR_DC_H_
#define _MY_MOTOR_DC_H_

#include "TwoMotor.h"

extern Vietduino_DCmotor motorLeft;
extern Vietduino_DCmotor motorRight;
extern TwoMotor myCar;


extern void runDCMotor(int direc, int speeds);

#endif