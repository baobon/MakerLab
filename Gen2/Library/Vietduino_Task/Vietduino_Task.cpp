/**
 * File: Vietduino_Task.cpp
 * Description:
 * Vietduino_Manager library base on SoftTimer library which is a lightweight but effective event based timeshare solution for Arduino.
 *
 * Author: Balazs Kelemen
 * Modify: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    SoftTimer is free software: you can redistribute it and/or modify
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
#include "Vietduino_Task.h"

Vietduino_Task::Vietduino_Task(unsigned long periodMs, void (*callback)(Vietduino_Task* me)) {
  this->setPeriodMs(periodMs);
  this->callback = callback;
  this->lastCallTimeMicros = 0;
  this->nextTask = NULL;
}

void Vietduino_Task::setPeriodMs(unsigned long periodMs) {
  this->periodMicros = periodMs * 1000;
}

void Vietduino_Task::setPeriodUs(unsigned long periodMs) {
  this->periodMicros = periodMs;
}
