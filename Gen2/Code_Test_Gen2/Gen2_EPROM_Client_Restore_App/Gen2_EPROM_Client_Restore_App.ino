/*
   Tool Board :  ESP32_Wrover_Module
   Partition Scheme : Huge AJPP(3MB_NO_OTA)

*/



#include "Gen2_IO.h"

//Constructor
Gen_EPROM Eprom;
Gen_Voltage vol;
Gen_SplitStr handing;
Vietduino_DCmotor motorLeft(3);
Vietduino_DCmotor motorRight(4);
Vietduino_Servo servo_one;
Vietduino_Servo servo_two;

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
//Value of Controller
uint8_t  g_Controller = 0;

//Value of Led

String voltage;

//EEPROM
String s_id;
String s_pw;

void setup() {
  Serial.begin(115200);
  motorLeft.stop();
  motorRight.stop();
}

void loop() {
  VIETDUINO_UPDATE;
}

// **-----> This Funtion to Debug App ! <------** //
CREATE_FUNCTION(Debug_Gen) {
  while (!false) {
    //    Serial.println(g_Controller);
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}


// **-----> This Funtion to CreatWifi && Read Data Send from App Phone ! <------**
CREATE_FUNCTION(WiFi_ReadCommand) {
  Eprom.begin();
  WiFi.mode(WIFI_AP);
  s_id = Eprom.readId();
  s_pw = Eprom.readPw();
  WiFi.softAP(s_id, s_pw);
  GEN_PRINTLN();
  GEN_PRINT("ssid : "); GEN_PRINTLN(s_id);
  GEN_PRINT("pass : "); GEN_PRINTLN(s_pw);
  IPAddress myIP = WiFi.softAPIP();
  GEN_PRINT("AP IP address: ");
  GEN_PRINTLN(myIP);
  // Starting WEB-server
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();
  GEN_PRINTLN("Begin Send Data");
  while (!false) {
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
      /*
         Controller in here
      */
      //
      GEN_PRINT("Servo_one.write(" + String(g_Servo_one) + ")");
      //      Serial.print("Servo_one.write(" + String(g_Servo_one) + ")");
      GEN_PRINT("    ");
      //      Serial.print("   ");
      //Servo_two
      GEN_PRINT("Servo_two.write(" + String(g_Servo_two) + ")");
      GEN_PRINT("   ");
      //Speed
      GEN_PRINT("Speed = " + String(g_Speed));
      GEN_PRINT("   ");
      //
      //      g_Direction == 1 ? GEN_PRINT("1->Left")    :
      //          g_Direction == 2 ? GEN_PRINT("2->Right") :
      //              g_Direction == 3 ? GEN_PRINT("3->Forward") :
      //                  g_Direction == 4 ? GEN_PRINT("4->Backward") :
      //                      GEN_PRINT("5->Stop");


      //      runDCMotor(g_Direction, g_Speed);

      M_DELAY(0);

      /*
         End Controller
      */

      command = "";
    }
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}
/// This void to send Data ///
void HTTP_handleRoot(void) {

  if ( server.hasArg("Makershop") ) {
    //    Serial.println(server.arg("Makershop"));
  }
  server.send ( 200, "text/html", "Voltage=" + voltage );
}
// **-----> This funtion to Handing Controller && Config <--------** //
CREATE_FUNCTION(Controler_Config) {
  //Config
  if (g_Runset == 99 && g_Confirm == 99) {
    Eprom.write(g_SSID, g_PASS);
    pinMode(PINLED, OUTPUT);
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
    GEN_PRINTLN("Write EEPROM");
  }

  M_DELAY(0);
  END_CREATE_FUNCTION
}

//Serial.println(",Led=" + String(g_Led) + ",");

// **-----> This Funtion to Send Status Led to Camera ! <------** //
CREATE_FUNCTION(Send_Camera) {
  int statusLed = 1;
  while (!false) {
    if (g_Led == 1 && statusLed == 1) {
      Serial.println(",Led=" + String(g_Led) + ",");
      statusLed = 0;
    } else if (g_Led == 0 && statusLed == 0) {
      Serial.println(",Led=" + String(g_Led) + ",");
      statusLed = 1;
    }
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}



// **-----> This Funtion to Wait Data Send from App Phone ! <------** //
CREATE_FUNCTION(EPROM_WaitSendData) {
  while (!false) {
    if (Serial.available()) {
      String command = Serial.readStringUntil('\n');
      //      Serial.println(command);
      if (command.indexOf("WaitingRead") > -1) {
        Serial.println(",Config=99,ssid=" + s_id + ",pass=" + s_pw + ",");
      }
      M_DELAY(0);
    }
    M_DELAY(0);
    END_CREATE_FUNCTION
  }
}


//// **-----> This Funtion to Controller Gen when App Phone send Data ! <------** //
//CREATE_FUNCTION(DC_Motor_Controller) {
//  //  motorLeft.stop();
//  //  motorRight.stop();
//  while (!false) {
//    GEN_PRINTLN("g_Direction = " +String(g_Direction));
//    switch (g_Direction) {
//      case 1:
//        motorRight.write(1, g_Speed, 1000);
//        //        Serial.println("Left");
//        break;
//      case 2:
//        motorLeft.write(1, g_Speed, 1000);
//        //        Serial.println("Right");
//        break;
//      case 3:
//        motorRight.write(1, g_Speed, 1000);
//        motorLeft.write(1, g_Speed, 1000);
//        //        Serial.println("Forward");
//        break;
//      case 4:
//        motorRight.write(0, g_Speed, 1000);
//        motorLeft.write(0, g_Speed, 1000);
//        //        Serial.println("Backward");
//        break;
//      default:
//       GEN_PRINTLN("STOP STOP STOP");
//        motorLeft.stop();
//        motorRight.stop();
//        break;
//    }
//    M_DELAY(0);
//  }
//  M_DELAY(0);
//  END_CREATE_FUNCTION
//}




// **-----> This Funtion to Run Servo ! <------** //
CREATE_FUNCTION(Run_Servo) {
  servo_one.begin(SERVO_ONE_PIN);
  servo_two.begin(SERVO_TWO_PIN);
  while (!false) {
    servo_one.write_for(g_Servo_one, 10);
    servo_two.write_for(g_Servo_two, 10);
    M_DELAY(0);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}




// **-----> This Funtion to Wait Data Send from App Phone ! <------** //
CREATE_FUNCTION(EPROM_WaitRestore) {
  while (!false) {
    //    Eprom.waitRestore();
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
    voltage = String(vol.readV());
    //    server.send ( 200, "text/html", voltage);
    M_DELAY(1000);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}


void runDCMotor(int direc, int speeds) {
  switch (direc) {
    case 1:
      motorRight.write(1, speeds, 1000);
      GEN_PRINTLN("Left");
      break;
    case 2:
      motorLeft.write(1, speeds, 1000);
      GEN_PRINTLN("Right");
      break;
    case 3:
      motorRight.write(1, speeds, 1000);
      motorLeft.write(1, speeds, 1000);
      GEN_PRINTLN("Forward");
      break;
    case 4:
      motorRight.write(0, speeds, 1000);
      motorLeft.write(0, speeds, 1000);
      GEN_PRINTLN("Backward");
      break;
    default:
      GEN_PRINTLN("Stop");
      motorLeft.stop();
      motorRight.stop();
      break;
  }
}
