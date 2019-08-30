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

#ifndef _VIETDUINO_MANAGER_H_
#define _VIETDUINO_MANAGER_H_

#include "Vietduino_Task.h"
#define    VIETDUINO_UPDATE      Vietduino_Manager.run();
#define    VIETDUINO_TASK        * me

class Vietduino_Manager_class
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
    void run();
  private:
    void testAndCall(Vietduino_Task* task);
    Vietduino_Task* _tasks;
};

extern Vietduino_Manager_class Vietduino_Manager;

#endif
