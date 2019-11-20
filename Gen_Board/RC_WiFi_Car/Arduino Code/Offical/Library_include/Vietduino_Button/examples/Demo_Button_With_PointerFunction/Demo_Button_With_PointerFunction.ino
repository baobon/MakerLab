#include "Vietduino_NewFunction.h"
#include "Vietduino_Button.h"

#define DEMO_BTN_PIN_8        (8)
#define DEMO_BTN_ACTIVE_LOW   HIGH

/*
	Wiring:
	                   Button
	                   _|_
	8 ----------------o  o--------------GND
*/

Vietduino_Button btn_8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Test Vietduino_Button Start!");
  btn_8.begin(DEMO_BTN_PIN_8,DEMO_BTN_ACTIVE_LOW);
  
  btn_8.setClickTicks(200); //Set time (200 ms) to detect even Click, default 600ms
  btn_8.setPressTicks(200); //Set time (200 ms) to detect even Press, default 300ms
  
  btn_8.attachClick(&click_Action);
  btn_8.attachDoubleClick(&doubleClick_Action);
  btn_8.attachLongPressStop(&pressStop_Action);
  btn_8.attachLongPressStart(&pressStart_Action);
  btn_8.attachDuringLongPress(&duringLongPress_Action);
  btn_8.attachRelease(&release_Action);
}

void loop() {
  // put your main code here, to run repeatedly:
  VIETDUINO_UPDATE;
}

void click_Action(){
  Serial.println("_CLICKED_");
}

void doubleClick_Action(){
  Serial.println("_DOUBLE_CLICKED_");
}

void pressStart_Action(){
  Serial.println("_PRESSED_");
}

void pressStop_Action(){
  Serial.println("_LONG_CLICKED_");
}

void duringLongPress_Action(){
  Serial.println("_DURING_LONG_PRESSED_");
}

void release_Action(){
  Serial.println("_RELEASE_");
}
