#include "LEDMatrix.h"
#include "OtaHelper.h"
OtaHelper otaInstance;

LEDMatrix::LEDMatrix() : ROW_CNT(8), COL_CNT(8), PACKAGE_SIZE(18)
{
  // colsVal = new byte[ROW_CNT];
  instance = this; // Required for ISR access
}
LEDMatrix *LEDMatrix::instance = nullptr;

void LEDMatrix::begin(const char *ssid, const char *password, int udpPort, int clientPort)
{

  this->isInAPMode = true; // Start in AP mode
  this->UDPPort = udpPort;
  this->clientPort = clientPort;

  Serial.begin(115200);

  pinMode(buttonPin, INPUT_PULLUP);
  attachInterrupt((buttonPin), handleButtonInterrupt, FALLING);

  pinMode(LED_OUT, OUTPUT);
  pinMode(DATA, OUTPUT);
  pinMode(LATCH, OUTPUT);
  pinMode(CLOCK, OUTPUT);
  pinMode(outputEnablePin, OUTPUT);
  digitalWrite(outputEnablePin, HIGH);

#if MATRIX_REGISTERS_INIT_CLEAR
  clearDisplay();
#endif

  digitalWrite(LED_OUT, LOW);
  /*
    WiFi.begin(ssid, password);
    Serial.println("");

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    */
  // otaInstance.start(ssid, password, "hostName", "hostPassword", 3232, 115200);

  row_ = 0;
  buffer_ = new byte[MATRIX_SIZE];
  // UDPServer.begin(UDPPort); // now in switchToAPMode and switchToSTAMode

  digitalWrite(LED_OUT, HIGH);
  switchToAPMode(); // Initialize AP mode at boot

  test();
}

void IRAM_ATTR handleButtonInterrupt()
{
  if ((millis() - LEDMatrix::instance->lastInterruptTime) > LEDMatrix::instance->debounceTime)
  {
    LEDMatrix::instance->buttonPressed = true;
  }
}

void LEDMatrix::switchToSTAMode()
{
  Serial.println("Switching to STA mode...");

  WiFi.softAPdisconnect(true); // Turn off AP
  WiFi.disconnect();           // Disconnect from any existing Wi-Fi
  WiFi.mode(WIFI_STA);         // Set to station mode

  otaInstance.start("real", "suman saha", "hostName", "hostPassword", 3232, 115200);

  isInAPMode = false;
  UDPServer.begin(UDPPort); // Restart UDP with new IP
  loadString(WiFi.localIP().toString().c_str());
  scrollLeftToRight(8); // 8 is the optimal speed
  clearDisplay();
}

void LEDMatrix::switchToAPMode()
{
  Serial.println("Switching to AP mode...");

  WiFi.disconnect();               // Disconnect from Wi-Fi
  WiFi.mode(WIFI_AP);              // Set to AP mode
  WiFi.softAP(apSSID, apPassword); // Start the access point

  Serial.print("AP SSID: ");
  Serial.println(apSSID);
  Serial.print("AP IP address: ");
  Serial.println(WiFi.softAPIP());

  isInAPMode = true;
  UDPServer.begin(UDPPort); // Restart UDP with new IP
  loadString(WiFi.softAPIP().toString().c_str());
  scrollLeftToRight(8); // 8 is the optimal speed
  clearDisplay();
}

void LEDMatrix::toggleMode()
{
  if (isInAPMode)
  {
    // Reinitialize OTA in STA mode
    switchToSTAMode();
  }
  else
  {
    // Stop OTA before AP mode
    switchToAPMode();
  }
}

void LEDMatrix::but(){
 if (buttonPressed) // 8 is the optimal speed
  {
   buttonPressed = false; // Reset flag
    toggleMode();
    clearDisplay();
  }
}

void LEDMatrix::writeCell(int cols, int rows)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, (0x000000ff & rows));
  shiftOut(DATA, CLOCK, MSBFIRST, cols);
  digitalWrite(LATCH, HIGH);
}

void LEDMatrix::writeOutput(int rowVal, int col)
{
  digitalWrite(LATCH, LOW);
  shiftOut(DATA, CLOCK, MSBFIRST, rowVal);
  shiftOut(DATA, CLOCK, MSBFIRST, col);
  digitalWrite(LATCH, HIGH);
}

void LEDMatrix::brightnesscontrol(int br)
{
  brightnessBits = map(br, 0, 100, 1023, 0);
  // brightnessBits = constrain(brightnessBits, 0, 1023);
  analogWrite(outputEnablePin, brightnessBits);
}
void LEDMatrix::drawLedHorizontal()
{
  int rows = 0x00000001;
  for (int i = 0; i < PACKAGE_SIZE; i++)
  {
    writeCell(colsVal[i], rows);
    rows <<= 1;
    delayMicroseconds(5);
  }
}

void LEDMatrix::drawLedVertical()
{
  for (int i = 0; i < ROW_CNT; i++)
  {
    writeCell(colsVal[i], 1 << i);
    delayMicroseconds(150);
  }
}
/*
void LEDMatrix::processPostData() {
  int p = UDPServer.parsePacket();
  if (p) {
    UDPServer.read(packetBuffer, PACKAGE_SIZE);
   // Serial.println(colsVal[0]);
   for (int i = 0; i < PACKAGE_SIZE; i++)
    {
      colsVal[i] = packetBuffer[i];
             Serial.print(packetBuffer[i]);
      brightnesscontrol(packetBuffer[8]);
      //Serial.println((packetBuffer[8]));
       Serial.print(packetBuffer[i]);

    } Serial.println(" ");
  }
}
*/

void LEDMatrix::processPostData()
{
  int p = UDPServer.parsePacket();
  if (p)
  {
    UDPServer.read(packetBuffer, PACKAGE_SIZE);

    // Check if the packet starts with a prefix indicating a scroll direction
    if ((packetBuffer[0] == 'l' || packetBuffer[0] == 'r' || packetBuffer[0] == 'u' || packetBuffer[0] == 'd') && packetBuffer[1] == '/')
    {
      // Extract the rest of the packet as a string
      String receivedString = "";
      for (int i = 2; i < p; i++)
      {
        receivedString += (char)packetBuffer[i];
        Serial.print((char)packetBuffer[i]);
      }
      Serial.println(" ");

      // Call the loadstring function with the extracted string
      loadString(receivedString.c_str());

      // Call the appropriate text scrolling function based on the prefix
      switch (packetBuffer[0])
      {
      case 'l':
        scrollLeftToRight(30);
        break;
      case 'r':
        scrollRightToLeft(30);
        break;
      case 'u':
        scrollUpToDown(30);
        break;
      case 'd':
        scrollDownToUp(30);
        break;
      }
    }
    else
    {
      // Process the packet as usual if it doesn't start with a known prefix
      for (int i = 0; i < PACKAGE_SIZE; i++)
      {
        colsVal[i] = packetBuffer[i];
        Serial.print(packetBuffer[i]);
        brightnesscontrol(packetBuffer[8]);
        Serial.print(packetBuffer[i]);
      }
      Serial.println(" ");
    }
  }
  // drawLedHorizontal();
}

void LEDMatrix::update()
{

  if (currentMillis - previousMillis >= interval)
  {
    previousMillis = currentMillis;
    if (ledState == LOW)
      ledState = HIGH;
    else
      ledState = LOW;
    digitalWrite(LED_OUT, ledState);
    processPostData();
  }

  if (buttonPressed)
  {
    buttonPressed = false; // Reset flag
    toggleMode();
  }
}

void LEDMatrix::shiftRight(int delayTime)
{
  byte tmp = colsVal[0];
  for (int i = 0; i < PACKAGE_SIZE - 1; i++)
  {
    colsVal[i] = colsVal[i + 1];
  }
  colsVal[PACKAGE_SIZE - 1] = tmp;
  delay(delayTime);
}

void LEDMatrix::shiftLeft(int delayTime)
{
  byte tmp = colsVal[PACKAGE_SIZE - 1];
  for (int i = PACKAGE_SIZE - 1; i > 0; i--)
  {
    colsVal[i] = colsVal[i - 1];
  }
  colsVal[0] = tmp;
  delay(delayTime);
}

void LEDMatrix::test()
{
  writeCell(0xF9, 5);
}

void LEDMatrix::loadString(const char *text)
{
  _nrLetters = strlen(text);
  _textBytes = (byte *)malloc(_nrLetters * 6);

  for (int i = 0; i < _nrLetters; ++i)
  {
    int chPos = strchr(_letterPositions, text[i]) - _letterPositions;
    if (chPos < 0 || chPos >= sizeof(_letterPositions) - 1)
    {
      continue;
    }
    for (int j = 0; j < 6; ++j)
    {
      _textBytes[i * 6 + j] = _letters[chPos][j];
    }
  }
}

void LEDMatrix::scrollLeftToRight(int n)
{
  int end = _nrLetters * 6 + 0;
  for (int p = 0; p < end; p++)
  {
    displayScroll(p, n);
  }
}

void LEDMatrix::scrollRightToLeft(int n)
{
  int end = _nrLetters * 6 + 0;
  for (int p = end - 1; p >= 0; p--)
  {
    displayScroll(p, n);
  }
}

void LEDMatrix::scrollUpToDown(int n)
{
  int end = _nrLetters * 6 + 0;
  for (int p = 0; p < end; p++)
  {
    displayScrollVertical(p, n);
  }
}

void LEDMatrix::scrollDownToUp(int n)
{
  int end = _nrLetters * 6 + 0;
  for (int p = end - 1; p >= 0; p--)
  {
    displayScrollVertical(p, n);
  }
}

void LEDMatrix::displayScroll(int position, int n)
{
  for (int repeat = 0; repeat < n; repeat++)
  { // control scroll speed
    for (int col = 0; col < 8; col++)
    {
      int columnVal = (position + col < _nrLetters * 6) ? _textBytes[position + col] : 0;
      writeOutput(columnVal, _columnNumbers[col]);
      delay(1); // Adjust delay for smoother scrolling
    }
  }
}

void LEDMatrix::displayScrollVertical(int position, int n)
{
  for (int repeat = 0; repeat < n; repeat++)
  { // control scroll speed
    for (int col = 0; col < 8; col++)
    {
      int rowVal = 0;
      for (int row = 0; row < 8; row++)
      {
        rowVal |= ((position + row < _nrLetters * 6) ? ((_textBytes[position + row] >> (7 - col)) & 0x01) : 0) << row;
      }
      writeOutput(rowVal, _columnNumbers[col]);
      delay(1); // Adjust delay for smoother scrolling
    }
  }
}

void LEDMatrix::shutdown(bool status)
{
  // Implementation for shutdown
  if (status)
  {
    digitalWrite(LED_OUT, LOW); // Set to LOW to shutdown
    digitalWrite(outputEnablePin, 0);
  }
  else
  {
    digitalWrite(LED_OUT, HIGH); // Set to HIGH for normal operation
    digitalWrite(outputEnablePin, 1);
  }
}

void LEDMatrix::clearDisplay()
{
  // Implementation for clearDisplay
  for (int i = 0; i < ROW_CNT; i++)
  {
    writeCell(0x00, 1 << i); // Clear all rows
  }
}

byte *LEDMatrix::getBuffer() { return buffer_; }

void LEDMatrix::up()
{
  row_ = 1;
  for (int i = 0; i < MATRIX_SIZE; i++)
  {
    digitalWrite(LATCH, LOW);
    shiftOut(DATA, CLOCK, MSBFIRST, row_);
    shiftOut(DATA, CLOCK, MSBFIRST, buffer_[i]);
    digitalWrite(LATCH, HIGH);
    row_ <<= 1;
  }
}

void LEDMatrix::setLed(int addr, int row, int col, boolean state)
{

  if (state)
    // LED ON
    buffer_[row] |= (1 << col);
  else
    // LED OFF
    buffer_[row] &= ~(1 << col);
}

void LEDMatrix::setRow(int row, byte value)
{
  // Implementation for setRow
  writeCell(value, 1 << row);
}

void LEDMatrix::setColumn(int col, byte value)
{
  // Implementation for setColumn
  for (int i = 0; i < ROW_CNT; i++)
  {
    if (value & (1 << i))
    {
      setLed(0, i, col, true);
    }
    else
    {
      setLed(0, i, col, false);
    }
  }
}
