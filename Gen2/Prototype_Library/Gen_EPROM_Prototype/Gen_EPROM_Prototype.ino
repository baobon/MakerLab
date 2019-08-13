#include "Gen_EPROM.h"

Gen_EPROM Eprom;
String b_id = "XinChao";
String b_pass = "Makershop";
void setup() {
  Eprom.begin();
  Serial.begin(115200);
  //  Write
  Eprom.write(b_id, b_pass);
  //  Read
  ReadEEPROM();
}

void loop() {
  //Waiting Btn0-> GND to Rest Gen2 to Default
  Eprom.waitRestore();
}

void ReadEEPROM() {
  Serial.print("ssid : "); Serial.println(Eprom.readId());
  Serial.print("pass : "); Serial.println(Eprom.readPw());
}
