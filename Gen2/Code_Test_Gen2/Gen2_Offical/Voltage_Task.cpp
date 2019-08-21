#include "Voltage_Task.h"

#if defined(VOLTAGE_READ)

#include "Print_Debug.h"
#include "Vietduino_NewFunction.h"

Gen_Voltage vol;
String voltage;

/*
 **-----> This Funtion to ReadVoltage Gen <-----------**
 */
CREATE_FUNCTION(Gen_ReadVoltage) {
  vol.begin();
  while (!false) {
    GEN_PRINTLN(voltage);
    voltage = String(vol.readV());
    M_DELAY(1000);
  }
  M_DELAY(0);
  END_CREATE_FUNCTION
}
#else
#include "Vietduino_NewFunction.h"
String voltage;
#endif
