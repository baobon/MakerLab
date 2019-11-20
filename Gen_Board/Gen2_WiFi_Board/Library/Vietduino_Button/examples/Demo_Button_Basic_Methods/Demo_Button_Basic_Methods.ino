#include "Vietduino_NewFunction.h"
#include "Vietduino_Button.h"

/*
	Wiring:
	                   Button
	                   _|_
	8 ----------------o  o--------------GND
*/

#define DEMO_BTN_PIN_8        (8)

Vietduino_Button btn_8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Test Vietduino_Button Start!");
  btn_8.begin(DEMO_BTN_PIN_8);
}

void loop() {
  // put your main code here, to run repeatedly:
  VIETDUINO_UPDATE;

  if(btn_8.available(_CLICKED_)){
    Serial.println("_CLICKED_");
  }

  if(btn_8.available(_DOUBLE_CLICKED_)){
    Serial.println("_DOUBLE_CLICKED_");
  }

  if(btn_8.available(_LONG_CLICKED_)){
    Serial.println("_LONG_CLICKED_");
  }

  if(btn_8.available(_PRESSED_)){
    Serial.println("_PRESSED_");
  }

  if(btn_8.available(_DURING_LONG_PRESSED_)){
    Serial.println("_DURING_LONG_PRESSED_");
  }
  
}
