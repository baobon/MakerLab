/*
  Made by MakerShop.vn

  Tool Board : ESP8266 Generic Module
  FlashSize : 1M(No SPIFFS)

  Pin Board in TestGen2_IO.h

  Test:
      Servo 1 , 2
      DC Motor 1 , Dc Motor 2
      Uart

  Set GPIO0 -> GND to update code !
  Normal run !

  **** Ket qua test 
  * Min Speed 350 
  * Max Speed 1023
  * 
  
*/


#include "Vietduino_Manager.h"
#include "Vietduino_NewFunction.h"
#include "TestGen2_IO.h"
#include "Vietduino_Servo.h"
Vietduino_Servo servo_one;
Vietduino_Servo servo_two;
int voltage;
int Speed = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {

  }
  pinMode(PWM_ONE, OUTPUT);
  pinMode(PWM_TWO, OUTPUT);
  pinMode(DIR_ONE, OUTPUT);
  pinMode(DIR_TWO, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  VIETDUINO_UPDATE;
}

void goT() {
//  Serial.println("Tien");
  analogWrite(PWM_ONE, Speed);
  analogWrite(PWM_TWO, Speed);
  analogWrite(DIR_ONE, 0);
  analogWrite(DIR_TWO, 0);
}
void goL() {
  //  Serial.println("Lùi");
  analogWrite(PWM_ONE, Speed);
  analogWrite(PWM_TWO, Speed);
  analogWrite(DIR_ONE, 0);
  analogWrite(DIR_TWO, 0);
}
void Stop() {
  //  Serial.println("Stop");
  analogWrite(PWM_ONE, 0);
  analogWrite(PWM_TWO, 0);
}


CREATE_FUNCTION(MotorTest) {
    goT();
    //    M_DELAY(2000);
    //    Stop();
    //    M_DELAY(2000);
    //    goL();
    //    M_DELAY(2000);
    //    Stop();
    M_DELAY(1);
  END_CREATE_FUNCTION
}


CREATE_FUNCTION(ServoTest) {
  servo_one.begin(SERVO_ONE);
  servo_two.begin(SERVO_TWO);
  while (1) {
    //    Serial.println("Run Servo");
    servo_one.write_for(0, 1000);
    servo_two.write_for(180, 1000);
    M_DELAY(2000);
    servo_two.write_for(0, 1000);
    servo_one.write_for(180, 1000);
    M_DELAY(2000);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}


CREATE_FUNCTION(ReadBaterry) {
  voltage = map(analogRead(A0),0,1023,0,1000);
  Serial.println(voltage);
  voltage = analogRead(A0)/1023*18.56;
  Serial.print("Demo ");;
  Serial.println(voltage);
  M_DELAY(100);
  END_CREATE_FUNCTION
}


CREATE_FUNCTION(UartTest) {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Speed = command.toInt();
    Serial.println(Speed);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}
