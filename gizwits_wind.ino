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
#include <Metro.h>

#include "cy_weather.h"
#include "wind_tools.h"

const char *gc_hostname = "gizwind";

Metro go_metro_meas(60000); //(60000);

//--------------------------------------------------------------------------------------
void setup() {

  cy_serial::start(__FILE__);

  //----------------------------------
  set_rgb(255, 255, 255);
  delay(1000);

  wifi_init(gc_hostname);
  delay (1000);

  init_ota(gv_clientname);

  set_rgb(0, 0, 0);
  delay (1000);

  // Setup Wind-Sensor
  Int1Exit = true;
  pinMode(RPMsensor, INPUT);
  attachInterrupt(RPMsensor, rpmint, FALLING);

  do_sensor();
}

//--------------------------------------------------------------------------
void loop() {
  check_wifi_conn();

  check_ota();

  if (go_metro_meas.check() == 1) {

    do_sensor();

  }

  delay(500);
}

void do_sensor   () {

  set_rgb(0, 255, 0);

  // get Wind direction
  Wind_get_dir();
  DebugPrint("Direction: ");
  DebugPrint(Direction);
  DebugPrintln(" °");

  send_val(14, Direction);

  // get Wind speed
  Wind_get_speed();

  DebugPrint("Speed: ");
  DebugPrint(RPM);
  DebugPrintln(" km/h");

  send_val(13, RPM);

  set_rgb(0, 0, 0);

}

