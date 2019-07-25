/**
 * File: Vietduino_DCmotor.cpp
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_DCmotor is free software: you can redistribute it and/or modify
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

#include "Vietduino_DCmotor.h"
#include "Vietduino_Manager_Priority.h"

Vietduino_DCmotor::Vietduino_DCmotor(unsigned char _port_uno_base_):
    Vietduino_Task(0, &Vietduino_DCmotor::run){
    if(_port_uno_base_ == 1){       //LEFT Motor
        dir= 7;
        pwm= 6;
    }else if(_port_uno_base_ == 2){       //RIGHT Motor
        dir= 4;
        pwm= 5;
    }else;


    myBit_d = NK_PIN_TO_BITMASK(dir);          // get send pin's ports and bitmask
    myReg_d = NK_PIN_TO_BASEREG(dir);         // get pointer to output register

    pinMode(dir,OUTPUT);
    pinMode(pwm,OUTPUT);
    Vietduino_Manager_3.add(this);
}

Vietduino_DCmotor::Vietduino_DCmotor(unsigned char _dir_, unsigned char _speed_):
    Vietduino_Task(0, &Vietduino_DCmotor::run){
    dir= _dir_;
    pwm= _speed_;

    myBit_d = NK_PIN_TO_BITMASK(dir);          // get send pin's ports and bitmask
    myReg_d = NK_PIN_TO_BASEREG(dir);         // get pointer to output register

    pinMode(dir,OUTPUT);
    pinMode(pwm,OUTPUT);
    Vietduino_Manager_3.add(this);
}

void Vietduino_DCmotor::forward(unsigned char s){
    if(uc_Last_Dir_Val == _V_DIR_BACKWARD_){
        NK_DIRECT_WRITE_HIGH(myReg_d, myBit_d);
        uc_Last_Dir_Val = _V_DIR_FORWARD_;
    }

    if(uc_Last_Pwm_Val != s){
        analogWrite(pwm, 255 - s);
        uc_Last_Pwm_Val = s;
    }

}
void Vietduino_DCmotor::backward(unsigned char s){
    if(uc_Last_Dir_Val == _V_DIR_FORWARD_){
        NK_DIRECT_WRITE_LOW(myReg_d, myBit_d);
        uc_Last_Dir_Val = _V_DIR_BACKWARD_;
    }

    if(uc_Last_Pwm_Val != s){
        analogWrite(pwm,s);
        uc_Last_Pwm_Val = s;
    }

}

void Vietduino_DCmotor::stop(){
    if(uc_Last_Dir_Val == _V_DIR_FORWARD_){
        forward(0);
    }else{
        backward(0);
    }

    ul_timeRun = 0;
    _loopID_ = 0;
    setPeriodUs(0);
}

void Vietduino_DCmotor::write(unsigned char _dir_, unsigned char _speed_){
    if(_speed_ == 0){
        stop();
    }else{
        if(_dir_ == HIGH){
            forward(_speed_);
        }
        else if(_dir_ == LOW){
            backward(_speed_);
        }
    }

}

void Vietduino_DCmotor::write(unsigned char _dir_, unsigned char _speed_, unsigned long _runForMs_)
{
    write(_dir_, _speed_);
    ul_timeRun = _runForMs_;
    _loopID_ = 0;
    setPeriodUs(0);
}

void Vietduino_DCmotor::run(Vietduino_Task *me){
    Vietduino_DCmotor * te = (Vietduino_DCmotor*) me;
    if(te->_loopID_ == 0){
        if(te->ul_timeRun > 0){
            te->_loopID_ = 1;
            te->setPeriodUs(te->ul_timeRun * 1000);
        }
    }else if(te->_loopID_ == 1){
        te->stop();
//        te->ul_timeRun = 0;
//        te->_loopID_ = 0;
//        te->setPeriodUs(0);
    }else;
}
 
