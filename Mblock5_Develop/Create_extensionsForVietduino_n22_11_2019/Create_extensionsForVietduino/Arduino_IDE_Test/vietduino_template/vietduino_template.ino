/*
* Template used in Mblock 5
*/
#include "Vietduino_NewFunction.h"
#include "Vietduino_Led.h"
#include "Vietduino_Servo.h"
#include "Servo.h"
#include "Vietduino_DCmotor.h"
#include "Vietduino_Button.h"
#include "QTRSensors.h"
#include "OfflineBroadcast.h"
#include "Vietduino_Ultrasonic.h"
#include "OfflineBroadcast_withoutDelay.h"
#include "Vietduino_Buzzer.h"

//lib
Vietduino_Led myLed_13(13,HIGH);
// Vietduino_Servo myServo;
// Vietduino_DCmotor motorL(4,5); // dir pin - speed pin
// Vietduino_Button btn_1;
Vietduino_Buzzer buzzer;



#pragma region qtrcSS

// QTRSensors qtr;
// uint8_t SensorCount = 0;
// uint16_t sensorQTRValues[4];
// const uint8_t pinQTRs[] = {A0, A1, A2, A3};

// uint16_t res=0;
#pragma endregion qtrcSS

OfflineBroadcast_withoutDelay broadcaster;
// OfflineBroadcast broadcaster1;

Vietduino_Ultrasonic sieuam(12);  // trig 12, echo 13


//declare





CREATE_FUNCTION(main_loop){
  Serial.begin(115200);
  Serial.println("Start");
  while(1){
    // Serial.println("1 " + String(millis()));
    // M_DELAY_S(1);
    // Serial.println("0");
    delay(1000);
  }

  END_CREATE_FUNCTION
}

#pragma region readSerial

// CREATE_FUNCTION(read__Serial){
//   delay(100);
//   if(Serial.available()){
//     String kk = Serial.readStringUntil('\n');
//     Serial.println("RECV: " + kk);
//     setCalibrate(kk.toInt());
//   }
//   END_CREATE_FUNCTION
// }

#pragma endregion

#pragma region test led
CREATE_FUNCTION(main_loop2){
  pinMode(13, OUTPUT);
  while(1){
//     // myLed_13.write(100,100);   // sắng tắt tuần hoàn 100ms
//     // _delay(2);
//     // myLed_13.write(0);    // tắt hẳn
//     // _delay(1);
//     // myLed_13.write(100);  // sáng 100ms rồi tắt hẳn
//     // _delay(3);

//     // myLed_13.write(0);
//     // _delay(1);

//     // myLed_13.write(2000,1000,3);  // sáng 2000ms tắt 1000ms tuần hoàn trong 3 lần
//     // _delay(8);
//     // myLed_13.write(100,100,2,1000);   // sáng tắt tuần hoàn 100ms trong 3 lần, mỗi lần cách nhau 1000ms
//     // _delay(4);

//     #pragma region test loi khong tat dc led

    // Serial.println(F("Start blink led:"));
    myLed_13.write(100,100);
    _delay(4);
//     myLed_13.write(2000);
//     _delay(1);
//     myLed_13.write(0);
//     _delay(2);
//     myLed_13.write(100,100,2);
//     _delay(4);

//     #pragma endregion
  }

  END_CREATE_FUNCTION
}
#pragma endregion - test led

#pragma region test Servo
// CREATE_FUNCTION(loop_Servo){
//   myServo.begin(9);

//   while(1){
//     #pragma region test Servo cơ bản ok
//     // myServo.write(0,100);     // Góc 0 tốc độ 100%
//     // M_DELAY_S(2);
//     // myServo.write(180,100);     // Góc 180 tốc độ 100%
//     // M_DELAY_S(2);

//     // myServo.write(0,50);
//     // M_DELAY_S(3);
//     // myServo.write(180,50);
//     // M_DELAY_S(3);
// #pragma endregion
//     myServo.write_for(0,2000);
//     M_DELAY_S(1);
//     myServo.stop();
//     _delay(1);
//     myServo.write(180,99);
//     M_DELAY_S(2);

//   }

//   END_CREATE_FUNCTION
// }


#pragma region doc goc hien tai của servo
// CREATE_FUNCTION(ngatServo){
//   _delay(0.06);
//   // myServo.stop();
//   Serial.println("Current Angle" + String(myServo.getCurrentAngle()));
//   END_CREATE_FUNCTION
// }
#pragma endregion
#pragma endregion

#pragma region Test DCmotor
// CREATE_FUNCTION(main_dcMotor){
  
//   while(1){
//     motorL.write(1, (uint8_t) (50*255/100),1000); // forward, speed %, run for 1000ms then stop
//     M_DELAY_S(3);

//     motorL.write(0, 100,1000);
//     M_DELAY_S(3);
//   }

//   END_CREATE_FUNCTION
// }

#pragma endregion

#pragma region Test button
// CREATE_FUNCTION(main_button){
//   btn_1.begin(8,1);
//   _delay(1);
//   while(1){
    
//     if(btn_1.available(_CLICKED_)){
//       Serial.println(F("btn1 clicked"));
//     }

//     if(btn_1.available(_LONG_CLICKED_)){
//       Serial.println(F("btn1 long clicked"));
//     }

//     if(btn_1.available(_DOUBLE_CLICKED_)){
//       Serial.println(F("btn1 double clicked"));
//     }

//     if(btn_1.available(_PRESSED_)){
//       Serial.println(F("btn1 pressed"));
//     }

//     if(btn_1.available(_DURING_LONG_PRESSED_)){
//       Serial.println(F("btn1 during long press"));
//     }

//     _delay(0);
//   }

//   END_CREATE_FUNCTION
// }

#pragma endregion

#pragma region test QTRSensor
// CREATE_FUNCTION(test_QTRSen){

//   SensorCount = sizeof(pinQTRs);
//   qtr.setTypeRC();
//   qtr.setSensorPins(pinQTRs, SensorCount); // Right to Left
//   // qtr.setSensorPins((const uint8_t[]){A0, A1, A2, A3}, SensorCount); // Right to Left
//   Serial.println("Sensor: Start calibrate");

//   // 2.5 ms RC read timeout (default) * 10 reads per calibrate() call
//   // = ~25 ms per calibrate() call.
//   // Call calibrate() 400 times to make calibration take about 10 seconds.
//   // for (static uint16_t i = 0; i < 400; i++)
//   // {
//     qtr.calibrate();
//   //   delay(0);
//   // }
//   for (uint8_t i = 0; i < SensorCount; i++)
//   {
//     qtr.calibrationOn.minimum[i] = 500; // use for Black line
//     // qtr.calibrationOn.minimum[i] = 250; // use for White line
//     qtr.calibrationOn.maximum[i] = 2500;
//   }

//   while(1){
//     res = qtr.readLineBlack(sensorQTRValues);
//     for(int cf = 0; cf < 4; cf++){
//       Serial.print(sensorQTRValues[cf]);
//       Serial.print("\t");
//     }

//     Serial.print(getCalibrate());
//     Serial.print("\t");

//     Serial.println("Sensor: " +String (res));
//     delay(100);
//   }
//   END_CREATE_FUNCTION
// }

// uint16_t getCalibrate(){
//   uint16_t temVal = 2500;
//   for (uint8_t i = 0; i < SensorCount; i++)
//   {
//     temVal = min(qtr.calibrationOn.minimum[i],temVal);
//   }
//   return temVal;
// }

// void setCalibrate(uint16_t _min_Value___){
//   for (uint8_t i = 0; i < SensorCount; i++)
//   {
//     qtr.calibrationOn.minimum[i] = _min_Value___;
//   }
// }

#pragma endregion

#pragma region Test OfflineBroadcast.h over Serial

// // Vietduino_Queue <Listener_Broadcast> spriteMessage;
// // String broadcastValue_1 = "";
// void broadcastHandler(){
//   // broadcaster.broadcast(String("hoho"),String("1"));
//   // broadcaster.broadcast(String("message"),String(broadcaster.broadcastValue));
//   // broadcastValue_1 = broadcaster.broadcastValue;

//   broadcaster.callOK();
// }

// // CREATE_FUNCTION(when_broadcastValueAvailable){
// //   if(broadcastValue_1 != ""){
// //     broadcaster.broadcast(String("message"),String(broadcastValue_1));
// //     delay(100);
// //     broadcastValue_1 = "";
// //   }
// //   END_CREATE_FUNCTION
// // }

// // void sendBroadcast(String msg, String value){ // Chưa chay duoc
// //   static Listener_Broadcast tempValueSendMessageQueue;
// //   tempValueSendMessageQueue.msg = msg;
// //   tempValueSendMessageQueue.value = value;
// //   spriteMessage.push(tempValueSendMessageQueue);
// //   // Serial.println(F("push"));
// // }
// CREATE_FUNCTION(testbroadcast){
//   // spriteMessage.setPrinter(Serial);
//   broadcaster.on(String("message"),broadcastHandler);
//   broadcaster.on(String("message3"), broadcastHandler);

//   while(1){
//     broadcaster.broadcast(String("message"),String("maybay"));
//     delay(500);
//     broadcaster.broadcast(String("message"),String("panda"));
//     delay(500);

//     // sendBroadcast(String("message"),String("maybay2"));  // chưa chay dc
//     // delay(1100);
//     // sendBroadcast(String("message"),String("pad"));
//     // delay(1100);
//     // sendBroadcast(String("message"),String("may"));
//     // delay(1100);
//   }
  
//   END_CREATE_FUNCTION
// }

// // CREATE_FUNCTION(loop_BroadcastSendMessage){   // chưa chay dươc
// //   if(!spriteMessage.isEmpty()){
// //     Serial.println(F("Start send"));
// //     static Listener_Broadcast tempValueSendMessageQueue;// = spriteMessage.pop();
// //     tempValueSendMessageQueue = spriteMessage.pop();
// //     broadcaster.broadcast(tempValueSendMessageQueue.msg,tempValueSendMessageQueue.value);
// //     Serial.print(F("data: "));
// //     Serial.print(tempValueSendMessageQueue.msg);
// //     Serial.print("\t");
// //     Serial.println(tempValueSendMessageQueue.value);
// //     Serial.println(F("sending!"));
// //     delay(100);
// //     // Serial.println(F("sending!"));
// //   }
// //   END_CREATE_FUNCTION
// // }

// CREATE_FUNCTION(testRecieveBroadcast){  // Chưa chay dc
//   if(broadcaster.checkMessage("message3")){
//     broadcaster.broadcast(String("message2"),String( broadcaster.getMessageValue("message3")));
//     delay(500);
//   }
//   END_CREATE_FUNCTION
// }

// CREATE_FUNCTION(loop_Broadcast){
//   broadcaster.loop();
//   // broadcaster1.loop();
//   END_CREATE_FUNCTION
// }

#pragma endregion Test OfflineBroadcast.h over Serial

#pragma region test Ultrasonic hc-04
// CREATE_FUNCTION(Test_SieuAm_HC_04){
//   int distance = sieuam.getMeasure();
//   Serial.print("Trig pin:" + String(sieuam.trig_pin));
//   Serial.print("\t");
//   Serial.print("Echo pin:" + String(sieuam.echo_pin));
//   Serial.print("\t");

//   Serial.println(distance);
//   delay(10);
//   END_CREATE_FUNCTION
// }
#pragma endregion

#pragma region test block cua broadcast

CREATE_FUNCTION(runBuzzer){
  // //  Run buzzer only 2s
  // buzzer.write(2000);
  // M_DELAY(3000);
  // //  Run buzzer on
  // buzzer.on();
  //  M_DELAY(3000);
  // //   Buzzer off
  // buzzer.stop();
  //  M_DELAY(3000);
  //  Buzzer blink 100
  // buzzer.write(100,100);
  //  M_DELAY(3000);
  // //  Buzzer blink 100 ,  2 count 
  // buzzer.write(100,100,2);
  //  M_DELAY(3000);
  // //  Buzzer blink 100 , 2 count , 1s repeat
  // buzzer.write(100,100,2,1000);
  //  M_DELAY(3000);

   while(1){
  buzzer.on();
   M_DELAY(100);
  buzzer.stop();
   M_DELAY(100);
   }
  
  END_CREATE_FUNCTION
}

#pragma endregion test block cua broadcast



