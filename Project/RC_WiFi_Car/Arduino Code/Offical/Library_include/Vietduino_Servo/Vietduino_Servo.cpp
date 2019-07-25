/**
 * File: Vietduino_Servo.cpp
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

#include "Vietduino_Servo.h"
#include "Vietduino_Manager_Priority.h"

// ----- Initialization and Default Values -----

Vietduino_Servo::Vietduino_Servo():
    Vietduino_Task(30, &Vietduino_Servo::tick){
    Vietduino_Manager_3.add(this);
}

Vietduino_Servo::Vietduino_Servo(int _pin_):
    Vietduino_Task(30, &Vietduino_Servo::tick){

    myservo = new(Servo);
    myservo->attach(_pin_);
    posNeed = 0;
    pos = 0;
    Servo_speed = _MIN_SPEED_VALUE_;
    lastpos = 0;

    Vietduino_Manager_3.add(this);
    
}

Vietduino_Servo::~Vietduino_Servo(){

}

void Vietduino_Servo::begin(int pin)
{
    myservo = new(Servo);
    myservo->attach(pin);
    posNeed = 0;
    pos = 0;
    Servo_speed = _MIN_SPEED_VALUE_;
    lastpos = 0;
}

void Vietduino_Servo::begin(int pin, ServoWrite_pf _servowrite_f_)
{
    ui8_servoPin = pin;
    pf_serWrite = _servowrite_f_;
}

void Vietduino_Servo::write(unsigned char _Angle_, unsigned char _speed_){
    checkValid_Angel(_Angle_);

    if(SERVO_MAP_SPEED(_speed_) >= _MAX_SPEED_VALUE_){
        Servo_speed = _MAX_SPEED_VALUE_;
    }else if(SERVO_MAP_SPEED(_speed_) <= _MIN_SPEED_VALUE_){
        Servo_speed = _MIN_SPEED_VALUE_;
    }else{
        Servo_speed = SERVO_MAP_SPEED(_speed_);
    }
}

void Vietduino_Servo::write(unsigned char _Angle_)
{
    write(_Angle_, 100);
}

void Vietduino_Servo::write_for(float _Angle_, unsigned long _time_in_ms_)
{
    // Lay so lan chay
    float tem_num_time_run = _time_in_ms_ / time_interval;
    if(tem_num_time_run < 1) tem_num_time_run = 1;
    // Lay goc quay chia deu cho so lan chay => goc gia
    checkValid_Angel(_Angle_);

    Servo_speed = abs(_Angle_ - (float)lastpos)/tem_num_time_run;
}

void Vietduino_Servo::Servo_write(unsigned char _Angle_)
{
    if(this->myservo){
        this->myservo->write(_Angle_);
    } 

    if(this->pf_serWrite) this->pf_serWrite(ui8_servoPin, _Angle_);
}

void Vietduino_Servo::attachWrite(ServoWrite_pf _servowrite_f_)
{
    pf_serWrite = _servowrite_f_;
}

bool Vietduino_Servo::available()
{
    return (lastpos == posNeed);
}

void Vietduino_Servo::checkValid_Angel(unsigned char _Angle_)
{
    if(_Angle_ >= _MAX_ANGLE_VALUE_){
        posNeed = _MAX_ANGLE_VALUE_;
    }else if(_Angle_ <= _MIN_ANGLE_VALUE_){
        posNeed = _MIN_ANGLE_VALUE_;
    }else{
        posNeed = _Angle_;
    }
}

void Vietduino_Servo::tick(Vietduino_Task * me)
{
    Vietduino_Servo *tem = (Vietduino_Servo*) me;
    
    if(tem->posNeed > tem->pos){
      tem->pos += tem->Servo_speed;
      if((tem->pos > tem->posNeed) || (tem->Servo_speed == _MAX_SPEED_VALUE_)){
        tem->pos = tem->posNeed;
      }
    }else if(tem->posNeed < tem->pos){
      tem->pos -= tem->Servo_speed;
      if((tem->pos < tem->posNeed) || (tem->Servo_speed == _MAX_SPEED_VALUE_)){
        tem->pos = tem->posNeed;
      }
    }else;
    if(tem->lastpos != tem->pos){
      tem->Servo_write(tem->pos);
      tem->lastpos = tem->pos;
      
    }

}

// end.

