/**
 * File: Vietduino_NewFunction.cpp
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_NewFunction is free software: you can redistribute it and/or modify
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

#include "Vietduino_NewFunction.h"
//#include "Vietduino_Manager.h"

Vietduino_NewFunction::Vietduino_NewFunction(void (*_UserF_)(Vietduino_Task * me)):
    Vietduino_Task(0, &(Vietduino_NewFunction::run)) {
    p_manager = &Vietduino_Manager_3;
    this->MyF = _UserF_;
    this->enable();
}

Vietduino_NewFunction::Vietduino_NewFunction(void (*_UserF_)(Vietduino_Task *), p_Priority_class _p_manager):
    Vietduino_Task(0, &(Vietduino_NewFunction::run))
{
    p_manager = _p_manager;
    this->MyF = _UserF_;
    this->enable();
}

void Vietduino_NewFunction::delay(unsigned long __dl_) {
  this->setPeriodMs(__dl_);
}

void Vietduino_NewFunction::delayus(unsigned long __dl_) {
  this->setPeriodUs(__dl_);
}

void Vietduino_NewFunction::run(Vietduino_Task * me){
    Vietduino_NewFunction * te = (Vietduino_NewFunction*)me;
    te->setPeriodMs(0);
    if(te->Enable){
            if(te->UserF){
                te->UserF(me);
            }

            if(te->UserF_2){
                te->UserF_2((boolean*)me);
            }

            if(te->MyF){
                te->MyF(me);
            }

    }else;
}

void Vietduino_NewFunction::disable(){
	Enable = false;
//        Vietduino_Manager.remove(this);
        p_manager->remove(this);
}

void Vietduino_NewFunction::enable(){
	if(Enable == false){
		Enable = true;
	}
        this->setPeriodMs(0);
        this->setJumPoint((void *)0);
//        Vietduino_Manager.add(this);
        p_manager->add(this);
}


void Vietduino_NewFunction::begin(void (*_UserF_)(Vietduino_Task * me)){
	UserF = _UserF_;
	enable();
}

void Vietduino_NewFunction::begin(void (*_UserF_)(boolean * me)){
        UserF_2 = _UserF_;
        enable();
}

bool Vietduino_NewFunction::available(){
    return Enable;
}
