// -----
// Vietduino_Button base on OneButton - Library for detecting button clicks, doubleclicks and long press pattern on a single button.
// This class is implemented for use with the Arduino environment.
// Copyright (c) by Matthias Hertel, http://www.mathertel.de
// This work is licensed under a BSD style license. See http://www.mathertel.de/License.aspx
// More information on: http://www.mathertel.de/Arduino
// -----
// Changelog: see OneButton.h
// -----

#include "Vietduino_Button.h"
#include "Vietduino_Manager_Priority.h"

// ----- Initialization and Default Values -----

Vietduino_Button::Vietduino_Button():
    Vietduino_Task(10, &Vietduino_Button::tick){
    Vietduino_Manager_3.add(this);
}

Vietduino_Button::~Vietduino_Button(){

}

void Vietduino_Button::begin(int pin, int activeLow = 1)
{
    myBit = NK_PIN_TO_BITMASK(pin);          // get send pin's ports and bitmask
    myReg = NK_PIN_TO_BASEREG(pin);         // get pointer to output register

  NK_DIRECT_MODE_INPUT(myReg, myBit);

  _pin = pin;

  _clickTicks = 600;        // number of millisec that have to pass by before a click is detected.
  _pressTicks = 300;       // number of millisec that have to pass by before a long button press is detected.
 
  _state = 0; // starting with state 0: waiting for button to be pressed
  _isLongPressed = false;  // Keep track of long press state

  if (activeLow) {
    // button connects ground to the pin when pressed.
    _buttonReleased = HIGH; // notPressed
    _buttonPressed = LOW;
    NK_DIRECT_MODE_PULLUP(myReg, pin);

  } else {
    // button connects VCC to the pin when pressed.
    _buttonReleased = LOW;
    _buttonPressed = HIGH;
  } // if


  _doubleClickFunc = NULL;
  _pressFunc = NULL;
  _longPressStartFunc = NULL;
  _longPressStopFunc = NULL;
  _duringLongPressFunc = NULL;
} // Vietduino_Button


// explicitly set the number of millisec that have to pass by before a click is detected.
void Vietduino_Button::setClickTicks(int ticks) {
  _clickTicks = ticks;
} // setClickTicks


// explicitly set the number of millisec that have to pass by before a long button press is detected.
void Vietduino_Button::setPressTicks(int ticks) {
  _pressTicks = ticks;
} // setPressTicks


// save function for click event
void Vietduino_Button::attachClick(Vietduino_Function newFunction)
{
  _clickFunc = newFunction;
} // attachClick


// save function for doubleClick event
void Vietduino_Button::attachDoubleClick(Vietduino_Function newFunction)
{
  _doubleClickFunc = newFunction;
} // attachDoubleClick


// save function for press event
// DEPRECATED, is replaced by attachLongPressStart, attachLongPressStop, attachDuringLongPress,
void Vietduino_Button::attachPress(Vietduino_Function newFunction)
{
    _pressFunc = newFunction;
}

void Vietduino_Button::attachRelease(Vietduino_Function newFunction)
{
    _releaseFunc = newFunction;
} // attachPress

// save function for longPressStart event
void Vietduino_Button::attachLongPressStart(Vietduino_Function newFunction)
{
  _longPressStartFunc = newFunction;
} // attachLongPressStart

// save function for longPressStop event
void Vietduino_Button::attachLongPressStop(Vietduino_Function newFunction)
{
  _longPressStopFunc = newFunction;
} // attachLongPressStop

// save function for during longPress event
void Vietduino_Button::attachDuringLongPress(Vietduino_Function newFunction)
{
  _duringLongPressFunc = newFunction;
} // attachDuringLongPress

// function to get the current long pressed state
bool Vietduino_Button::isLongPressed(){
  return _isLongPressed;
}

void Vietduino_Button::tick(Vietduino_Task * me)
{
    Vietduino_Button * me_ = (Vietduino_Button *) me;
  // Detect the input information 
  int buttonLevel = NK_DIRECT_READ(me_->myReg, me_->myBit); // current button signal.
  unsigned long now = millis(); // current (relative) time in msecs.
  // Implementation of the state maechine
  if (me_->_state == 0) { // waiting for menu pin being pressed.
    if (buttonLevel == me_->_buttonPressed) {
      me_->_state = 1; // step to state 1
      me_->_startTime = now; // remember starting time
    } // if

  } else if (me_->_state == 1) { // waiting for menu pin being released.

    if ((buttonLevel == me_->_buttonReleased) && ((unsigned long)(now - me_->_startTime) < me_->_debounceTicks)) {
      // button was released to quickly so I assume some debouncing.
	  // go back to state 0 without calling a function.
      me_->_state = 0;

    } else if (buttonLevel == me_->_buttonReleased) {
      me_->_state = 2; // step to state 2

    } else if ((buttonLevel == me_->_buttonPressed) && ((unsigned long)(now - me_->_startTime) > me_->_pressTicks)) {
      me_->_isLongPressed = true;  // Keep track of long press state
      me_->button_state = _PRESSED_;

      if (me_->_pressFunc) me_->_pressFunc(me_);
      if (me_->_longPressStartFunc) me_->_longPressStartFunc(me_);
      if (me_->_duringLongPressFunc) me_->_duringLongPressFunc(me_);
      me_->_state = 6; // step to state 6
      
    } else {
      // wait. Stay in this state.
    } // if

  } else if (me_->_state == 2) { // waiting for menu pin being pressed the second time or timeout.
    if ((unsigned long)(now - me_->_startTime) > me_->_clickTicks) {
      // this was only a single short click
      me_->_isClicked = true;
      me_->button_state = _CLICKED_;

      if (me_->_releaseFunc) me_->_releaseFunc(me_);
      if (me_->_clickFunc) me_->_clickFunc(me_);
      me_->_state = 0; // restart.

    } else if (buttonLevel == me_->_buttonPressed) {
      me_->_state = 3; // step to state 3
    } // if

  } else if (me_->_state == 3) { // waiting for menu pin being released finally.
    if (buttonLevel == me_->_buttonReleased) {
      // this was a 2 click sequence.
        me_->button_state = _DOUBLE_CLICKED_;
      if (me_->_doubleClickFunc) me_->_doubleClickFunc(me_);
      me_->_state = 0; // restart.
    } // if

  } else if (me_->_state == 6) { // waiting for menu pin being release after long press.
    if (buttonLevel == me_->_buttonReleased) {
          me_->_isLongPressed = false;  // Keep track of long press state
          me_->button_state = _LONG_CLICKED_;
          if (me_->_releaseFunc) me_->_releaseFunc(me_);
          if(me_->_longPressStopFunc) me_->_longPressStopFunc(me_);
      me_->_state = 0; // restart.
    } else {
	  // button is being long pressed
          me_->_isLongPressed = true; // Keep track of long press state
          me_->button_state = _DURING_LONG_PRESSED_;
          if (me_->_duringLongPressFunc) me_->_duringLongPressFunc(me_);
    } // if  

  } // if  
} // Vietduino_Button.tick()

bool Vietduino_Button::available(unsigned char _state_id_){
    if(button_state == _state_id_){
        button_state = _CLICK_NOTHING_;
        return true;
    }else
        return false;
}

int Vietduino_Button::gettimePress(){
    return millis() - _startTime;
}

// end.

