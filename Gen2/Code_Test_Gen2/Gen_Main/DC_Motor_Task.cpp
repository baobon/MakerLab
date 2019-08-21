
#include "DC_Motor_Task.h"

#if defined(RUN_MOTOR_DC)

#include "Gen_Debug.h"
#include "Vietduino_NewFunction.h"

Vietduino_DCmotor motorLeft(LEFT_MOTOR);
Vietduino_DCmotor motorRight(RIGHT_MOTOR);

TwoMotor myCar(&motorLeft, &motorRight, 1000);

//CREATE_FUNCTION(testCarMotor){
//  myCar.up(100,50);
//  M_DELAY(3000);
//  myCar.up(100,30);
//  M_DELAY(3000);
//  myCar.up(30,100);
//  M_DELAY(3000);
//  END_CREATE_FUNCTION
//}

void runDCMotor(int direc, int speeds) {
  switch (direc) {
    case 1:
      myCar.up(0,speeds);
      GEN_PRINTLN("Left");
      break;
    case 2:
      myCar.up(speeds,0);
      GEN_PRINTLN("Right");
      break;
    case 3:
      myCar.up(speeds,speeds);
      GEN_PRINTLN("Forward");
      break;
    case 4:
      myCar.down(speeds,speeds);
      GEN_PRINTLN("Backward");
      break;
    default:
      GEN_PRINTLN("Stop");
      myCar.up(0,0);
      break;
  }
}

#else
 #define  runDCMotor(direc, speeds)  
#endif