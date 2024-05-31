/*

//randompixel  example
//by SUMAN SAHA
//my repo https://github.com/circuito-suman/74HC595ledmatrixlibrary

#include "LEDMatrix.h"

LEDMatrix ledMatrix;

const char* wifiSSID = "real"; // your WiFi SSID
const char* wifiPassword = "suman saha"; // your WiFi password



// Timer for the update
unsigned long lastUpdateMicros = 0;

// Structure for dot position
struct DotPosition {
  unsigned int x : 3;
  unsigned int y : 5;
} dotPosition;

void updateDotPosition() {
  // Clear the previous dot position
  ledMatrix.setLed(0, dotPosition.x, dotPosition.y, 0);

  // Create a random value (-1 or 1)
  int offset = (random(2) == 1) ? 1 : -1;

  // Add random offset to the position
  if (random(2) == 1)
    dotPosition.x = (dotPosition.x + offset) % 8;
  else
    dotPosition.y = (dotPosition.y + offset) % 8;

  // Set the new dot position on the matrix
  ledMatrix.setLed(0, dotPosition.x, dotPosition.y, 1);
}

void setup() {
  // Initialize the LED matrix with WiFi credentials
  ledMatrix.begin(wifiSSID, wifiPassword);

  // Set the initial dot position
  dotPosition.x = 4;
  dotPosition.y = 4;

  // Seed the random number generator using noise from the analog pin
  randomSeed(analogRead(A0));
}

void loop() {
  // Check if it's time to update the dot position
  if (micros() - lastUpdateMicros >= 100000) {
    lastUpdateMicros = micros();
    updateDotPosition();
  }

  // Draw the LED matrix
  ledMatrix.up();
}

*/
