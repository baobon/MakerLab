/*
  Mỗi byte của của EEPROM chỉ lưu được giá trị từ 0 - 255
*/

#include <EEPROM.h>
String ssid = "Demo";
String pass = "Pass";
uint8_t addrid = 0;
uint8_t addrpw = 30;
uint8_t addfn = 60;
void setup() {
  Serial.begin(115200);

  EEPROM.begin(512);
  Serial.println("Start");
  ReadEEPROM();
  delay(2000);
  WriteEEPROM();
  delay(2000);
  ReadEEPROM();
}

void loop() {

}

void ReadEEPROM() {

  Serial.println("Read SSID EEPROM");
  String b_ssid = "";
  for (int i = addrid; i < addrpw; i++) {
    b_ssid += char(EEPROM.read(i));
  }
  Serial.print("SSID: ");
  Serial.println(b_ssid.c_str());
  b_ssid.trim();


  Serial.println("Read PASS EEPROM");
  String b_pass = "";
  for (int i = addrpw; i < addfn; i++) {
    b_pass += char(EEPROM.read(i));
  }
  Serial.print("SSID: ");
  Serial.println(b_pass.c_str());
  b_pass.trim();
}

void WriteEEPROM() {
  Serial.println("Clear eeprom");
  for (int i = 0; i < 512; ++i)
  {
    EEPROM.write(i, 0);
  }

  Serial.println("Writing eeprom ssid");
  Serial.print("Wrote: ");
  for (int i = 0 ; i < ssid.length(); i++) {
    EEPROM.write(i, ssid[i]);
    Serial.print(ssid[i]);
  }
  Serial.println();

  Serial.println("Writing eeprom p");
  Serial.print("Wrote: ");
  for (int i = 0 ; i < pass.length(); i++) {
    EEPROM.write(addrpw + i, pass[i]);
    Serial.print(pass[i]);
  }
  Serial.println();

}





//void loop() {
//  // need to divide by 4 because analog inputs range from
//  // 0 to 1023 and each byte of the EEPROM can only hold a
//  // value from 0 to 255.
//  int val = analogRead(A0) / 4;
//
//  // write the value to the appropriate byte of the EEPROM.
//  // these values will remain there when the board is
//  // turned off.
//  EEPROM.write(addr, val);
//
//  // advance to the next address.  there are 512 bytes in
//  // the EEPROM, so go back to 0 when we hit 512.
//  // save all changes to the flash.
//  addr = addr + 1;
//  if (addr == 512) {
//    addr = 0;
//    EEPROM.commit();
//  }
//
//  delay(100);
//}
