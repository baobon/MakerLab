#ifndef _EXTEN_H_FUNCTION_H_
#define _EXTEN_H_FUNCTION_H_

#include "Vietduino_NewFunction.h"
#include "Vietduino_Led.h"
#include "Vietduino_DCmotor.h"
#include "Vietduino_Servo.h"

//      DEFINE_FUNCTION(ReadSerial);

extern Vietduino_Led      myBuzzer;
extern Vietduino_DCmotor myMotor;
extern Vietduino_Servo    myServo;
extern String c_buzzer, c_controller, c_speed;
extern String splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset);
void handlingdata(String data);

#endif
