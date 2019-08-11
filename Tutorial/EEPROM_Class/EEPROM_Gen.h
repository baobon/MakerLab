#ifdef  _EEPROM_GEN_B_
#define _EEPROM_GEN_B_


#define EEPROM_GEN_DEBUG(x) Serial.println(x);

class EEPROM_Gen
{
  public:
    //Constructor
    EEPROM_Gen();
    //Method
    void begin(bool _isRun = true);
    String WriteSSID;
    String WritePASS;
    String ReadSSID;
    String ReadPASS;

    bool isRun;
    
  private:
};

#endif
