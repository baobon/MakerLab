/**
 * File: Vietduino_Servo.h
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_Servo is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/

#ifndef _VIETDUINO_SERVO_H_
#define _VIETDUINO_SERVO_H_

#include "Arduino.h"
#include "Vietduino_Task.h"
#include <Servo.h>

#define _VIETDUINI_SERVO_VER        2.0
#define _VIETDUINO_SERVO_DATE       270618

#define _MAX_ANGLE_VALUE_       180
#define _MIN_ANGLE_VALUE_       0

#define _MAX_SPEED_VALUE_       9
#define _MIN_SPEED_VALUE_       1
#define SERVO_MAP_SPEED_X(x, y)         map(x,0,100,0,y)
#define SERVO_MAP_SPEED(x)              SERVO_MAP_SPEED_X(x,_MAX_SPEED_VALUE_)

extern "C" {
    typedef void (*ServoWrite_pf)(int pin, unsigned char _angel_);
}

class Vietduino_Servo: public Vietduino_Task
{
public:
  // ----- Constructor -----
    Vietduino_Servo();
    Vietduino_Servo(int _pin_);
    virtual ~Vietduino_Servo();

    void begin(int pin);
    void begin(int pin, ServoWrite_pf _servowrite_f_);

    // ----- Set runtime parameters -----
    static void tick(Vietduino_Task * me);
    void write(unsigned char _Angle_, unsigned char _speed_);
    void write(unsigned char _Angle_);
    void write_for(float _Angle_, unsigned long _time_in_ms_);
    virtual void Servo_write(unsigned char _Angle_);
    void attachWrite(ServoWrite_pf _servowrite_f_);

    // Return true when Servo stop
    bool available();

private:
    Servo * myservo;
    int posNeed, pos, Servo_speed, lastpos;
    unsigned long time_interval = 30;
    ServoWrite_pf  pf_serWrite;

    void checkValid_Angel(unsigned char _Angle_);
    uint8_t ui8_servoPin;
};

#endif


