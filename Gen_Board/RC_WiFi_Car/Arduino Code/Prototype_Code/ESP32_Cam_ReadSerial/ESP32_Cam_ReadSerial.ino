void setup() {
  Serial.begin(115200);
  while (!Serial) {

  }
  pinMode(4, OUTPUT);
  digitalWrite(4, HIGH);
  delay(500);
  digitalWrite(4, LOW);
  delay(500);
}

void loop() {

  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    if (command != "") {
      handlingdata(command);
    }
  }
}


String splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset)
{
  unsigned char tem_Offset = v_G_Offset - 1;
  unsigned char lenOfCommand = v_G_Command.length();

  int posOfCommand = v_G_motherString.indexOf(v_G_Command);
  int PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol, posOfCommand + lenOfCommand);
  if (posOfCommand < 0)
    return "";

  // Xu ly Dau Command
  //  DB_SPLIT(v_G_Command + " posOfCommand " + (String)posOfCommand);
  if (posOfCommand > 0)
  {
    String tem__ = v_G_motherString.substring(posOfCommand - 1, posOfCommand);
    //    DB_SPLIT("posOfCommand at Start " + tem__);
    if ((tem__ != " ") && (tem__ != v_G_Stop_symbol))
    {
      return "";
    }
  }

  // Xu ly cuoi Command
  unsigned int temPosOfLastCommand = posOfCommand + lenOfCommand;
  if (temPosOfLastCommand)
  {
    String tem__ = v_G_motherString.substring(temPosOfLastCommand, temPosOfLastCommand + 1);
    //    DB_SPLIT("posOfCommand at Last " + tem__);
    if ((tem__ != " ") && (tem__ != v_G_Start_symbol))
    {
      return "";
    }
  }

  if (v_G_Offset == 0)
  {
    String tem__ = v_G_motherString.substring(posOfCommand, PosOfStartSymbol);
    if (tem__ == v_G_Command)
    {
      return tem__;
    }
    return "";
  }

  while (tem_Offset > 0)
  {
    tem_Offset--;
    PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol, PosOfStartSymbol + 1);
  }

  if (v_G_Stop_symbol != "")
  {
    int PosOfStopSymbol = v_G_motherString.indexOf(v_G_Stop_symbol, PosOfStartSymbol + 1);
    if (PosOfStopSymbol == -1)
    {
      return "";
    }
    else
      ;
    return v_G_motherString.substring(PosOfStartSymbol + 1, PosOfStopSymbol);
  }
  else
  {
    return v_G_motherString.substring(PosOfStartSymbol + 1);
  }
}

void handlingdata(String datas)
{
  String led = splitString(datas, "LedCam", "=", ",", 1);
  if (led == "1") {
    digitalWrite(4, HIGH);
  } else if (led == "0") {
    digitalWrite(4, LOW);
  }
}
