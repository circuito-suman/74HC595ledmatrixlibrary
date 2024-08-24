/*
// This example uses udp protocol to receive data which is sent through a python program 
//by SUMAN SAHA
//my repo https://github.com/circuito-suman/74HC595ledmatrixlibrary

#include "LEDMatrix.h"
LEDMatrix ledMatrix;
const char* ssid = "real"; // your wifi ssid
const char* password = "suman saha"; // your wifi password

unsigned long previousMillis = 0;
const unsigned long interval = 1;

void setup() {
  ledMatrix.begin(ssid, password);


}
void loop() {
 
   unsigned long currentMillis = millis();

 if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    if (ledMatrix.ledState == LOW)
      ledMatrix.ledState = HIGH;
    else
      ledMatrix.ledState = LOW;
    digitalWrite(ledMatrix.LED_OUT, ledMatrix.ledState);
    ledMatrix.processPostData();
  }

ledMatrix.drawLedHorizontal();


}

*/







