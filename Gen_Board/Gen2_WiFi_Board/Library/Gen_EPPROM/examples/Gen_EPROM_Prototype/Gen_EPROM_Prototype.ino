/* 
   This Library for write ssid && write password to EEPROM ESP8266
   read ssid && read password
 *  
   This Library for Restore Gen when user forgot passworld
   When user Press GPIO -> LOW (time 10s) --> Set ssid && pass default
   ssid      = MakerShop_Gen2
   password  = 123456789
   
*/

#include "Gen_EPROM.h"

Gen_EPROM Eprom(0,2);
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
  Eprom.waitRestore(b_id,b_pass);
}

void ReadEEPROM() {
  Serial.print("ssid : "); Serial.println(Eprom.readId());
  Serial.print("pass : "); Serial.println(Eprom.readPw());
}