//---------------------------------------------------------------------------
// Wind Sensor
#define PotPin (A0)    // define the input pin for the wind vane potentiometer
#define RPMsensor 4 // = GPIO04 = D2      //The pin location of the anemometer sensor
int Direction ; // Wind direction
const char* DirNames[] = {"N ", "NO", "O ", "SO", "S", "SW", "W", "NW" };
byte DirNameIx;

int PotValue = 0;      // variable to store the value coming from the potentiometer

volatile unsigned long RPMTops;  // RPM tops counter in interrupt routine
volatile unsigned long ContactTime;  // Timer to avoid conatct bounce in interrupt routine
volatile boolean Int1Exit;  //exit INT1 w/o action
float RPM;       // RPM count


//----------------------------------------------------------------------
void Wind_get_dir() {
  // Wind Direction
  PotValue = analogRead(PotPin);     // read the value from the potmeter
  Direction = map(PotValue, 0, 1023, 0, 359);
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
void rpmint()   {

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


