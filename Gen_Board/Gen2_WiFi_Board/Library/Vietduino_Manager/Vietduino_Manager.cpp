/**
 * File: Vietduino_Manager.cpp
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

#include "Arduino.h"
#include "Vietduino_Manager.h"

/**
 * Register a task in the timer Vietduino_Manager.
 */
void Vietduino_Manager_class::add(Vietduino_Task* task) {

  // -- A task should be registered only once.
  this->remove(task);
  
  if(this->_tasks == NULL) {
  
    // -- This is the first task being registered.
    this->_tasks = task;
    
  } else {
  
    Vietduino_Task* lastTask = this->_tasks;
    // -- Find the last task, to build a chain.
    while(lastTask->nextTask != NULL) {
      lastTask = lastTask->nextTask;
    }
    // -- Last task found, let's add this task to the end of the chain.
    lastTask->nextTask = task;
    
  }
  
  task->lastCallTimeMicros = micros() - task->periodMicros; // -- Start immediately after registering.
  task->nextTask = NULL;
}


/**
 * Remove registration of a task in the timer manager.
 */
void Vietduino_Manager_class::remove(Vietduino_Task* task) {
  if(this->_tasks != NULL) {
    if(this->_tasks == task) {
      // -- This was the first task.
      this->_tasks = task->nextTask;
    } else {
      Vietduino_Task* lastTask = this->_tasks;
      // -- Find this task in the chain.
      while(lastTask->nextTask != NULL) {
        if(lastTask->nextTask == task) {
          // -- Remove the task with joining the chain.
          lastTask->nextTask = task->nextTask;
          break;
        }
        lastTask = lastTask->nextTask;
      }
    }
  }
}

/**
 * Walk through the chain looking for task to call.
 */
void Vietduino_Manager_class::run() {
    Vietduino_Task* task = this->_tasks;
    // -- (If this->_tasks is NULL, than nothing is registered.)
    while(task != NULL) {
      this->testAndCall(task);
      task = task->nextTask;
    }
}

/**
 * Test a task and call the callback if its period was passed since last call.
 */
void Vietduino_Manager_class::testAndCall(Vietduino_Task* task) {
  unsigned long now = micros();
  unsigned long calc = task->lastCallTimeMicros + task->periodMicros;
  if(
    ((now >= calc) && (
      (calc >= task->lastCallTimeMicros) // -- Nothing was overflown.
      || (task->lastCallTimeMicros > now) // -- Both timer and interval-end overflows
      ))
    || ((now < task->lastCallTimeMicros) && (task->lastCallTimeMicros <= calc))) // -- timer overflows, but interval-end does not
  {
    task->nowMicros = now;
    task->callback(task);
    task->lastCallTimeMicros = now;
  }
}


/**
 * Create a singleton from this manager class.
 */
Vietduino_Manager_class Vietduino_Manager;
