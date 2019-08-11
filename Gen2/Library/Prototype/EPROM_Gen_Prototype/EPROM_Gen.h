#ifndef _EEPROM_GEN_B_
#define _EEPROM_GEN_B_

#include "Arduino.h"
#define ADDRID  0
#define ADDRPW  30
#define ADDFN   60

class EPROM_Gen {
  public:
    EPROM_Gen();
    void begin();
    void write(String b_id,String b_pass);
    String readId();
    String readPw();
    String b_ssid,b_pass;
};

#endif
