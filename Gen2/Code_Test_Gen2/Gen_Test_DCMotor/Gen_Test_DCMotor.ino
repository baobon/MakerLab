#include "Vietduino_DCmotor.h"
#include "Vietduino_Manager.h"
#include "Vietduino_NewFunction.h"

Vietduino_DCmotor motorLeft(3);
Vietduino_DCmotor motorRight(4);
int speeds = 40;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
  }
}

void loop() {

  VIETDUINO_UPDATE;

}

CREATE_FUNCTION(myVoid3) {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
    speeds = command.toInt();
  }
  Serial.println("Forward");
  motorRight.write(1, speeds, 4000);
  motorLeft.write(1, speeds, 4000);
  M_DELAY(4000);
  Serial.println("Stop");
  motorRight.stop();
  motorLeft.stop();
  M_DELAY(4000);
  Serial.println("Backward");
  motorRight.write(0, speeds, 4000);
  motorLeft.write(0, speeds, 4000);
  M_DELAY(4000);
}



}
