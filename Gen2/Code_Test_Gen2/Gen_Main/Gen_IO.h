/*
 * This header to define PIN_BOARD && API DATA
 */

#ifndef __GEN_IO_H_
#define __GEN_IO_H_

#define SERVO_ONE_PIN          (12)
#define SERVO_TWO_PIN          (13)
#define LEFT_MOTOR             (3)
#define RIGHT_MOTOR            (4)
#define PIN_LED_STATUS         (2)
#define PIN_BUTTON_RESTORE     (0)

/*
    Value
 */

//Config from APP
#define TIME_LED_CONFIG          (200)
#define TIME_CONFIG_RESET       (10000)



/*
 * API
 */

#define SPEED       "Speed"
#define DIREC       "Direction"
#define SERVO_ONE   "Servo_one"
#define SERVO_TWO   "Servo_two"
#define LED         "Led"

#define RUNSET      "RunSet"
#define CONFIRM     "Confirm"
#define ID          "SSID"
#define PW          "PASS"
#define SSID_NORMAL        "MakerShop_Gen2"
#define PASS_NORMAL        "123456789"
#define IP_ADDRESS          "IPCAMERA"

/*
 * ENABLE/DISABLE DEBUG
 * Un Comment to DISABLE
 */


//  -->  DC_Motor  <--  //
#define RUN_MOTOR_DC

//  -->  Camera  <--  //
#define RUN_CAMERA

//  -->  Voltage Read  <--  //
#define VOLTAGE_READ

//  -->  Servo Run  <--  //
#define RUN_SERVO


#endif