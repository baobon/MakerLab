#ifndef _GEN_SPLITSTRING_B_
#define _GEN_SPLITSTRING_B_

#include "Arduino.h"
//example_value = splitString(data, "example", "=", ",", 1);
#define START_SYMBOL  "="
#define STOP_SYMBOL   ","
#define OFFSET         1


class Gen_SplitStr {
  public :
    Gen_SplitStr();
    String splitStr(String v_G_motherString, String v_G_Command,
                    String v_G_Start_symbol = START_SYMBOL,
                    String v_G_Stop_symbol = STOP_SYMBOL,
                    unsigned char v_G_Offset = OFFSET);
    String splitString;
    unsigned char tem_Offset;
    unsigned char lenOfCommand;
    int posOfCommand;
    int PosOfStartSymbol;

};

#endif
