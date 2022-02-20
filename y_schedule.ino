
void do_sensor   () {

  set_rgb(0, 255, 0);

  // get Wind direction
  Wind_get_dir();
  DebugPrint("Direction: ");
  DebugPrint(Direction);
  DebugPrintln(" °");

  // get Wind speed
  Wind_get_speed();

  DebugPrint("Speed: ");
  DebugPrint(WindSpeedkmh);
  DebugPrintln(" km/h");

  set_rgb(0, 0, 0);

}

void send_vals() {
  set_rgb(0, 0, 255);

  //send_val(14, Direction);
  //send_val(13, WindSpeedkmh);
  pub_sens();

  set_rgb(0, 0, 0);
}
