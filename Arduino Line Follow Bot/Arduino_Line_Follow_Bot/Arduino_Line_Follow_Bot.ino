/*
    Creator: QuocBao
    Robot Follow Line Source Code 
      + Vietduino-Uno
      + L298
      + Simple Line Sensor

*/


#include "Line_Follow_IO.h"

int b_speed_left = 0;
int b_speed_right = 100;
int lastvalue;
int value;

void setup()
{
  Serial.begin(115200);
  pinModes();
}

void loop()
{
  // goL();
  //  goFR();

  // Serial.println("Left sensor = " + String(analogRead(Sensor_Left)) +
  //                "  Right sensor = " + String(analogRead(Sensor_Right)));
  Run();
  // delay(50);
}

void pinModes()
{
  pinMode(IN_1, OUTPUT);
  pinMode(IN_2, OUTPUT);
  pinMode(IN_3, OUTPUT);
  pinMode(IN_4, OUTPUT);
  pinMode(Sensor_Right, INPUT);
  pinMode(Sensor_Left, INPUT);
}

void goStop()
{
  analogWrite(IN_1, 0);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, 0);
  analogWrite(IN_4, 0);
}

void goFF()
{
  digitalWrite(IN_1, 1);
  analogWrite(IN_2, 255 - b_speed_right);
  analogWrite(IN_3, 255 - b_speed_right);
  digitalWrite(IN_4, 1);
}

void goFR()
{
  digitalWrite(IN_1, 0);
  analogWrite(IN_2, 0);
  analogWrite(IN_3, 255 - b_speed_right);
  digitalWrite(IN_4, 1);
}

void goFL()
{
  digitalWrite(IN_1, 1);
  analogWrite(IN_2, 255 - b_speed_right);
  analogWrite(IN_3, 0);
  digitalWrite(IN_4, 0);
}

void goL()
{
  digitalWrite(IN_1, 1);
  analogWrite(IN_2, 255 - b_speed_right);
  analogWrite(IN_3, b_speed_right);
  digitalWrite(IN_4, 0);
}

void goR()
{
  digitalWrite(IN_1, 0);
  analogWrite(IN_2, b_speed_right);
  analogWrite(IN_3, 255 - b_speed_right);
  digitalWrite(IN_4, 1);
}

void ReadSensor()
{
  if (analogRead(Sensor_Right) <= 50 && analogRead(Sensor_Left) <= 50)
  {
    value = lastvalue;
  }
  else
  {
    if (analogRead(Sensor_Right) >= 600 && analogRead(Sensor_Left) >= 600)
    {
      // goFF();
      value = 1500;
    }
    else
    {
      if (analogRead(Sensor_Right) <= 300 && analogRead(Sensor_Left) >= 600)
      {
        // goFL();
        value = 0;
        lastvalue = 0;
      }
      else
      {
        if (analogRead(Sensor_Right) >= 600 && analogRead(Sensor_Left) <= 300)
        {
          // goFR();
          value = 3000;
          lastvalue = 3000;
        }
      }
    }
  }
}

void Run()
{
  ReadSensor();
  if (value > 1500)
  {
    if (value == 3000)
    {
      goR();
    }
    else
    {
      goFL();
    }
  }
  else
  {
    if (value < 1500)
    {
      if (value == 0)
      {
        goL();
      }
      else
      {
        goFR();
      }
    }
    else
    {
      if (value = 1500)
      {
        goFF();
      }
    }
  }
}
