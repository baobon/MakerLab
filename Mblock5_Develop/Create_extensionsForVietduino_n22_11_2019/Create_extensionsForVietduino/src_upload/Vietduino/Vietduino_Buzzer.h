
#ifndef _VIETDUINO_BUZZER_H_
#define _VIETDUINO_BUZZER_H_

#include <inttypes.h>
#include "Arduino.h"
#include "Vietduino_Io.h"
#include "Vietduino_Task.h"


#define VIETDUINO_BUZZER_DEBUG(x)     Serial.println(x);
#define BUZZER_STATE_OFF (0)
#define BUZZER_STATE_ON (1)
#define BUZZER_STATE_WAIT (2)
#define VBUZZER_CHECK_VALID_TIME(value)     min(4294967, value)
#define VIETDUINO_BUZZER_FREQ           (3000)

class Vietduino_Buzzer : public Vietduino_Task
{
  public:
    /**
     * By using this constructor you will be create a perpetual blinker with even on and off time-spans.
     *  outPin - The pin buzzer.
     */
    Vietduino_Buzzer(byte outPin = 3);
// Tạo hàm ảo để xóa bộ nhớ !
    virtual ~Vietduino_Buzzer() {}
     /**
     * Register the led Task to the Vietduino_Manager: start led.
     */

    /*
        On Buzzer && Off Buzzer
    */
    void on();

    void start();
    /**
     * Remove the led Task from the Vietduino_Manager.
     */
    void stop();
    /** The pin will be on for this amount of microseconds. */
    unsigned long onUs;
    /** The pin will be off for this amount of microseconds. */
    unsigned long offUs;
    /** The count of ON states before the task will sleep or be stopped. See delayUs for details. */
    byte count;
    /**
      * After a "count" of ON states the blinker will sleep for this amount of microseconds.
      * Value zero (0) has a special meaning: delay is disabled.
      * If delay is disabled AND count is specified, the task will be automatically removed after the count of ON states.
      */
    unsigned long delayUs;

    byte onLevel;

    bool isRunning();

    void write(unsigned long _ton_, unsigned long _toff_ = 0, byte _count_ = 0, unsigned long _delay_ = 0); // unit ms.
  private:
    void init(byte _outPin, unsigned long onUs, unsigned long offUs, byte count, unsigned long delayUs);

    byte outPin; // Luu chan dang chay -> Khai bao ben innit cpp

    // Khúc này làm gì ???
    // Chạy trong hàm VIETDUINO_UPDATE;
    static void stepState(Vietduino_Task *me);
    byte _counter;
    /** Can be STATE_OFF, STATE_ON, STATE_WAIT */
    byte _state;
    bool _isrun;
    uint8_t _bitMask;
    volatile NK_IO_REG_TYPE *_portRegister;
};

#endif