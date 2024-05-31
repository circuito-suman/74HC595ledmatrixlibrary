//scroll text that is recieved over wifi example
//by SUMAN SAHA
//my repo https://github.com/circuito-suman/74HC595ledmatrixlibrary
#include <ESP8266WebServer.h>
#include "webserver.h"

#include "LEDMatrix.h"
LEDMatrix ledMatrix;
const char* ssid = "real"; // your wifi ssid
const char* password = "suman saha"; // your wifi password


// Create an instance of the ESP8266WebServer
ESP8266WebServer server(80);

// Variable to store input text
String inputText = "";
String scrollDirection = "left";
int scrollspeed =20;
// Function to handle the root page
void handleRoot() {
  String page=html;

  server.send(200, "text/html", page);
}


void handleUpdateText() {
  if (server.hasArg("text")) {
    inputText = server.arg("text");
    ledMatrix.loadString(inputText.c_str());
    Serial.println("Received text: " + inputText);
    server.send(200, "text/html", text);
  }
  else {
    server.send(400, "text/html", error);
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleUpdateDirection() {
  if (server.hasArg("direction")) {
    scrollDirection = server.arg("direction");
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup() {
  ledMatrix.begin(ssid, password);
  server.on("/", handleRoot);
  server.on("/updateText", HTTP_POST, handleUpdateText);
  server.on("/updateDirection", HTTP_POST, handleUpdateDirection);


  server.begin();
 inputText = "open " + WiFi.localIP().toString();
  ledMatrix.loadString(inputText.c_str());
  ledMatrix.scrollLeftToRight(20);
  ledMatrix.loadString(" ");
  ledMatrix.clearDisplay();

}

void loop() {
  server.handleClient();

  //ledMatrix.loadString(inputText.c_str());

  if (scrollDirection == "left") {
ledMatrix.scrollLeftToRight(scrollspeed);
 } else if (scrollDirection == "right") {
ledMatrix.scrollRightToLeft(scrollspeed);
  } else if (scrollDirection == "up") {
ledMatrix.scrollDownToUp(scrollspeed);
  } else if (scrollDirection == "down") {
ledMatrix.scrollUpToDown(scrollspeed); 
  }

}
