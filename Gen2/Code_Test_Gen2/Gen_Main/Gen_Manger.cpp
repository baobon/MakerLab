/*
    This MAIN of Project
 */

#include "Gen_Manager.h"
#include "Gen_Debug.h"
#include "Voltage_Task.h"
#include "Camera_Task.h"
// #include "Gen_IO.h"

/*
    Value
 */

//Value of Camera
String s_id, s_pw;
uint8_t g_Led = 0;
//Value of APIKEY Controller
uint8_t g_Speed = 0;
uint8_t g_Direction = 5;
uint8_t g_Servo_one = 90;
uint8_t g_Servo_two = 90;
//Value of APIKEY Config
uint8_t g_Runset = 0;
uint8_t g_Confirm = 0;
String g_SSID = "";
String g_PASS = "";
//Value of Controller
uint8_t g_Controller = 0;
//Value of Config
unsigned long cf_time_led = 0;
unsigned long cf_time_rst;

String command;

/*
    Constructor
 */
Gen_EPROM Eprom(PIN_BUTTON_RESTORE, PIN_LED_STATUS);
ESP8266WebServer server(80);
Gen_SplitStr handing;
// void HTTP_handleRoot(void);

/*
--------------------------------------------------------------------------------------------------------
 */

// **-----> This Funtion to CreatWifi && Read Data Send from App Phone ! <------**
CREATE_FUNCTION(WiFi_ReadCommand)
{
  Eprom.begin();
  WiFi.mode(WIFI_AP);
  s_id = Eprom.readId();
  s_pw = Eprom.readPw();
  WiFi.softAP(s_id, s_pw);
  GEN_PRINTLN();
  GEN_PRINT("ssid : ");
  GEN_PRINTLN(Eprom.readId());
  GEN_PRINT("pass : ");
  GEN_PRINTLN(Eprom.readPw());
  IPAddress myIP = WiFi.softAPIP();
  server.on("/", HTTP_handleRoot);
  server.onNotFound(HTTP_handleRoot);
  server.begin();
  while (!false)
  {
    server.handleClient();
    command = server.arg("Makershop");
    if (command != "")
    {
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
      g_Led = handing.splitStr(command, LED).toInt();
      runDCMotor(g_Direction, g_Speed);
      command = "";
      M_DELAY(0);
    }
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}

/// This void to send Voltage Data ///
void HTTP_handleRoot(void)
{

  if (server.hasArg("Makershop"))
  {
    Serial.println(server.arg("Makershop"));
  }
  server.send(200, "text/html", "Voltage=" + voltage + ",  IPAddress=" + c_ipaddress);
  // GEN_PRINTLN(c_ipaddress);
}

// **-----> This Funtion to help user Restore App to Default ! <------**
CREATE_FUNCTION(RestoreGen)
{
  Eprom.waitRestore(SSID_NORMAL, PASS_NORMAL);
    GEN_PRINTLN(c_ipaddress);
  M_DELAY(1000);
  END_CREATE_FUNCTION
}

// **-----> This Funtion to help user Config from Phone ! <------**
CREATE_FUNCTION(ConfigApp)
{
  if (g_Runset != 99 && g_Confirm != 99)
  {
    cf_time_rst = millis();
    // GEN_PRINTLN("Cf_time_Rst : " + String(cf_time_rst));
    M_DELAY(0);
  }
  else if (g_Runset == 99 && g_Confirm == 99)
  {
    if (millis() - cf_time_led >= TIME_LED_CONFIG)
    {
      cf_time_led = millis();
      digitalWrite(PIN_LED_STATUS, !digitalRead(PIN_LED_STATUS));
      M_DELAY(0);
    }
    if (millis() - cf_time_rst >= TIME_CONFIG_RESET)
    {
      Eprom.write(g_SSID, g_PASS);
      ESP.restart();
      GEN_PRINTLN("Write EEPROM");
      g_Runset = g_Confirm = 0;
      M_DELAY(0);
    }
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}
