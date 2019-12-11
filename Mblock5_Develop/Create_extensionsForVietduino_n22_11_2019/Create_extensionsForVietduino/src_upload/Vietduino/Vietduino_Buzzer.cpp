
/**
 * File: Vietduino_Buzzer.cpp
 *
 * Author: Ngoc Khuu
 * Contact: xuanngoc1992@gmail.com
 * Copyright: 2018 Ngoc Khuu
 * Copying permission statement:

    Vietduino_Buzzer is free software: you can redistribute it and/or modify
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

#include "Vietduino_Buzzer.h"
#include "Vietduino_Manager_Priority.h"
/*
  Contructor khai báo                                                        ->>>> Vietduino Update
*/
Vietduino_Buzzer::Vietduino_Buzzer(byte outPin) : Vietduino_Task(0, &(Vietduino_Buzzer::stepState))
{
    this->init(outPin, 0, 0, 0, 0);
    this->stop();
}
/* 
  Khởi tạo thông số mặc định 
*/
void Vietduino_Buzzer::init(byte b_outPin, unsigned long onUs, unsigned long offUs, byte count, unsigned long delayUs)
{
    this->onUs = onUs;
    this->offUs = offUs;
    this->count = count;
    this->delayUs = delayUs;
    this->outPin = b_outPin;
                   // this->_bitMask = digitalPinToBitMask(outPin);
                   // this->_portRegister = NK_PIN_TO_BASEREG(outPin);
                   // NK_DIRECT_MODE_OUTPUT(this->_portRegister, this->_bitMask);
    this->onLevel = 1; // Kich cao thap !
}

void Vietduino_Buzzer::on()
{
    // this->_state = BUZZER_STATE_ON;
    this->_state = BUZZER_STATE_ON;
    this->write(429496, 1, 0, 0);
}

void Vietduino_Buzzer::start()
{
    this->_state = BUZZER_STATE_OFF;
    this->_counter = 0;
    this->setPeriodUs(0);
    this->_isrun = true;
    Vietduino_Manager_3.add(this);
}

void Vietduino_Buzzer::stop()
{	noTone(3);
    this->_isrun = false;
    Vietduino_Manager_3.remove(this);
}

void Vietduino_Buzzer::stepState(Vietduino_Task *task)
{
    Vietduino_Buzzer *bt = (Vietduino_Buzzer *)task;
    if (bt->_state == BUZZER_STATE_ON)
    {
        // -- Turn off.
        if (bt->onLevel != HIGH)
        {
            tone(bt->outPin, VIETDUINO_BUZZER_FREQ); // tone(tham so truyen vo)
            VIETDUINO_BUZZER_DEBUG(F("Buzzer_debug---> on"));
        }
        else
        {
            noTone(bt->outPin);
            VIETDUINO_BUZZER_DEBUG(F("Buzzer_debug ---> off"));
        }
        bt->_state = BUZZER_STATE_OFF;
        if (bt->offUs == 0)
        {
            bt->stop();
        }
        else
        {
            bt->setPeriodUs(bt->offUs);
            bt->_counter += 1;
        }

        if ((bt->count > 0) && (bt->_counter >= bt->count))
        {
            // -- Count was defined, and we reached it.
            bt->_counter = 0;

            if (bt->delayUs > 0)
            {
                // -- delay was defined.
                bt->_state = BUZZER_STATE_WAIT;
                bt->setPeriodUs(bt->delayUs);
            }
            else
            {
                bt->stop();
            }
        }
    }
    else
    {
        // -- state == OFF or WAIT
        // -- Turn on.
        if (bt->onLevel != HIGH)
        {
            // NK_DIRECT_WRITE_LOW(bt->_portRegister, bt->_bitMask);
            noTone(bt->outPin);
        }
        else
        {
            // NK_DIRECT_WRITE_HIGH(bt->_portRegister, bt->_bitMask);
            tone(bt->outPin, VIETDUINO_BUZZER_FREQ);
        }
        bt->_state = BUZZER_STATE_ON;
        bt->setPeriodUs(bt->onUs);
        //    bt->_counter += 1;
    }
}

bool Vietduino_Buzzer::isRunning()
{
    return this->_isrun;
}



void Vietduino_Buzzer::write(unsigned long _ton_, unsigned long _toff_, byte _count_, unsigned long _delay_)
{ // unit ms.
    this->stop();
    this->onUs = VBUZZER_CHECK_VALID_TIME(_ton_) * 1000;
    this->offUs = VBUZZER_CHECK_VALID_TIME(_toff_) * 1000;
    this->count = _count_;
    this->delayUs = VBUZZER_CHECK_VALID_TIME(_delay_) * 1000;

    this->start();
}
