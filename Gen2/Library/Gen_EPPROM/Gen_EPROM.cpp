#include "Gen_EPROM.h"
#include <EEPROM.h>

uint8_t addrid = 0;

Gen_EPROM::Gen_EPROM(uint8_t b_outPin, uint8_t b_outLed , uint8_t b_restore)
{
  this-> outPin = b_outPin;
  this-> outLed = b_outLed;
  this-> restore = b_restore;
  this-> timer_Rst_max = TIME_RS_MAX;
  this-> timer_Rst = TIME_ZERO;
  this-> timer_Led = TIME_ZERO;
  this-> timer_LedMax = TIME_LED_MAX;
}

void Gen_EPROM::begin() {
  EEPROM.begin(512);
  pinMode(this->outPin, INPUT);
  pinMode(this->outLed, OUTPUT);
  DEBUG_PRINTLN(F("Start Debug EPROM_Gen_Restore"));
}


void Gen_EPROM::waitRestore(String w_id,String w_pw) {
  // if(pF_Warning)pF_Warning();

  if (digitalRead(this->outPin) == 1 && this->restore == 1) {
    this->timer_Rst = millis();
  } else if (digitalRead(this->outPin) == 0 && this->restore == 1) {
    if (millis() - this->timer_Led >= this->timer_LedMax) {
      timer_Led = millis();
      digitalWrite(this->outLed, !digitalRead(this->outLed));
    }
    if (millis() - this->timer_Rst >= this->timer_Rst_max)
    {
      write(G_SSID,G_PASS);
      DEBUG_PRINTLN(F("RST Compile"));
      digitalWrite(this->outLed, LOW);
      this->restore = 0;
    }
  }
}


void Gen_EPROM::write(String id, String pw) {
  //  Clear EPROM
  for (int i = 0; i < 512; i++) {
    EEPROM.write(i, 0);
  }
  //  Write SSID
  DEBUG_PRINTLN(F("SSID"));
  for (int i = ADDRID ; i < id.length(); i++) {
    EEPROM.write(i, id[i]);
    DEBUG_PRINT(id);
  }
  //  Write PW
  DEBUG_PRINTLN(F("PASS"));
  for (int i = ADDRID ; i < pw.length(); i++) {
    EEPROM.write(ADDRPW + i, pw[i]);
    DEBUG_PRINT(pw);
  }
  EEPROM.commit();
  EEPROM.end();
  DEBUG_PRINTLN(F("Write Compile"));
}
String Gen_EPROM::readId() {
  b_ssid = "";
  for (int i = ADDRID; i < ADDRPW; i++) {
    b_ssid += char(EEPROM.read(i));
  }
  b_ssid.trim();
  return b_ssid.c_str();
}

String Gen_EPROM::readPw() {
  b_pass = "";
  for (int i = ADDRPW; i < ADDFN; i++) {
    b_pass += char(EEPROM.read(i));
  }
  b_pass.trim();
  return b_pass.c_str();
}
