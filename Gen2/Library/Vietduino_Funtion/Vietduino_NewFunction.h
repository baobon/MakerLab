/**
 * File: Vietduino_NewFunction.h
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

#ifndef __VIETDUINO_H_NEW_FUNCTION_H__
#define __VIETDUINO_H_NEW_FUNCTION_H__

#include "Arduino.h"
#include "Vietduino_Task.h"
#include "Vietduino_Manager_Priority.h"

////---------------------------
#define M_DELAY(delayMillis) \
  do { \
      te->delay(delayMillis); \
        do { \
          __label__ jump_point; \
          te->setJumPoint(&& jump_point); \
          return; \
          jump_point: ; \
          te->setJumPoint((void*)0);\
        } while (false);\
    } while (false)
/// ++++++++++++++++++++++++++++
////---------------------------
#define M_DELAY_US(delayMicros) \
  do { \
      te->delayus(delayMicros); \
        do { \
          __label__ jump_point; \
          te->setJumPoint(&& jump_point); \
          return; \
          jump_point: ; \
          te->setJumPoint((void*)0);\
        } while (false);\
    } while (false)
/// ++++++++++++++++++++++++++++
/// ----------------------------
#define M_LOOP()  \
  Vietduino_NewFunction *te  =  (Vietduino_NewFunction*)me;\
  void* p = te->getJumPoint();\
    if (p != 0) {\
      goto *p;\
    }
/// ++++++++++++++++++++++++++++
/// ----------------------------
///
#define CREATE_FUNCTION(...)   \
    GET_CREATE_FUNCTION(__VA_ARGS__, CREATE_FUNCTION2, CREATE_FUNCTION1)(__VA_ARGS__)

#define GET_CREATE_FUNCTION(_1, _2, NAMEE, ...) NAMEE

#define CREATE_FUNCTION1(FunctionName) \
    void FunctionName##_FE(Vietduino_Task * me);\
    Vietduino_NewFunction FunctionName(FunctionName##_FE);\
    void FunctionName##_FE(Vietduino_Task * me){\
    M_LOOP()

#define CREATE_FUNCTION2(FunctionName, pri_level) \
    void FunctionName##_FE(Vietduino_Task * me);\
    Vietduino_NewFunction FunctionName(FunctionName##_FE, \
    (pri_level> 0)?&Vietduino_Manager_##pri_level:&Vietduino_Manager_3);\
    void FunctionName##_FE(Vietduino_Task * me){\
    M_LOOP()

#define END_CREATE_FUNCTION  }

#define DEFINE_FUNCTION(...)   \
GET_DEFINE_FUNCTION(__VA_ARGS__, DEFINE_FUNCTION2, DEFINE_FUNCTION1)(__VA_ARGS__)

#define GET_DEFINE_FUNCTION(_1, _2, NAMEE, ...) NAMEE

#define DEFINE_FUNCTION1(FunctionName) \
    extern void FunctionName##_FE(Vietduino_Task * me);\
    extern Vietduino_NewFunction FunctionName;

#define DEFINE_FUNCTION2(FunctionName, pri_level) \
    extern void FunctionName##_FE(Vietduino_Task * me);\
    extern Vietduino_NewFunction FunctionName;
/// ++++++++++++++++++++++++++++

class Vietduino_NewFunction : public Vietduino_Task
{

  public:
    Vietduino_NewFunction(Vietduino_Function me = 0);
    Vietduino_NewFunction(void (*_UserF_)(Vietduino_Task * me), \
    p_Priority_class _p_manager);
    p_Priority_class p_manager;
    virtual ~Vietduino_NewFunction(){}
    
    void delay(unsigned long __dl_);
    void delayus(unsigned long __dlus_);

    static void run(Vietduino_Task * me);
    void disable();
    void enable();
    virtual void begin(void (*_UserF_)(Vietduino_Task * me) = 0);
    virtual void begin(void (*_UserF_)(boolean * me) = 0);
    void (*UserF)(Vietduino_Task * me);
    void (*UserF_2)(boolean * me);
    void (*MyF)(Vietduino_Task * me);

    bool available();

    void * p_currentPoint;
    void * p_lastPoint;
    void setJumPoint(void *_myJumPoint){p_currentPoint = _myJumPoint;}
    void * getJumPoint(){return p_currentPoint;}


  private:
    bool Enable;
};
#endif //__Vietduino_NewFunction_H__
