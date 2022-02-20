void pub_sens() {

  char buffer[256];

  // Allocate the JSON document
  //
  // Inside the brackets, 200 is the RAM allocated to this document.
  // Don't forget to change this value to match your requirement.
  // Use arduinojson.org/v6/assistant to compute the capacity.
  StaticJsonDocument<200> jsondoc;

  // StaticJsonObject allocates memory on the stack, it can be
  // replaced by DynamicJsonDocument which allocates in the heap.
  //
  // DynamicJsonDocument  doc(200);

  // Add values in the document
  //

  // Add the "Brunnen"
  JsonObject wind = jsondoc.createNestedObject("Wind");

  // if (!gv_error) {
  wind["Richtung"] = (int)(Direction);
  wind["RichtungName"] = DirNames[DirNameIx];
  wind["Geschwindigkeit"] = WindSpeedkmh;
  //   wind["Status"] = "OK";
  // } else {
  //   wind["Status"] = "ERROR";
  // }

  int n  = serializeJson(jsondoc, buffer);

  //client.publish(mqtt_pubtopic_sensor, buffer, true);
  client.publish(mqtt_GetTopic_P(gv_ptopic, mqtt_pre_tele, gv_clientname, (PGM_P)F("SENSOR")), buffer, true);
}

void init_mqtt_local( ) {

  init_mqtt(gv_clientname);

}
