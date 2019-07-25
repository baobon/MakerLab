#include "Vietduino_NewFunction.h"
#include "Vietduino_Manager_Priority.h"

void myVoid(Vietduino_Task * me);
void myVoid2(Vietduino_Task * me);

Vietduino_NewFunction tt(myVoid, &Vietduino_Manager_3);
Vietduino_NewFunction tt2(myVoid2, &Vietduino_Manager_3);

int LED = 13;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  Serial.begin(9600);
  VIETDUINO_UPDATE;
}

void loop() {
    // put your main code here, to run repeatedly:
//  VIETDUINO_UPDATE;
}

void myVoid(Vietduino_Task * me) {
  M_LOOP() {
    digitalWrite(LED, 1);
    M_DELAY(100);
    digitalWrite(LED, 0);
    M_DELAY(100);
  }
}

CREATE_FUNCTION(myVoid3,2) {
  Serial.println(1000);
  M_DELAY(1000);
  Serial.println(2000);
  M_DELAY(1000);
  END_CREATE_FUNCTION
}

CREATE_FUNCTION(myVoid4,1) {
  Serial.println(1100);
  M_DELAY(1000);
  Serial.println(2200);
  M_DELAY(1000);
  END_CREATE_FUNCTION
}

void myVoid2(Vietduino_Task * me) {
  M_LOOP() {
    Serial.println(1);
    M_DELAY(1000);
    Serial.println(2);
    M_DELAY(1000);
  }
}
