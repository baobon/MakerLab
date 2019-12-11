// -----
// Vietduino_Button base on OneButton - Library for detecting button clicks, doubleclicks and long press pattern on a single button.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// 02.10.2010 created by Matthias Hertel
// 21.04.2011 transformed into a library
// 01.12.2011 include file changed to work with the Arduino 1.0 environment
// 23.03.2014 Enhanced long press functionalities by adding longPressStart and longPressStop callbacks
// 21.09.2015 A simple way for debounce detection added.
// 17.05.2018 KXN edit to use with Vietduino Framework.
// -----

#ifndef _VIETDUINO_BUTTON_H_
#define _VIETDUINO_BUTTON_H_

#include "Arduino.h"
#include "Vietduino_Task.h"
#include "Vietduino_Io.h"

// ----- Callback function types -----

enum{
    _CLICK_NOTHING_ = 0,
    _CLICKED_,
    _DOUBLE_CLICKED_,
    _LONG_CLICKED_,
    _PRESSED_,
    _DURING_LONG_PRESSED_

}But_state;

class Vietduino_Button: public Vietduino_Task
{
public:
  // ----- Constructor -----
    Vietduino_Button();
    virtual ~Vietduino_Button();

    void begin(int pin, int active = 1);

    // ----- Set runtime parameters -----

    // set # millisec after single click is assumed.
    void setClickTicks(int ticks);

    // set # millisec after press is assumed.
    void setPressTicks(int ticks);

    // attach functions that will be called when button was pressed in the specified way.
    void attachClick(Vietduino_Function newFunction);
    void attachDoubleClick(Vietduino_Function newFunction);
    void attachPress(Vietduino_Function newFunction); // DEPRECATED, replaced by longPressStart, longPressStop and duringLongPress
    void attachRelease(Vietduino_Function newFunction);
    void attachLongPressStart(Vietduino_Function newFunction);
    void attachLongPressStop(Vietduino_Function newFunction);
    void attachDuringLongPress(Vietduino_Function newFunction);

    // ----- State machine functions -----

    // call this function every some milliseconds for handling button events.
    static void tick(Vietduino_Task * me);
    bool isLongPressed();
    bool Press_available();
    bool Click_available();
    bool Double_Click_available();
    bool Long_Click_available();
    bool Long_Press_available();
    bool available(unsigned char _state_id);
    int gettimePress();

private:
    int _pin;        // hardware pin number.
    int _clickTicks; // number of ticks that have to pass by before a click is detected
    int _pressTicks; // number of ticks that have to pass by before a long button press is detected
    const int _debounceTicks = 50; // number of ticks for debounce times.

    int _buttonReleased;
    int _buttonPressed;

    bool _isLongPressed;
    bool _isClicked;
    unsigned char button_state;

    // These variables will hold functions acting as event source.
    Vietduino_Function _clickFunc;
    Vietduino_Function _doubleClickFunc;
    Vietduino_Function _pressFunc;
    Vietduino_Function _releaseFunc;
    Vietduino_Function _longPressStartFunc;
    Vietduino_Function _longPressStopFunc;
    Vietduino_Function _duringLongPressFunc;

    // These variables that hold information across the upcoming tick calls.
    // They are initialized once on program start and are updated every time the tick function is called.
    int _state;
    unsigned long _startTime; // will be set in state 1

    NK_IO_REG_TYPE myBit;
    volatile NK_IO_REG_TYPE *myReg;
};

#endif


