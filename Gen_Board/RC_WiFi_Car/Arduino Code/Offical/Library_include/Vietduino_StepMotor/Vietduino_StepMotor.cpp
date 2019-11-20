/**
 * File: Vietduino_StepMotor.cpp
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_StepMotor is free software: you can redistribute it and/or modify
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

#include "Vietduino_StepMotor.h"
#include "Vietduino_Manager.h"

Vietduino_StepMotor::Vietduino_StepMotor(unsigned char _pinA_, unsigned char _pinB_, unsigned char _pinC_, unsigned char _pinD_):
    Vietduino_Task(0, &Vietduino_StepMotor::run)
{
    pinMode(_pinA_, OUTPUT);
    pinMode(_pinB_, OUTPUT);
    pinMode(_pinC_, OUTPUT);
    pinMode(_pinD_, OUTPUT);

    myBit_a = NK_PIN_TO_BITMASK(_pinA_);          // get send pin's ports and bitmask
    myReg_a = NK_PIN_TO_BASEREG(_pinA_);         // get pointer to output register

    myBit_b = NK_PIN_TO_BITMASK(_pinB_);          // get send pin's ports and bitmask
    myReg_b = NK_PIN_TO_BASEREG(_pinB_);         // get pointer to output register

    myBit_c = NK_PIN_TO_BITMASK(_pinC_);          // get send pin's ports and bitmask
    myReg_c = NK_PIN_TO_BASEREG(_pinC_);         // get pointer to output register

    myBit_d = NK_PIN_TO_BITMASK(_pinD_);          // get send pin's ports and bitmask
    myReg_d = NK_PIN_TO_BASEREG(_pinD_);         // get pointer to output register

//    ui8_arr_MyStep[0] = 0x01;
//    ui8_arr_MyStep[1] = 0x02;
//    ui8_arr_MyStep[2] = 0x04;
//    ui8_arr_MyStep[3] = 0x08;

    ui8_arr_MyStep[0] = 0x08;
    ui8_arr_MyStep[1] = 0x0c;
    ui8_arr_MyStep[2] = 0x04;
    ui8_arr_MyStep[3] = 0x06;
    ui8_arr_MyStep[4] = 0x02;
    ui8_arr_MyStep[5] = 0x03;
    ui8_arr_MyStep[6] = 0x01;
    ui8_arr_MyStep[7] = 0x09;

    ui8_My_current_IndexStep = 0;
    ul_timeRun_us = 1000;

    Vietduino_Manager.add(this);
}

void Vietduino_StepMotor::forward(unsigned char s){
    if(uc_Last_Dir_Val == _V_DIR_BACKWARD_){
        NK_DIRECT_WRITE_HIGH(myReg_d, myBit_d);
        uc_Last_Dir_Val = _V_DIR_FORWARD_;
    }

    if(uc_Last_Pwm_Val != s){
        analogWrite(pwm, 255 - s);
        uc_Last_Pwm_Val = s;
    }

}
void Vietduino_StepMotor::backward(unsigned char s){
    if(uc_Last_Dir_Val == _V_DIR_FORWARD_){
        NK_DIRECT_WRITE_LOW(myReg_d, myBit_d);
        uc_Last_Dir_Val = _V_DIR_BACKWARD_;
    }

    if(uc_Last_Pwm_Val != s){
        analogWrite(pwm,s);
        uc_Last_Pwm_Val = s;
    }

}

void Vietduino_StepMotor::stop(){
    if(uc_Last_Dir_Val == _V_DIR_FORWARD_){
        forward(0);
    }else{
        backward(0);
    }

    ul_timeRun = 0;
    _loopID_ = 0;
    setPeriodUs(0);
}

void Vietduino_StepMotor::write(unsigned char _dir_, unsigned char _speed_){
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

void Vietduino_StepMotor::write(unsigned char _dir_, unsigned char _speed_, unsigned long _runForMs_)
{
    write(_dir_, _speed_);
    ul_timeRun = _runForMs_;
    _loopID_ = 0;
    setPeriodUs(0);
}

void Vietduino_StepMotor::setR_wheel(float R_mm)
{
    f_wheel_r_mm = R_mm; //
    f_wheel_c_mm = f_wheel_r_mm * 2 * PI;
}

bool Vietduino_StepMotor::available()
{
    return !isRunning;
}

unsigned long Vietduino_StepMotor::ulF_convertMmToStep(float unit_mm)
{
    return unit_mm * ul_stepPerRound / f_wheel_c_mm;
}

float Vietduino_StepMotor::ulF_convertStepToMm(unsigned long _step_)
{
    return (float)_step_ * f_wheel_c_mm / ul_stepPerRound;
}

void Vietduino_StepMotor::run(Vietduino_Task *me){
    Vietduino_StepMotor * te = (Vietduino_StepMotor*) me;
//    if(te->_loopID_ == 0){
//        if(te->ul_timeRun > 0){
//            te->_loopID_ = 1;
//            te->setPeriodUs(te->ul_timeRun * 1000);
//        }
//    }else if(te->_loopID_ == 1){
//        te->stop();
//    }else;
    te->ui8_My_current_IndexStep = STEPMOTOR_GET_NEXT_INDEX(te->ui8_My_current_IndexStep, 1);
    te->F_outPut(te->ui8_arr_MyStep[te->ui8_My_current_IndexStep]);

//    uint8_t temVal_step = 0;
//    NK_bitSet(temVal_step, te->ui8_My_current_IndexStep);
//    te->F_outPut(temVal_step);

    te->setPeriodUs(te->ul_timeRun_us);
}

void Vietduino_StepMotor::F_outPut(uint8_t _inputValue_)
{
    if(NK_bitRead(_inputValue_, 0)){
        NK_DIRECT_WRITE_HIGH(myReg_a, myBit_a);
    }else{
        NK_DIRECT_WRITE_LOW(myReg_a, myBit_a);
    }

    if(NK_bitRead(_inputValue_, 1)){
        NK_DIRECT_WRITE_HIGH(myReg_b, myBit_b);
    }else{
        NK_DIRECT_WRITE_LOW(myReg_b, myBit_b);
    }

    if(NK_bitRead(_inputValue_, 2)){
        NK_DIRECT_WRITE_HIGH(myReg_c, myBit_c);
    }else{
        NK_DIRECT_WRITE_LOW(myReg_c, myBit_c);
    }

    if(NK_bitRead(_inputValue_, 3)){
        NK_DIRECT_WRITE_HIGH(myReg_d, myBit_d);
    }else{
        NK_DIRECT_WRITE_LOW(myReg_d, myBit_d);
    }
}
 
