#include "Debug_Program.h"

#if defined(RUN_MOTOR_DC)

#ifndef _MY_MOTOR_DC_H_
#define _MY_MOTOR_DC_H_

#include "TwoMotor.h"

extern Vietduino_DCmotor motorLeft;
extern Vietduino_DCmotor motorRight;
extern TwoMotor myCar;


extern void runDCMotor(int direc, int speeds);

#endif
#else


#endif
