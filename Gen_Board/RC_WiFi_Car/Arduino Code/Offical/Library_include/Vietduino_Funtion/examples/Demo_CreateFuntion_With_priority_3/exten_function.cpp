#include "exten_function.h"

CREATE_FUNCTION(myVoid3,3) {
  Serial.begin(9600);

  while(1){
    Serial.println("exten_function 1000");
    M_DELAY(1000);
    RunLed.enable();

    while(RunLed.available())M_DELAY(1);
    
    Serial.println("exten_function 2000");
    
    M_DELAY(1000);
    
    RunLed.enable();
    
    while(RunLed.available())M_DELAY(1);
  }
  
  END_CREATE_FUNCTION
}

CREATE_FUNCTION(RunLed){
  pinMode(LED, OUTPUT);
  
  while(1){
    digitalWrite(LED, 1);
    M_DELAY(100);
    digitalWrite(LED, 0);
    M_DELAY(100);
  
    static uint8_t count = 0;
    count++;
    if(count >= 4){
      RunLed.disable();
      count = 0;
    }  
  }
  

  END_CREATE_FUNCTION
}

CREATE_FUNCTION(ReadSerial){
  if(Serial.available()){
      String kk = Serial.readStringUntil('\n');
      if(kk.indexOf("run") > -1){
        myVoid3.enable();
      }else if(kk.indexOf("stop") > -1){
        myVoid3.disable();
      }
  }
  END_CREATE_FUNCTION
}
