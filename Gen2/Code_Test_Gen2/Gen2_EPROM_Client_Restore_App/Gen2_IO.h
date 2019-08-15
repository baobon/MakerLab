#include "Vietduino_Manager.h"
#include "Vietduino_NewFunction.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Gen_EPROM.h"
#include "Gen_Voltage.h"
#include "Gen_SplitStr.h"

#define SPEED       "Speed"
#define DIREC       "Direction"
#define SERVO_ONE   "Servo_one"
#define SERVO_TWO   "Servo_two"
#define LED         "Led"

#define RUNSET      "RunSet"
#define CONFIRM     "Confirm"
#define ID          "SSID"
#define PW          "PASS"

//Constructor
extern Gen_EPROM Eprom;
extern Gen_SplitStr handing;
extern Gen_Voltage vol;
extern ESP8266WebServer server;

extern String command;
extern String lastcommand;

//Value of APIKEY Controller
extern uint8_t  g_Speed;
extern uint8_t  g_Direction;
extern uint8_t  g_Servo_one;
extern uint8_t  g_Servo_two;
//Value of Camera
extern uint8_t  g_Led;
//Value of APIKEY Config
extern uint8_t  g_Runset;
extern uint8_t  g_Confirm;
extern String   g_SSID;
extern String   g_PASS;

//Value of controller
extern uint8_t  g_Controller;
