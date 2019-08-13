#include "Gen_Voltage.h"
Gen_Voltage vol;

void setup() {
 vol.begin();
 Serial.begin(115200);

}

void loop() {
  Serial.println(vol.readV());
  delay(10);
}
