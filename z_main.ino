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

  init_wind();

  do_sensor();
}

//--------------------------------------------------------------------------
void loop() {
  check_wifi_conn();

  check_ota();

  if (go_metro_meas.check() == 1) {

    do_sensor();
    send_vals();

  }

  delay(500);
}
