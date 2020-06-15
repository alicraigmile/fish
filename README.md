# fish
Fish swimming across a 0.96" monochrome OLED display

## Hardware

* 0.96 inch white SPI OLED Display module
* Ardiuno Pro Mini 5V 16MHz
* 1 x 18650 LiPo Cell
* Micro USB Charger board
* Momentary switch Push button
* 10K resistor

### Block diagram

![](https://github.com/alicraigmile/fish/raw/master/fish.svg "Block diagram of the required hardware")

### Connections

1. Display module is driven by software SPI using 5 digital pins on the Arduino. I've used pins 7, 8, 10, 11 and 12. Use any 5 pins you have free and update the code accordingly.
2. Display module needs to be connected to Vcc and 0V.
3. The momentary switch connects between Vcc and pin 3 (interrupt 2 on this Arduino version). Use the 10k resistor to pull-down pin 3 to 0V. (Use a different pin if you like - just update the code to match.)
4. Vcc is supplied to the Arduino from the LiPo cell via the charger board.
5. Finally, the 18650 LiPo cell can be connected to the charger board (recommend using a suitable JST style connector if you have one).

## Software

Download the following code and upload it to the Arduino:

https://raw.githubusercontent.com/alicraigmile/fish/master/fish.ino

### How exactly?

See https://www.arduino.cc/en/Guide/ArduinoProMini#:~:text=Upload

### Dependancies

Adafruit_GFX and Adafruit_SSD1306 libraries are required to get this working.

## Usage

Connect the battery and you should see an animation appear on the screen. After 10s, you should see the fish.

You can also push the button, if you like.

## Acknowledgements

This code is heavily influenced by the Adafruit_SSD1306 sample code. Why not do Adafruit a favour and purchase all of the components for this project from them. 




