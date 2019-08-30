/**
 * File: Vietduino_Task.h
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

#ifndef _VIETDUINO_H_TASK_H_
#define _VIETDUINO_H_TASK_H_

/**
 * Vietduino_Task is a job that should be called repeatedly,
 */

class Vietduino_Task
{
  public:
    /**
     * Construct a task with defining a period and a callback handler function.
     *  periodMs - Call the task in every X milliseconds. Do not add values greater then 4,294,967, which is about 71 minutes!
     *  callback - Is a static function reference, the function will be called each time. The callback function need to
     * have one argument, which is the currently running task.
     */
    Vietduino_Task(unsigned long periodMs, void (*callback)(Vietduino_Task* me));

    virtual ~Vietduino_Task(){}
    
    /**
     * The timeslot in milliseconds the handler should be called.
     * Do not add values greater then 4,294,967, which is about 71 minutes!
     */
    void setPeriodMs(unsigned long periodMs);

    void setPeriodUs(unsigned long periodUs);           //kxn add 22/2/2018

    /**
     * The timeslot in milliseconds the handler should be called. If the value is near 1 the handler will be called in every loop.
     */
    unsigned long periodMicros;
    
    /**
     * The last call (start) time of the task. You can reset the task by setting this value to micros().
     */
    volatile unsigned long lastCallTimeMicros;
    
    /**
     * Start time of the task.
     */
    volatile unsigned long nowMicros;
    
    /**
     * The function that will be called when the period time was passed since the lastCallTime. This member is for internal use only.
     */
    void (*callback)(Vietduino_Task* me);
    /**
     * This member is for internal use only. Do not change!
     */
    Vietduino_Task* nextTask;
  private:
};

extern "C" {
  typedef void (*Vietduino_Function)(Vietduino_Task * me);
}

#endif
