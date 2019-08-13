#include "Gen_SplitStr.h"
String data = "HshopWiFiCar=,Speed=Hello,LedRight=1,LedLeft=1,Buzzer=0,Controller=1";
Gen_SplitStr handing;
String speeds;
void setup() {
  Serial.begin(115200);
  Serial.println("Start");
    speeds = handing.splitStr(data, "Speed");
//  speeds = handing.splitStr(data, "Speed", "=", ",", 1);
  //  String speeds = data.splitStr(a,"Speed");
  Serial.println(speeds);


}

void loop() {
  Serial.println(speeds);
  delay(50);

}
