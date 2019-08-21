#include "Servo_Task.h"

#if defined(RUN_SERVO)

#include "Gen_Debug.h"
#include "Vietduino_NewFunction.h"
#include "Gen_Manager.h"

Vietduino_Servo servo_one;
Vietduino_Servo servo_two;

/*
**-----> This Funtion to Run Servo ! <------** //
 */

CREATE_FUNCTION(Run_Servo) {
 servo_one.begin(SERVO_ONE_PIN);
 servo_two.begin(SERVO_TWO_PIN);
 
 while (!false) {
   servo_one.write_for(g_Servo_one, 100);
   servo_two.write_for(g_Servo_two, 100);
   M_DELAY(0);
 }
 M_DELAY(0);
 END_CREATE_FUNCTION
}


#else
/*
  Cần coi lại khúc này sau khi đưa biến voltage ra dùng ở bên Manager;
 */
Vietduino_Servo servo_one;
Vietduino_Servo servo_two;
#endif