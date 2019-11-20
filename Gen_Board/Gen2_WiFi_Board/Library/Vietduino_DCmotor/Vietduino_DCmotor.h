/**
 * File: Vietduino_DCmotor.h
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

#ifndef __VIETDUINO_DC_MOTOR_H__
#define __VIETDUINO_DC_MOTOR_H__

#include "Arduino.h"
#include "Vietduino_Task.h"
#include "Vietduino_Io.h"

enum{
    _V_DIR_BACKWARD_ = 0,
    _V_DIR_FORWARD_
}dir_motor_state;

class Vietduino_DCmotor: public Vietduino_Task
{
 public:

        Vietduino_DCmotor(unsigned char _Port_Unobase_);
        Vietduino_DCmotor(unsigned char _speed_, unsigned char _dir_);
        virtual ~Vietduino_DCmotor(){}
	void forward(unsigned char s);
	void backward(unsigned char s);
        void stop();
        void write(unsigned char _dir_, unsigned char _speed_);
        void write(unsigned char _dir_, unsigned char _speed_, unsigned long _runForMs_);

        static void run(Vietduino_Task * me);
private:
        unsigned char dir;
        unsigned char pwm;

        unsigned char uc_Last_Dir_Val;
        unsigned char uc_Last_Pwm_Val;

        unsigned char _loopID_ = 0;

        unsigned long ul_timeRun;

        NK_IO_REG_TYPE myBit_d;
        volatile NK_IO_REG_TYPE *myReg_d;

        NK_IO_REG_TYPE myBit_s;
        volatile NK_IO_REG_TYPE *myReg_s;
};

#endif //__DC_H__
