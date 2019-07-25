/**
 * File: Vietduino_Led.cpp
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_Led is free software: you can redistribute it and/or modify
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

#include "Vietduino_Led.h"
#include "Vietduino_Manager_Priority.h"

Vietduino_Led::Vietduino_Led(byte outPin, byte _ledActive_) : Vietduino_Task(0, &(Vietduino_Led::stepState)){
    this->init(outPin, _ledActive_, 0, 0, 0, 0);
    this->stop();
}

void Vietduino_Led::init(byte outPin, byte _onlevel_,unsigned long onUs, unsigned long offUs, byte count, unsigned long delayUs) {
  this->onUs = onUs;
  this->offUs = offUs;
  this->count = count;
  this->delayUs = delayUs;
  this->_bitMask = digitalPinToBitMask(outPin);
  this->_portRegister = NK_PIN_TO_BASEREG(outPin);
  NK_DIRECT_MODE_OUTPUT(this->_portRegister,this->_bitMask);

  this->onLevel = _onlevel_;
}

void Vietduino_Led::start() {
  this->_state = STATE_OFF;
  this->_counter = 0;
  this->setPeriodUs(0);
  this->_isrun = true;
  Vietduino_Manager_3.add(this);
}

void Vietduino_Led::stop() {
  this->_isrun = false;
  Vietduino_Manager_3.remove(this);
}

void Vietduino_Led::stepState(Vietduino_Task* task) {
  Vietduino_Led* bt = (Vietduino_Led*)task;
  if(bt->_state == STATE_ON) {
    // -- Turn off.
    if(bt->onLevel != HIGH) {
        NK_DIRECT_WRITE_HIGH(bt->_portRegister,bt->_bitMask);
    } else {  
        NK_DIRECT_WRITE_LOW(bt->_portRegister,bt->_bitMask);
    }
    bt->_state = STATE_OFF;
    if(bt->offUs == 0){
        bt->stop();
    }else{
        bt->setPeriodUs(bt->offUs);
        bt->_counter += 1;
    }

    if((bt->count > 0) && (bt->_counter >= bt->count)) {
      // -- Count was defined, and we reached it.
      bt->_counter = 0;

      if(bt->delayUs > 0) {
        // -- delay was defined.
        bt->_state = STATE_WAIT;
        bt->setPeriodUs(bt->delayUs);
      } else {
        bt->stop();
      }
    }

  }
  else {
    // -- state == OFF or WAIT
    // -- Turn on.
    if(bt->onLevel != HIGH) {
        NK_DIRECT_WRITE_LOW(bt->_portRegister,bt->_bitMask);
    } else {  
        NK_DIRECT_WRITE_HIGH(bt->_portRegister,bt->_bitMask);
    }
    bt->_state = STATE_ON;
    bt->setPeriodUs(bt->onUs);
//    bt->_counter += 1;
  }
}

bool Vietduino_Led::isRunning(){
    return this->_isrun;
}

void Vietduino_Led::write(unsigned long _ton_, unsigned long _toff_, byte _count_, unsigned long _delay_){ // unit ms.
    this->stop();
    this->onUs = VLED_CHECK_VALID_TIME(_ton_) * 1000;
    this->offUs = VLED_CHECK_VALID_TIME(_toff_) * 1000;
    this->count = _count_;
    this->delayUs = VLED_CHECK_VALID_TIME(_delay_) * 1000;

    this->start();
}
