/*
    This header to Manager library !!!
*/

#ifndef __DEBUG_PROGRAM_H_
#define __DEBUG_PROGRAM_H_

#include "Vietduino_Manager.h"
#include "Vietduino_NewFunction.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


#include "DC_Motor_Task.h"
#include "Gen_IO.h"
#include "Gen_EPROM.h"
#include "Gen_SplitStr.h"

/*
    Serial
 */
#define mySerial Serial

/*
    Task Running hidden
    +    Voltage_Task   -> Send voltage to Manager.cpp
    +    Servo_Task     -> Run servo !
    +    Camera_Task    -> WaitSend(ssid,pass) - > Camera && Send command control led -> Camera
 */


/*
    Value
 */

extern uint8_t  g_Speed;
extern uint8_t  g_Direction;
extern uint8_t  g_Servo_one;
extern uint8_t  g_Servo_two;
//Value of Camera
extern String s_id,s_pw;
extern uint8_t  g_Led;
//Value of APIKEY Config
extern uint8_t  g_Runset;
extern uint8_t  g_Confirm;
extern String   g_SSID;
extern String   g_PASS;
//Value of controller

//Value of Config
extern unsigned long cf_time_led;
extern unsigned long cf_time_rst;

/*
    Constructor
 */
extern Gen_EPROM Eprom;
extern ESP8266WebServer server;
extern Gen_SplitStr handing;
extern void HTTP_handleRoot(void);




#endif