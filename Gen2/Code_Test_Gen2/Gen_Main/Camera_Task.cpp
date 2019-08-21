#include "Camera_Task.h"

#if defined(RUN_CAMERA)

#include "Gen_Manager.h"
#include "Gen_Manager.h"
#include "Gen_Debug.h"
String c_data;
String c_ipaddress;

/*
 *-----> This Funtion to Wait Data Send from App Phone ! <------** 
 */

CREATE_FUNCTION(EPROM_WaitSendData)
{
    while (!false)
    {
        if (Serial.available())
        {
            c_data = mySerial.readStringUntil('\n');
            if (c_ipaddress == "")
            {
                c_ipaddress = handing.splitStr(c_data, IP_ADDRESS);
            }
            // c_ipaddress = handing.splitStr(c_data, IP_ADDRESS);
            // GEN_PRINT(c_ipaddress);
            if (c_data.indexOf("WaitingRead") > -1)
            {
                Serial.println(",Config=99,ssid=" + s_id + ",pass=" + s_pw + ",");
                M_DELAY(0);
            }
            M_DELAY(0);
        }
        M_DELAY(0);
    }
    M_DELAY(0);
    END_CREATE_FUNCTION
}

#else

#endif