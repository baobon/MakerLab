#include "exten_function.h"

#include "Car_Config.h"

String c_buzzer, c_controller, c_speed, c_ledcam;

Vietduino_Led myBuzzer(PIN_BUZZER, ACTIVE_SIGNAL_BUZZER);
Vietduino_Led ledBoard(13, 1);
Vietduino_Servo myServo;

//API KEY  =

CREATE_FUNCTION(B_Main)
{
  ledBoard.write(100, 100 , 2);
  while (1)
  {
    M_DELAY(0);
  }

  END_CREATE_FUNCTION
}

CREATE_FUNCTION(ReadSerial)
{
  wifiSerial.begin(115200);
  DB_SERIAL_KXN("Start");

  while (1)
  {

    if (wifiSerial.available())
    {
      String command = wifiSerial.readStringUntil('\n');
      if (command != "") {
        DB_SERIAL_KXN(command);
        handlingdata(command);
      }
      // DB_SERIAL_KXN(command);
      // handlingdata(command);
    }
    M_DELAY(0);
  }

  END_CREATE_FUNCTION
}

//command=value,    Offset0 = command, offset1 = value
//Update--11/7/2019
#define DB_SPLIT(...) Serial.println(__VA_ARGS__)
#define DB_SPLIT(...)

String splitString(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset)
{
  unsigned char tem_Offset = v_G_Offset - 1;
  unsigned char lenOfCommand = v_G_Command.length();

  int posOfCommand = v_G_motherString.indexOf(v_G_Command);
  int PosOfStartSymbol = v_G_motherString.indexOf(v_G_Start_symbol, posOfCommand + lenOfCommand);
  if (posOfCommand < 0)
    return "";

  // Xu ly Dau Command
  DB_SPLIT(v_G_Command + " posOfCommand " + (String)posOfCommand);
  if (posOfCommand > 0)
  {
    String tem__ = v_G_motherString.substring(posOfCommand - 1, posOfCommand);
    DB_SPLIT("posOfCommand at Start " + tem__);
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
    DB_SPLIT("posOfCommand at Last " + tem__);
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

void handlingdata(String data)
{
  c_speed = splitString(data, "Speed", "=", ",", 1);
  c_buzzer = splitString(data, "Buzzer", "=", ",", 1);
  c_controller = splitString(data, "Controller", "=", ",", 1);
  c_ledcam = splitString(data, "LedCam", "=", ",", 1);
  DB_SERIAL_KXN("_speed: " + c_speed);
  DB_SERIAL_KXN("_buzzer: " + c_buzzer);
  DB_SERIAL_KXN("_controller: " + c_controller);
  DB_SERIAL_KXN("_ledcam: " + c_ledcam);
  c_ledcam == "1" ? Serial.println("ledon") : Serial.println("ledoff");

}

//void checkController(String b_controller, String b_speed,
//                     String b_buzzer, String b_ledLeft, String b_ledRight)
//{
//  // Check Buzzer
//  if (b_buzzer == "1" && myBuzzer.isRunning() == false)
//  {
//    myBuzzer.write(100, 100, 4);
//  }
//  else if (b_buzzer == "0" && myBuzzer.isRunning() == true)
//  {
//    myBuzzer.stop();
//  }
//
//  //Check Light
//  // if (b_ledLeft == "1" && myLedLeft.isRunning() == false)
//  // {
//  //   myLedLeft.write(5000, 1);
//  // }
//  // else if (b_ledLeft == "0" && myLedLeft.isRunning() == true)
//  // {
//  //   myLedLeft.stop();
//  // }
//  // if (b_ledRight == "1" && myLedRight.isRunning() == false)
//  // {
//  //   myLedRight.write(5000, 1);
//  // }
//  // else if (b_ledRight == "0" && myLedRight.isRunning() == true)
//  // {
//  //   myLedRight.stop();
//  // }
//
//  //Check Controller
//  /*
//     Tiến 1    Lùi 2     Phải 3     Trái 4     Tiến Trái 5
//     Tiến Phải 6    Lùi Trái 7    Lùi Phải 8     Dừng 9
//  */
//  int _speed_ = b_speed.toInt() * 2.54;
//  int _controllers_ = b_controller.toInt();
//  static uint8_t tmpDirectionBackward = _V_DIR_BACKWARD_;
//  static uint8_t tmpDirectionForward = _V_DIR_FORWARD_;
//  unsigned long timeMotor = 500;
//  switch (_controllers_)
//  {
//  case 1:
//    // myMotor.forward(_speed_);
//    myLedLeft.write(100, 100, 4);
//    myLedRight.write(100, 100, 4);
//    myMotor.write(tmpDirectionForward, _speed_, timeMotor);
//    myServo.write(SERVO_GO);
//    break;
//  case 2:
//    myLedLeft.write(100, 100, 4);
//    myLedRight.write(100, 100, 4);
//    myMotor.write(tmpDirectionBackward, _speed_, timeMotor);
//    myServo.write(SERVO_GO);
//    break;
//  case 3:
//    myLedRight.write(100, 100, 4);
//    // myLedLeft.stop();
//    myMotor.write(tmpDirectionForward, _speed_, timeMotor);
//    myServo.write(SERVO_RIGHT);
//    break;
//  case 4:
//    myLedLeft.write(100, 100, 4);
//    // myLedRight.stop();
//    myMotor.write(tmpDirectionForward, _speed_, timeMotor);
//    myServo.write(SERVO_Left);
//    break;
//  case 5:
//    myMotor.write(tmpDirectionForward, _speed_, timeMotor);
//    myServo.write(SERVO_GO_LEFT);
//    myLedLeft.write(100, 100, 4);
//    // myLedRight.stop();
//    break;
//  case 6:
//    myMotor.write(tmpDirectionForward, _speed_, timeMotor);
//    myServo.write(SERVO_GO_RIGHT);
//    myLedRight.write(100, 100, 4);
//    // myLedRight.stop();
//    break;
//  case 7:
//    myMotor.write(tmpDirectionBackward, _speed_, timeMotor);
//    myServo.write(SERVO_GO_LEFT);
//    myLedLeft.write(100, 100, 4);
//    // myLedRight.stop();
//    break;
//  case 8:
//    myMotor.write(tmpDirectionBackward, _speed_, timeMotor);
//    myServo.write(SERVO_GO_RIGHT);
//    myLedRight.write(100, 100, 4);
//    // myLedLeft.stop();
//    break;
//  case 9:
//    myMotor.stop();
//    break;
//  }
//}
//
