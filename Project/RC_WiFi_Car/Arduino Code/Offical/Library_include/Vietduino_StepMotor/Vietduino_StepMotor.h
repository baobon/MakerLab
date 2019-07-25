/**
 * File: Vietduino_StepMotor.h
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

#ifndef __VIETDUINO_STEP_MOTOR_H__
#define __VIETDUINO_STEP_MOTOR_H__

#include "Arduino.h"
#include "Vietduino_Task.h"
#include "Vietduino_Io.h"

//#define STEPMOTOR_MAX_INDEX  3
#define STEPMOTOR_MAX_INDEX  7
#define STEPMOTOR_MIN_INDEX  0
#define STEPMOTOR_GET_NEXT_INDEX(index, dir) \
        (dir ? (index >= STEPMOTOR_MAX_INDEX ? 0 : index + 1)\
        : (index <= STEPMOTOR_MIN_INDEX ? STEPMOTOR_MAX_INDEX : index - 1))

enum{
    _V_DIR_BACKWARD_ = 0,
    _V_DIR_FORWARD_
}dir_motor_state;

class Vietduino_StepMotor: public Vietduino_Task
{
 public:

        Vietduino_StepMotor(unsigned char _pinA_, unsigned char _pinB_, unsigned char _pinC_, unsigned char _pinD_);
        virtual ~Vietduino_StepMotor(){}
	void forward(unsigned char s);
	void backward(unsigned char s);
        void stop();
        void write(unsigned char _dir_, unsigned char _speed_);
        void write(unsigned char _dir_, unsigned char _speed_, unsigned long _runForMs_);

        void setR_wheel(float R_mm);
        bool available();

        unsigned long ulF_convertMmToStep(float unit_mm);
        float ulF_convertStepToMm(unsigned long _step_);

        static void run(Vietduino_Task * me);

        unsigned long ul_timeRun_us;
private:
        unsigned char dir;
        unsigned char pwm;

        unsigned char uc_Last_Dir_Val;
        unsigned char uc_Last_Pwm_Val;

        unsigned char _loopID_ = 0;

        unsigned long ul_timeRun;

        //  http://www.instructables.com/id/BYJ48-Stepper-Motor/
        unsigned long ul_stepPerRound = 4096; // steps= (360°/5.625°)*64"Gear ratio" = 64 * 64 =4096
        float f_wheel_r_mm = 65/2; //
        float f_wheel_c_mm = f_wheel_r_mm * 2 * PI;
        bool  isRunning = false;

        uint8_t ui8_arr_MyStep[8];

        uint8_t ui8_My_current_IndexStep = 0;

        NK_IO_REG_TYPE myBit_a;
        volatile NK_IO_REG_TYPE *myReg_a;

        NK_IO_REG_TYPE myBit_b;
        volatile NK_IO_REG_TYPE *myReg_b;

        NK_IO_REG_TYPE myBit_c;
        volatile NK_IO_REG_TYPE *myReg_c;

        NK_IO_REG_TYPE myBit_d;
        volatile NK_IO_REG_TYPE *myReg_d;

        void F_outPut(uint8_t _inputValue_);
};

#endif //__DC_H__
