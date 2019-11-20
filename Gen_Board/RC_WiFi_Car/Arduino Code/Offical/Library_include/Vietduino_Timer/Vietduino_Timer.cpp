/**
 * File: Vietduino_Timer.cpp
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_Timer is free software: you can redistribute it and/or modify
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

#include "Vietduino_Timer.h"
#include "Vietduino_Manager.h"

Vietduino_Timer::Vietduino_Timer(void (*_UserF_)(Vietduino_Task * me)):
    Vietduino_Task(0, &(Vietduino_Timer::run)) {
    this->MyF = _UserF_;
    this->isPause = false;
    this->enable();
}

void Vietduino_Timer::delay(unsigned long __dl_) {
  setPeriodMs(__dl_);
}

void Vietduino_Timer::delayus(unsigned long __dl_) {
  setPeriodUs(__dl_);
}

void Vietduino_Timer::run(Vietduino_Task * me){
    Vietduino_Timer * pt = (Vietduino_Timer*)me;
    pt->setPeriodMs(0);
    if(pt->Enable){
            pt->nextloop++;
            if(pt->UserF){
                pt->UserF(me);
            }

            if(pt->UserF_2){
                pt->UserF_2((boolean*)me);
            }

            if(pt->MyF){
                pt->MyF(me);
            }

    }else;
}

void Vietduino_Timer::disable(){
	nextloop = 0;
	Enable = false;
        Vietduino_Manager.remove(this);
}

void Vietduino_Timer::enable(){
	if(Enable == false){
		nextloop = 0;
		Enable = true;
	}
        this->setPeriodMs(0);
        Vietduino_Manager.add(this);
}

void Vietduino_Timer::enable(uint8_t _nextSch_){
	if(Enable == false){
		nextloop = _nextSch_;
		Enable = true;
	}
}

void Vietduino_Timer::begin(void (*_UserF_)(Vietduino_Task * me)){
	UserF = _UserF_;
	enable();
}

void Vietduino_Timer::begin(void (*_UserF_)(boolean * me)){
        UserF_2 = _UserF_;
        enable();
}

void Vietduino_Timer::setloop(uint8_t _nextloop_){
	lastloop = nextloop;
	nextloop = _nextloop_ - 1;
}

void Vietduino_Timer::pause(){
	if(isPause == false){
		Enable = false;
		isPause = true;
	}
}

void Vietduino_Timer::play(){
	if(isPause == true){
		Enable = true;
		isPause = false;
	}
	Enable = true;
}

bool Vietduino_Timer::available(){
    return Enable;
}
