# 💡LEDMatrix Library

## Introduction
This library provides functions to control an LED matrix using an ESP8266 microcontroller. It allows for horizontal and vertical scrolling of text, as well as basic LED manipulation.It also comes with a python program to sent it basic patterns over wifi via udp port.

## 🚀Installation
    To use this library, download it from the release page 
or
```
    git clone https://github.com/circuito-suman/74HC595ledmatrixlibrary
    cd 74HC595ledmatrixlibrary
```

## 🛠Usage

### Initialization
```

#include "LEDMatrix.h"
LEDMatrix ledMatrix;
const char* ssid = "real"; // your wifi ssid
const char* password = "suman saha"; // your wifi password

void setup() {
  ledMatrix.begin(ssid, password);
}
```

## Basic Functions

    void test(): Displays a test pattern on the LED matrix.
    void drawLedHorizontal(): Draws LEDs horizontally.
    void drawLedVertical(): Draws LEDs vertically.
    void update(): Updates the LED matrix.

## Text Scrolling



```
void loadString(const char *text);
void scrollLeftToRight(int n);
void scrollRightToLeft(int n);
void scrollUpToDown(int n);
void scrollDownToUp(int n);
```

## Advanced Functions
```
    void shiftLeft(int delayTime): Shifts LEDs to the left.
    void shiftRight(int delayTime): Shifts LEDs to the right.
    void brightnesscontrol(int br): Controls the brightness of the LEDs.
    void shutdown(bool status): Shuts down or restores the LED matrix.

```

### Demo  Example

```

#include "LEDMatrix.h"
LEDMatrix ledMatrix;
const char* ssid = "real"; // your wifi ssid
const char* password = "suman saha"; // your wifi password
int scrollspeed=30;

void setup() {
  ledMatrix.begin(ssid, password);
  ledMatrix.loadString("initiated");
  ledMatrix.scrollLeftToRight(scrollspeed);
}


void loop() {
ledMatrix.loadString("Suman wants you to try this out");
ledMatrix.scrollDownToUp(scrollspeed);
ledMatrix.scrollLeftToRight(scrollspeed);
ledMatrix.scrollRightToLeft(scrollspeed);
ledMatrix.scrollUpToDown(scrollspeed);
}

```
## 🔌Dependencies

    OtaHelper (Optional): Provides over-the-air update functionality.
    ESP8266WebServer for web based text update




### Images
Include images here.
![8x8 matrix cross](examples/demo2.jpg)


### Schematic
Include schematic diagram here.
![8x8 matrix cross](examples/demo2.jpg)


## 🙏 Acknowledgements
Thank you for checking out this project! If you have any questions or suggestions, feel free to open an issue or reach out to me on social media. Happing learning 💻✨


## Authors

- [@circuito-suman](https://www.github.com/circuito-suman)


![Logo](https://avatars.githubusercontent.com/u/125496903?v=4)




## Contributing

Contributions are always welcome!




## License

This library is licensed under the MIT License.
