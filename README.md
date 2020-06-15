# Project fish

A (prototype) smart badge with some lovely fish swimming across it

## Hardware

* 0.96" monochrome OLED Display module SPI white
* Ardiuno Pro Mini 5V 16MHz
* 1 x 18650 Lipo Cell
* TP4056 Micro USB Lipo charger module
* Momentary switch / push button
* 10K resistor

### Block diagram

![](https://github.com/alicraigmile/fish/raw/master/fish.svg "Block diagram of the required hardware")

### Circuit diagram

![](https://github.com/alicraigmile/fish/raw/master/circuit.svg "Circuit diagram showing individual pin connections")

### Connections

1. Display module is driven by software SPI using 5 digital pins on the Arduino. I've used pins 7, 8, 10, 11 and 12. Use any 5 pins you have free and update the code accordingly.
2. Display module needs to be connected to Vcc and 0V.
3. The momentary switch connects between Vcc and pin 3 (interrupt 2 on this Arduino version). Use the 10k resistor to pull-down pin 3 to 0V. (Use a different pin if you like - just update the code to match.)
4. Vcc is supplied to the Arduino from the Lipo cell via the charger board.
5. Finally, the 18650 Lipo cell can be connected to the charger board (recommend using a suitable JST style connector if you have one).

## Software

Download the following code and upload it to the Arduino:

https://github.com/alicraigmile/fish/tree/master/src/fish

### How exactly?

See https://www.arduino.cc/en/Guide/ArduinoProMini#:~:text=Upload

### Dependancies

Adafruit_GFX and Adafruit_SSD1306 libraries are required to get this working.

## Usage

Pin the OLED display to your t-shirt, top, tie or lapel (delete as appropriate).

Upon connecting the battery, you should see an animation appear on the screen, and after 10s or so, you should see the fish swim in from the right of the display.

You can also push the button, if you'd like.

## Acknowledgements

This code is heavily influenced by the sample code that came with the Adafruit_SSD1306 library. Some or all of the compenents for this project can be purchased from [Adafruit](https://www.adafruit.com/) if you want to try making your own - although other retailers are available.

Project fish is dedicated to my colleagues past and present at [BBC Bitesize](https://www.bbc.co.uk/bitesize).




