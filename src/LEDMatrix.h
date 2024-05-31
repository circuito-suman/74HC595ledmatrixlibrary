#include "core_esp8266_features.h"
#include <stdint.h>
#include "pins_arduino.h"
#ifndef LEDMATRIX_H
#define LEDMATRIX_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
 
#define MATRIX_SIZE 8
#define MATRIX_REGISTERS_INIT_CLEAR 1

class LEDMatrix {
public:
  LEDMatrix();

  void begin(const char* ssid, const char* password, int udpPort = 6868, int clientPort = 6969);
  void processPostData();
  void drawLedHorizontal();
  void drawLedVertical();
  void test();
  void update();
  void shiftLeft(int delayTime);
  void shiftRight(int delayTime);
  void loadString(const char *text);
  void scrollLeftToRight(int n);
  void scrollRightToLeft(int n);
  void scrollUpToDown(int n);
  void scrollDownToUp(int n);


  void shutdown(bool status);
  void clearDisplay();
  void setLed(int addr, int row, int col, boolean state);
  void setRow(int row, byte value);
  void setColumn(int col, byte value);
  void up();
  byte* getBuffer();

private:
  void writeCell(int cols, int rows);
  void writeOutput(int rowVal, int col);
  void brightnesscontrol(int br);
  void displayScroll(int position, int n);
  void displayScrollVertical(int position, int n);





private:
  WiFiUDP UDPServer;


  unsigned int UDPPort;
  unsigned int clientPort;
  
  int ROW_CNT;
  int COL_CNT;
  int PACKAGE_SIZE;
 
  byte *buffer_;
  byte row_;

  byte *_textBytes;
  int _nrLetters;
  int _columnNumbers[8] = {128, 64, 32, 16, 8, 4, 2, 1};
  char _letterPositions[73] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890?! ";
  byte _letters[72][6] = {
  { 0xFE, 0x11, 0x11, 0x11, 0xFE, 0x00}, //  A
  { 0xFF, 0x91, 0x91, 0x91, 0x6E, 0x00}, //  B
  { 0x7E, 0x81, 0x81, 0x81, 0x42, 0x00}, //  C
  { 0xFF, 0x81, 0x81, 0x42, 0x3C, 0x00}, //  D
  { 0xFF, 0x91, 0x91, 0x91, 0x81, 0x00}, //  E
  { 0xFF, 0x90, 0x90, 0x90, 0x80, 0x00}, //  F
  { 0x7E, 0x81, 0x89, 0x89, 0x4E, 0x00}, //  G
  { 0xFF, 0x10, 0x10, 0x10, 0xFF, 0x00}, //  H
  { 0x81, 0x81, 0xFF, 0x81, 0x81, 0x00}, //  I
  { 0x06, 0x01, 0x01, 0x01, 0xFE, 0x00}, //  J
  { 0xFF, 0x18, 0x24, 0x42, 0x81, 0x00}, //  K
  { 0xFF, 0x01, 0x01, 0x01, 0x01, 0x00}, //  L
  { 0xFF, 0x40, 0x30, 0x40, 0xFF, 0x00}, //  M
  { 0xFF, 0x40, 0x30, 0x08, 0xFF, 0x00}, //  N
  { 0x7E, 0x81, 0x81, 0x81, 0x7E, 0x00}, //  O
  { 0xFF, 0x88, 0x88, 0x88, 0x70, 0x00}, //  P
  { 0x7E, 0x81, 0x85, 0x82, 0x7D, 0x00}, //  Q
  { 0xFF, 0x88, 0x8C, 0x8A, 0x71, 0x00}, //  R
  { 0x61, 0x91, 0x91, 0x91, 0x8E, 0x00}, //  S
  { 0x80, 0x80, 0xFF, 0x80, 0x80, 0x00}, //  T
  { 0xFE, 0x01, 0x01, 0x01, 0xFE, 0x00}, //  U
  { 0xF0, 0x0C, 0x03, 0x0C, 0xF0, 0x00}, //  V
  { 0xFF, 0x02, 0x0C, 0x02, 0xFF, 0x00}, //  W
  { 0xC3, 0x24, 0x18, 0x24, 0xC3, 0x00}, //  X
  { 0xE0, 0x10, 0x0F, 0x10, 0xE0, 0x00}, //  Y
  { 0x83, 0x85, 0x99, 0xA1, 0xC1, 0x00}, //  Z
  { 0x06, 0x29, 0x29, 0x29, 0x1F, 0x00}, //  a
  { 0xFF, 0x09, 0x11, 0x11, 0x0E, 0x00}, //  b
  { 0x1E, 0x21, 0x21, 0x21, 0x12, 0x00}, //  c
  { 0x0E, 0x11, 0x11, 0x09, 0xFF, 0x00}, //  d
  { 0x0E, 0x15, 0x15, 0x15, 0x0C, 0x00}, //  e
  { 0x08, 0x7F, 0x88, 0x80, 0x40, 0x00}, //  f
  { 0x30, 0x49, 0x49, 0x49, 0x7E, 0x00}, //  g
  { 0xFF, 0x08, 0x10, 0x10, 0x0F, 0x00}, //  h
  { 0x00, 0x00, 0x5F, 0x00, 0x00, 0x00}, //  i
  { 0x02, 0x01, 0x21, 0xBE, 0x00, 0x00}, //  j
  { 0xFF, 0x04, 0x0A, 0x11, 0x00, 0x00}, //  k
  { 0x00, 0x81, 0xFF, 0x01, 0x00, 0x00}, //  l
  { 0x3F, 0x20, 0x18, 0x20, 0x1F, 0x00}, //  m
  { 0x3F, 0x10, 0x20, 0x20, 0x1F, 0x00}, //  n
  { 0x0E, 0x11, 0x11, 0x11, 0x0E, 0x00}, //  o
  { 0x3F, 0x24, 0x24, 0x24, 0x18, 0x00}, //  p
  { 0x10, 0x28, 0x28, 0x18, 0x3F, 0x00}, //  q
  { 0x1F, 0x08, 0x10, 0x10, 0x08, 0x00}, //  r
  { 0x09, 0x15, 0x15, 0x15, 0x02, 0x00}, //  s
  { 0x20, 0xFE, 0x21, 0x01, 0x02, 0x00}, //  t
  { 0x1E, 0x01, 0x01, 0x02, 0x1F, 0x00}, //  u
  { 0x1C, 0x02, 0x01, 0x02, 0x1C, 0x00}, //  v
  { 0x1E, 0x01, 0x0E, 0x01, 0x1E, 0x00}, //  w
  { 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x00}, //  x
  { 0x00, 0x39, 0x05, 0x05, 0x3E, 0x00}, //  y
  { 0x11, 0x13, 0x15, 0x19, 0x11, 0x00}, //  z
  { 0x00, 0x41, 0xFF, 0x01, 0x00, 0x00}, //  1
  { 0x43, 0x85, 0x89, 0x91, 0x61, 0x00}, //  2
  { 0x42, 0x81, 0x91, 0x91, 0x6E, 0x00}, //  3
  { 0x18, 0x28, 0x48, 0xFF, 0x08, 0x00}, //  4
  { 0xF2, 0x91, 0x91, 0x91, 0x8E, 0x00}, //  5
  { 0x1E, 0x29, 0x49, 0x89, 0x86, 0x00}, //  6
  { 0x80, 0x8F, 0x90, 0xA0, 0xC0, 0x00}, //  7
  { 0x6E, 0x91, 0x91, 0x91, 0x6E, 0x00}, //  8
  { 0x70, 0x89, 0x89, 0x8A, 0x7C, 0x00}, //  9
  { 0x7E, 0x89, 0x91, 0xA1, 0x7E, 0x00}, //  0
  { 0x60, 0x80, 0x8D, 0x90, 0x60, 0x00}, //  ?
  { 0x00, 0x00, 0xFD, 0x00, 0x00, 0x00}, //  !
  { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00} // SPACE
};




  
  public:

  uint8_t LED_OUT =LED_BUILTIN;
  uint8_t DATA=13;
  uint8_t LATCH=15;
  uint8_t CLOCK=14;
  uint8_t outputEnablePin=12;
  unsigned long currentMillis = millis();
  unsigned long previousMillis=0;
  unsigned long previousMillis2=0;
  unsigned long interval=1;
  unsigned long interval2=1050;  
  int ledState;
  int shiftSpeed=88;
  int scrollOffset=0;

  byte packetBuffer[25];
  byte colsVal[8] = {0};  
  byte brightnessBits;



};

#endif  // 
