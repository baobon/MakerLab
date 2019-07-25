/**
 * File: Vietduino_Timer.h
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

#ifndef __VIETDUINO_TIMER_H__
#define __VIETDUINO_TIMER_H__

#include "Arduino.h"

#include "Vietduino_Task.h"

#define SLOOP(x)    te->setloop(x);

//#define START_IF()   Vietduino_Timer* te = (Vietduino_Timer*) me;\
//                      if(te->nextloop == 1){

#define START_IFx(x)   x * te = (x *) me;\
                      if(te->nextloop == 1){

#define START_IF()   START_IFx(Vietduino_Timer)

#define DL_IF(x,y)  te->delay(x);\
                  }\
                  else if(te->nextloop == y){

#define EL_IF(y)  }\
                  else if(te->nextloop == y){

#define END_IF(x) \
                  te->delay(x);\
                  }else;
//{\
//                  SLOOP(1)\
                  }\

#define DELAY_IF(x)  te->delay(x);

#define WHILE_LOOP(x,y) if(x) SLOOP(y)

#define V_TASK  * me

#define DISABLE_IF  te->disable();

class Vietduino_Timer : public Vietduino_Task
{

  public:
    Vietduino_Timer(void (*_UserF_)(Vietduino_Task * me) = 0);
    virtual ~Vietduino_Timer(){}

    unsigned char nextloop; // nextSche;
    unsigned char lastloop;
    
    void delay(unsigned long __dl_);
    void delayus(unsigned long __dlus_);

    static void run(Vietduino_Task * me);
    void disable();
    void enable();
    void enable(uint8_t _nextloop_);
    virtual void begin(void (*_UserF_)(Vietduino_Task * me) = 0);
    virtual void begin(void (*_UserF_)(boolean * me) = 0);
    void (*UserF)(Vietduino_Task * me);
    void (*UserF_2)(boolean * me);
    void (*MyF)(Vietduino_Task * me);
    void setloop(uint8_t _nextloop_);
    void pause();
    void play();
    bool available();
  private:
    bool Enable;
    bool isPause;
};
#endif //__VIETDUINO_TIMER_H__
