//--------------------------------------------------------------------------
// Wifi Modul ESP8266 Beispiel Programm
//--------------------------------------------------------------------------
// Basis war das Beispiel von Ray Wang  http://rayshobby.net/?p=9734
//--------------------------------------------------------------------------
#include <cy_serdebug.h>
#include <cy_serial.h> 

#include "cy_wifi.h"
#include "cy_ota.h"

#include "gizwits.h"

#include "cy_weather.h"

const char *gc_hostname = "gizwind";
