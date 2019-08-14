/*
   Tool Board :  ESP32_Wrover_Module
   Partition Scheme : Huge AJPP(3MB_NO_OTA)

*/

#include "Gen2_IO.h"

//Constructor
Gen_EPROM Eprom;
Gen_Voltage vol;
Gen_SplitStr handing;
ESP8266WebServer server(80);

//Value
String command;
String lastcommand = "Gen";
//Value of APIKEY Controller
uint8_t  g_Speed = 0;
uint8_t  g_Direction = 5;
uint8_t  g_Servo_one = 90;
uint8_t  g_Servo_two = 90;
uint8_t  g_Led = 0 ;
//Value of APIKEY Config
uint8_t  g_Runset  = 0;
uint8_t  g_Confirm = 0;
String   g_SSID    = "";
String   g_PASS    = "";

void setup() {
  Serial.begin(115200);
}

void loop() {
  VIETDUINO_UPDATE;
}

// **-----> This Funtion to CreatWifi && Read Data Send from App Phone ! <------**
CREATE_FUNCTION(WiFi_ReadCommand) {
  Eprom.begin();
  WiFi.mode(WIFI_AP);
  WiFi.softAP(Eprom.readId(), Eprom.readPw());
  Serial.println();
  Serial.print("ssid : "); Serial.println(Eprom.readId());
  Serial.print("pass : "); Serial.println(Eprom.readPw());
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  // Starting WEB-server
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();
  Serial.println("Begin Send Data");

  while (!false) {
    server.handleClient();
    command = server.arg("Makershop");
    if (command != "" && command != lastcommand)
    {
      lastcommand = command;
      Serial.println(command);
      // ----> Get data controller to handing from Controller <-------
      g_Speed = (handing.splitStr(command, SPEED)).toInt();
      g_Direction = (handing.splitStr(command, DIREC)).toInt();
      g_Servo_one = (handing.splitStr(command, SERVO_ONE)).toInt();
      g_Servo_two = (handing.splitStr(command, SERVO_TWO)).toInt();
      // ----> Get data config to handing from Config <-----
      g_Runset = (handing.splitStr(command, RUNSET)).toInt();
      g_Confirm = (handing.splitStr(command, CONFIRM)).toInt();
      g_SSID = handing.splitStr(command, ID);
      g_PASS = handing.splitStr(command, PW);
      command = "";
    }
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}

void HTTP_handleRoot(void) {

  if ( server.hasArg("Makershop") ) {
    Serial.println(server.arg("Makershop"));
  }
  server.send ( 200, "text/html", "" );
  //  delay(1);
}
// **-----> This funtion to Handing Controller && Config <--------** //
CREATE_FUNCTION(Controler_Config) {
  //Config
  if (g_Runset == 99 && g_Confirm == 99) {
    Eprom.write(g_SSID, g_PASS);
    digitalWrite(PINLED, LOW); M_DELAY(500);
    digitalWrite(PINLED, !digitalRead(PINLED)); M_DELAY(500);
    digitalWrite(PINLED, !digitalRead(PINLED)); M_DELAY(500);
    digitalWrite(PINLED, !digitalRead(PINLED)); M_DELAY(500);
    digitalWrite(PINLED, !digitalRead(PINLED)); M_DELAY(500);
    digitalWrite(PINLED, !digitalRead(PINLED)); M_DELAY(500);
    digitalWrite(PINLED, !digitalRead(PINLED)); M_DELAY(500);
    M_DELAY(5000);
    ESP.restart();
    g_Runset = g_Confirm = 0;
    Serial.println("Write EEPROM");
  }

  M_DELAY(0);
  END_CREATE_FUNCTION
}


// **-----> This Funtion to Wait Data Send from App Phone ! <------** //
CREATE_FUNCTION(EPROM_WaitSendData) {
  while (!false) {
    if (Serial.available()) {
       String command = Serial.readStringUntil('\n');
       Serial.println(command);
       if(command.indexOf("WaitingRead")>-1){
        String s_id = Eprom.readId();
        String s_pw = Eprom.readPw();
        Serial.println(",Config=99,ssid="+s_id+",pass="+s_pw+",");
       }
    }
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}


// **-----> This Funtion to Wait Data Send from App Phone ! <------** //
CREATE_FUNCTION(EPROM_WaitRestore) {
  while (!false) {
    Eprom.waitRestore();
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}

//**-----> This Funtion to ReadVoltage Gen <-----------**
CREATE_FUNCTION(Gen_ReadVoltage) {
  vol.begin();
  while (!false) {
    //    Serial.println(vol.readV());
    M_DELAY(100);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}
