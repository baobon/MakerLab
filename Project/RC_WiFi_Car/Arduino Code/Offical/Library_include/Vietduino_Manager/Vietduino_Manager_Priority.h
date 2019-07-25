/**
 * File: Vietduino_Manager.h
 * Description:
 * Vietduino_Manager library base on SoftTimer library which is a lightweight but effective event based timeshare solution for Arduino.
 *
 * Author: Balazs Kelemen
 * Modify: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_Manager is free software: you can redistribute it and/or modify
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

#ifndef _VIETDUINO_H_MANAGER_PRIORITY_H_
#define _VIETDUINO_H_MANAGER_PRIORITY_H_

#include "Vietduino_Task.h"
#define     VIETDUINO_UPDATE        Vietduino_Manager_3.run();
#define     VIETDUINO_TASK          * me

//#define MANAGER_PRI_DB_EN

#ifdef  MANAGER_PRI_DB_EN
    #define MANAGER_PRI_DB(x)       Serial.println(x)
#else
#define MANAGER_PRI_DB(x)
#endif
class Vietduino_Manager_Priority_class
{
  public:
  
    /**
     * Register a task in the Vietduino_Manager.
     */
    void add(Vietduino_Task* task);
    
    /**
    * Remove registration of a task in the Vietduino_Manager.
    */
    void remove(Vietduino_Task* task);
    
    /**
     * For internal use only. You do not need to call this function.
     */
    #ifdef  MANAGER_PRI_DB_EN
        String myString;

        Vietduino_Manager_Priority_class(Vietduino_Manager_Priority_class * _p_higher_priority_class, String _str_db){
            p_higher_priority_class = _p_higher_priority_class;
            myString = _str_db;
        }

    #endif

    Vietduino_Manager_Priority_class(Vietduino_Manager_Priority_class * _p_higher_priority_class){
        p_higher_priority_class = _p_higher_priority_class;
    }

    Vietduino_Manager_Priority_class(){
        p_higher_priority_class = 0;
    #ifdef  MANAGER_PRI_DB_EN
        myString = "Highest!!";
    #endif
    }

    Vietduino_Manager_Priority_class * p_higher_priority_class;

    void run();
  private:
    void testAndCall(Vietduino_Task* task);
    Vietduino_Task* _tasks;

};

extern "C" {
    typedef Vietduino_Manager_Priority_class * p_Priority_class;
}

extern Vietduino_Manager_Priority_class Vietduino_Manager_1;
extern Vietduino_Manager_Priority_class Vietduino_Manager_2;
extern Vietduino_Manager_Priority_class Vietduino_Manager_3;

#endif
