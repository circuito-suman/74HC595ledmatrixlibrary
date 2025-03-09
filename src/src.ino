#include "LEDMatrix.h"
LEDMatrix ledMatrix;
const char *ssid = "real";           // your wifi ssid
const char *password = "suman saha"; // your wifi password

unsigned long previousMillis = 0;
const unsigned long interval = 1;

void setup()
{
  ledMatrix.begin(ssid, password);
  ledMatrix.loadString("initiated");
  ledMatrix.scrollLeftToRight(8); // 8 is the optimal speed
  ledMatrix.clearDisplay();
} 
void loop()
{
 ledMatrix.loadString("LOOP/");
 ledMatrix.scrollUpToDown(8); 
 ledMatrix.clearDisplay();
 ledMatrix.but(); // for handling wifi switching
}
