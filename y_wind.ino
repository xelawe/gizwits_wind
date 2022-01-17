//----------------------------------------------------------------------
void Wind_get_dir() {
  // Wind Direction
  PotValue = analogRead(PotPin);     // read the value from the potmeter
  DebugPrintln(PotValue);
  Direction = map(PotValue, 0, 994, 0, 359);
  Direction = constrain(Direction, 0, 360);
  if (Direction == 360) {
    Direction = 0;
  }
 
  if ((Direction) < 23) {
    DirNameIx = 0;  // N
  }
  if ((Direction > 22) && (Direction < 68)) {
    DirNameIx = 1;  // NE
  }
  if ((Direction > 67) && (Direction < 113)) {
    DirNameIx = 2;  // E
  }
  if ((Direction > 112) && (Direction < 158)) {
    DirNameIx = 3;  // SE
  }
  if ((Direction > 157) && (Direction < 203)) {
    DirNameIx = 4;  // S
  }
  if ((Direction > 202) && (Direction < 247)) {
    DirNameIx = 5;  // SW
  }
  if ((Direction > 246) && (Direction < 292)) {
    DirNameIx = 6;  // W
  }
  if ((Direction > 291) && (Direction < 337)) {
    DirNameIx = 7;  // NW
  }
  if ((Direction > 336) && (Direction <= 360)) {
    DirNameIx = 0;  // N
  }
  DebugPrintln(DirNames[DirNameIx]);
}

//----------------------------------------------------------------------
void Wind_get_speed() {

  // measure RPM
  Int1Exit = true; //Disable int1
  RPMTops = 0;   //Set NbTops to 0 ready for calculations
  Int1Exit = false; //Enables int1
  delay(3000);
  Int1Exit = true; //Disable int1

  // convert to km/h
  if ((RPMTops >= 0) and (RPMTops <= 21)) {
    RPM = RPMTops * 1.2;
  }
  if ((RPMTops > 21) and (RPMTops <= 45)) {
    RPM = RPMTops * 1.15;
  }
  if ((RPMTops > 45) and (RPMTops <= 90)) {
    RPM = RPMTops * 1.1;
  }
  if ((RPMTops > 90) and (RPMTops <= 156)) {
    RPM = RPMTops * 1.0;
  }
  if ((RPMTops > 156) and (RPMTops <= 999)) {
    RPM = RPMTops * 1.0;
  }

}


//--------------------------------------------------------------------
// This is the function that interrupt calls to measure  RPM
void ICACHE_RAM_ATTR rpmint()   {

  // Exit interrupt w/o action?
  if ( Int1Exit ) {
    return;
  }

  if ((millis() - ContactTime) > 15 ) {  // debounce of REED contact. With 15ms speed more than 150 km/h can be measured
    RPMTops++;
    ContactTime = millis();
  }
}
// end of RPM measure
