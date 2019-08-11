#include "EPROM_Gen.h"
#include <EEPROM.h>

uint8_t addrid = 0;

EPROM_Gen::EPROM_Gen()
{
}

void EPROM_Gen::begin() {
  EEPROM.begin(512);
}

void EPROM_Gen::write(String id, String pw) {
  //  Clear EPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  //  Write SSID
  for (int i = ADDRID ; i < id.length(); i++) {
    EEPROM.write(i, id[i]);
  }
  //  Write PW
  for (int i = ADDRID ; i < pw.length(); i++) {
    EEPROM.write(ADDRPW + i, pw[i]);
  }
  EEPROM.commit();
  EEPROM.end();
}
String EPROM_Gen::readId() {
  b_ssid = "";
  for (int i = ADDRID; i < ADDRPW; i++) {
    b_ssid += char(EEPROM.read(i));
  }
  b_ssid.trim();
  return b_ssid.c_str();
}

String EPROM_Gen::readPw() {
  b_pass = "";
  for (int i = ADDRPW; i < ADDFN; i++) {
    b_pass += char(EEPROM.read(i));
  }
  b_pass.trim();
  return b_pass.c_str();
}
