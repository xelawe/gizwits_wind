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
