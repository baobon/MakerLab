/**
 * File: Vietduino_Led.h
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

#ifndef _VIETDUINO_LED_H_
#define _VIETDUINO_LED_H_

#include <inttypes.h>
#include "Arduino.h"
#include "Vietduino_Io.h"
#include "Vietduino_Task.h"

#define STATE_OFF                       (0)
#define STATE_ON                        (1)
#define STATE_WAIT                      (2)
#define VLED_CHECK_VALID_TIME(value)    min(4294967, value)

class Vietduino_Led : public Vietduino_Task
{
  public:
    /**
     * By using this constructor you will be create a perpetual blinker with even on and off time-spans.
     *  outPin - The pin to blink.
     *  _ledActive_ is LOW or HIGH when ON (default is HIGH).
     */
    Vietduino_Led(byte outPin, byte _ledActive_ = 1);

    virtual ~Vietduino_Led(){}

    /**
     * Register the led Task to the Vietduino_Manager: start led.
     */
    void start();

    /**
     * Remove the led Task from the Vietduino_Manager.
     */
    void stop();

    /** The pin will be on for this amount of microseconds. */
    unsigned long onUs;
    /** The pin will be off for this amount of microseconds. */
    unsigned long offUs;
    /** The count of ON states before the task will sleep or be stopped. See delayUs for details. */
    byte count;
    /**
      * After a "count" of ON states the blinker will sleep for this amount of microseconds.
      * Value zero (0) has a special meaning: delay is disabled.
      * If delay is disabled AND count is specified, the task will be automatically removed after the count of ON states.
      */
    unsigned long delayUs;
	
    /** Pin level for the ON state. By default the ON means HIGH, you can change this to be LOW. */
    byte onLevel;

    bool isRunning();

    void write(unsigned long _ton_, unsigned long _toff_ = 0, byte _count_ = 0, unsigned long _delay_ = 0); // unit ms.

  private:
    void init(byte outPin, byte _onlevel_, unsigned long onUs, unsigned long offUs, byte count, unsigned long delayUs);
    static void stepState(Vietduino_Task* me);
    byte _counter;
    /** Can be STATE_OFF, STATE_ON, STATE_WAIT */
    byte _state;
    bool _isrun;

    uint8_t _bitMask;
    volatile NK_IO_REG_TYPE *_portRegister;
};

#endif
