#include "Gen_Manager.h"
#include "Print_Debug.h"
#include "Restore_Task.h"
#include "Gen_EPROM.h"

extern Gen_EPROM Eprom;
/*
 * **-----> This Funtion to CreatWifi && Read Data Send from App Phone ! <------**
*/


CREATE_FUNCTION(WiFi_Config) {
  String s_id = Eprom.readId();
  String s_pw = Eprom.readPw();
//  WiFi.softAP(Eprom.readId(),Eprom.readPw());
  while (!false) {
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}
