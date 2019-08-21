#include "Vietduino_Manager.h"
#include "Vietduino_NewFunction.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "Gen_EPROM.h"
#include "Gen_Voltage.h"
#include "Gen_SplitStr.h"
#include "Vietduino_DCmotor.h"
#include "Vietduino_Servo.h"

/*
   Debug
*/

/* Uncomment to enable printing out nice debug messages. */
#define RESTORE_GEN

#define DEBUG_PRINTER Serial /**< Define where debug output will be printed. */
/* Setup debug printing macros. */
#ifdef RESTORE_GEN
#define GEN_PRINT(...) { DEBUG_PRINTER.print(__VA_ARGS__); }
#define GEN_PRINTLN(...) { DEBUG_PRINTER.println(__VA_ARGS__); }
#else
#define GEN_PRINT(...) {} /**< Debug Print Placeholder if Debug is disabled */
#define GEN_PRINTLN(...) {} /**< Debug Print Line Placeholder if Debug is disabled */
#endif




#define SPEED       "Speed"
#define DIREC       "Direction"
#define SERVO_ONE   "Servo_one"
#define SERVO_TWO   "Servo_two"
#define LED         "Led"

#define RUNSET      "RunSet"
#define CONFIRM     "Confirm"
#define ID          "SSID"
#define PW          "PASS"

//Motor 
#define TIME_RUN     (2000)
#define BACK_WARD       (1)
#define FOR_WARD        (0)
#define LEFT_MOTOR      (3)
#define RIGHT_MOTOR     (4)

//Servo
#define SERVO_ONE_PIN   12    // D6
#define SERVO_TWO_PIN   13    // D7

//Constructor
extern Vietduino_DCmotor motorLeft;
extern Vietduino_DCmotor motorRight;
extern Gen_EPROM Eprom;
extern Gen_SplitStr handing;
extern Gen_Voltage vol;
extern Vietduino_Servo servo_one;
extern Vietduino_Servo servo_two;


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
