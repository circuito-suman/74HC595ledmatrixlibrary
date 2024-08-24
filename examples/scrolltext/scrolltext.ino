/*

//scroll text example
//by SUMAN SAHA
//my repo https://github.com/circuito-suman/74HC595ledmatrixlibrary

#include "LEDMatrix.h"
LEDMatrix ledMatrix;
const char* ssid = "real"; // your wifi ssid
const char* password = "suman saha"; // your wifi password

void setup() {
  ledMatrix.begin(ssid, password);
  ledMatrix.loadString("initiated");
  ledMatrix.scrollLeftToRight();
}


void loop() {
 ledMatrix.scrollDownToUp();
ledMatrix.scrollLeftToRight();
ledMatrix.scrollRightToLeft();
ledMatrix.scrollUpToDown();
}


*/
