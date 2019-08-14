#include "EEPROM.h"

String b_id = "MakerShop_Gen2";
String b_pass = "123456789";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  EEPROM.begin(512);

  writeEEPROM();
  delay(3000);
  readEEPROM();
  
}

void loop() {
  // put your main code here, to run repeatedly:

}

void readEEPROM() {
  Serial.println("SSID = " + EEPROM.readString(0));
  Serial.println("SSID = " + EEPROM.readString(30));
}

void writeEEPROM() {
  
  
  EEPROM.writeString(0, b_id);
  EEPROM.writeString(30, b_pass);
  EEPROM.commit();
}
