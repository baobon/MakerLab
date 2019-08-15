#include "Vietduino_DCmotor.h"
Vietduino_DCmotor motorLeft(3);
Vietduino_DCmotor motorRight(4);
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (!Serial) {
  }
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    Serial.println(command);
//    motorRight.write(1, command.toInt(), 5000);
    motorLeft.forward(command.toInt());
  }


}
