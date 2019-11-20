#include "Gen_SplitStr.h"

//example_value = splitString(data, "example", "=", ",", 1);

Gen_SplitStr::Gen_SplitStr(){
 
}

String Gen_SplitStr::splitStr(String motherString, String Command,
                              String Start_symbol,
                              String Stop_symbol,
                              unsigned char Offset) {
  tem_Offset = Offset - 1;
  lenOfCommand = Command.length();

  posOfCommand = motherString.indexOf(Command);
  PosOfStartSymbol = motherString.indexOf(Start_symbol, posOfCommand + lenOfCommand);
  if (posOfCommand < 0)
    return "";
  // Xu ly Dau Command
  if (posOfCommand > 0)
  {
    String tem__ = motherString.substring(posOfCommand - 1, posOfCommand);
    if ((tem__ != " ") && (tem__ != Stop_symbol))
    {
      return "";
    }
  }

  // Xu ly cuoi Command
  unsigned int temPosOfLastCommand = posOfCommand + lenOfCommand;
  if (temPosOfLastCommand)
  {
    String tem__ = motherString.substring(temPosOfLastCommand, temPosOfLastCommand + 1);
    if ((tem__ != " ") && (tem__ != Start_symbol))
    {
      return "";
    }
  }

  if (Offset == 0)
  {
    String tem__ = motherString.substring(posOfCommand, PosOfStartSymbol);
    if (tem__ == Command)
    {
      return tem__;
    }
    return "";
  }

  while (tem_Offset > 0)
  {
    tem_Offset--;
    PosOfStartSymbol = motherString.indexOf(Start_symbol, PosOfStartSymbol + 1);
  }

  if (Stop_symbol != "")
  {
    int PosOfStopSymbol = motherString.indexOf(Stop_symbol, PosOfStartSymbol + 1);
    if (PosOfStopSymbol == -1)
    {
      return "";
    }
    else
      ;
    return motherString.substring(PosOfStartSymbol + 1, PosOfStopSymbol);
  }
  else
  {
    return motherString.substring(PosOfStartSymbol + 1);
  }
}
