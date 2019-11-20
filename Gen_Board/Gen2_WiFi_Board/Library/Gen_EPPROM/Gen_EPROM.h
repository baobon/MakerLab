/* 
   This Library for write ssid && write password to EEPROM ESP8266
   read ssid && read password
 *  
   This Library for Restore Gen when user forgot passworld
   When user Press GPIO -> LOW (time 10s) --> Set ssid && pass default
   ssid      = MakerShop_Gen2
   password  = 123456789
   
*/

#ifndef _EEPROM_GEN_B_
#define _EEPROM_GEN_B_

#include "Arduino.h"

/*
   Debug
*/

/* Uncomment to enable printing out nice debug messages. */
//#define RESTORE_DEBUG

#define DEBUG_PRINTER Serial /**< Define where debug output will be printed. */
/* Setup debug printing macros. */
#ifdef RESTORE_DEBUG
#define DEBUG_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define DEBUG_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
#define DEBUG_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
#define DEBUG_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif

/*
   Default
   SSID : MakerShop_Gen2
   PASS : 123456789
*/
#define G_SSID  "MakerShop_Gen2"
#define G_PASS    "123456789"

/*
   PIN  && VALUE
   EEPROM
*/

#define ADDRID  0
#define ADDRPW  30
#define ADDFN   60

/*
   PIN  && VALUE
   RESTORE
*/

#define DEFAULTPIN         A0
#define PINLED              2
#define TIME_RS_MAX      (10000);
#define TIME_ZERO          (0)
#define TIME_LED_MAX     (100);
extern "C" {
  typedef void (*Warning_Function)();
}

class Gen_EPROM {
  public:
    Warning_Function pF_Warning;
    //  Contructor
    // Gen_EPROM(uint8_t b_outPin , uint8_t b_restore = 1);
    Gen_EPROM(uint8_t b_outPin , uint8_t b_outLed, uint8_t b_restore = 1);
    //  Funtion
    void begin();
    void write(String b_id, String b_pass);
    void waitRestore(String w_ssid,String w_pass);
    String readId();
    String readPw();
    //  Value
    String b_ssid, b_pass,w_ssid,w_pass;
    uint8_t outPin, restore , outLed;
    unsigned long timer_Rst_max;
    unsigned long timer_Rst;
    unsigned long timer_Led;
    unsigned long timer_LedMax;
};

#endif
