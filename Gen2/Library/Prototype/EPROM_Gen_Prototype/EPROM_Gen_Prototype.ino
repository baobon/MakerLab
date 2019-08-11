#include "EPROM_Gen.h"

EPROM_Gen Eprom;
String b_id = "HeloMaycung";
String b_pass = "12356789";
void setup() {
  Eprom.begin();
  Serial.begin(115200);
  Serial.println("Start");
  //  Write
  Eprom.write(b_id, b_pass);
  //  Read
  Serial.print("ssid : "); Serial.println(Eprom.readId());
  Serial.print("pass : "); Serial.println(Eprom.readPw());

}

void loop() {
  // put your main code here, to run repeatedly:

}
