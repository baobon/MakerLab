#include "Vietduino_Led.h"
#include "Vietduino_NewFunction.h"

#define LED13_PIN   13
#define LED13_ACTIVE  HIGH

Vietduino_Led L13(LED13_PIN, LED13_ACTIVE);


void setup() {
  // put your setup code here, to run once:
  
}

void loop() {
  // DO NOT put your code here:
  VIETDUINO_UPDATE;
}

CREATE_FUNCTION(runLed){
  L13.write(2000);
  M_DELAY(3000);
  L13.write(300, 300, 4);
  M_DELAY(5000);
  L13.write(100, 100, 5, 1000);
  M_DELAY(7000);
  
  END_CREATE_FUNCTION
}
