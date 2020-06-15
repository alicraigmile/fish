/**************************************************************************
 Fish swimming across a 0.96" monochrome OLED display
 https://github.com/alicraigmile/fish

 Written by Ali Craigmile with contributions from the open source community.
 BSD license.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for SSD1306 display connected using software SPI (default case):
#define OLED_MOSI  11   //D1
#define OLED_CLK   12   //D0
#define OLED_DC    7
#define OLE 
#define OLED_RESET 10
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


#define NUMFISH       8  // Number of fish swimming in the 'sea'

#define LOGO_HEIGHT   16
#define LOGO_WIDTH    16
#define LOGO_PADDING  3  // Space between letters in BBC

#define SCREENSAVER_TIMEOUT 10000 // 10s
  
static const unsigned char PROGMEM goldfish_bmp[] =
{ B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B01111111, B11100000,
  B10000001, B00110000,
  B10000010, B10010111,
  B11111101, B00010101,
  B01111100, B00011101,
  B00000110, B00011001,
  B00011010, B01101001,
  B01111110, B10101111,
  B01100111, B00101000,
  B00100000, B11110000,
  B00111111, B11111000,
  B00000000, B00000000,
  B00000000, B00000000 };

static const unsigned char PROGMEM b_bmp[] = {
  0xff, 0xff, 
  0xff, 0xff, 
  0xf0, 0x3f, 
  0xf0, 0x1f, 
  0xf3, 0x8f, 
  0xf3, 0x8f, 
  0xf0, 0x1f, 
  0xf0, 0x1f, 
  0xf0, 0x0f, 
  0xf3, 0xc7, 
  0xf3, 0xc7, 
  0xf0, 0x0f, 
  0xf0, 0x1f, 
  0xff, 0xff, 
  0xff, 0xff, 
  0x00, 0x00
};

static const unsigned char PROGMEM c_bmp[] = {
  0x00, 0x00, 
  0x7f, 0xff, 
  0x7c, 0x0f, 
  0x70, 0x07, 
  0x61, 0xc7, 
  0x63, 0xff, 
  0x47, 0xff, 
  0x47, 0xff, 
  0x47, 0xff, 
  0x67, 0xff, 
  0x63, 0xf7, 
  0x70, 0x07, 
  0x78, 0x07, 
  0x7f, 0x7f, 
  0x7f, 0xff, 
  0x00, 0x00
};


volatile boolean buttonPress = false;
long previousMillis = 0;        // will store last time LED was updated

void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

 // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  // a button on digitalPin 2 will wake the device if it's in screensaver is running 

  // (NB:  on anrduino uno pin2 = interrupt 0)
  pinMode(3, INPUT);
  attachInterrupt(1, buttonPressed, RISING);
  
  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen unless we call clearDisplay() before display().
  display.clearDisplay();
  display.display();
 
  powerupanimation();
}

void buttonPressed() {
 buttonPress = true;
}

void loop() {
  drawbbcbitesize();
  delay(SCREENSAVER_TIMEOUT);
  screensaver(goldfish_bmp, LOGO_WIDTH, LOGO_HEIGHT, NUMFISH);
}

void drawbbcbitesize(void) {
  Serial.println("BBC Bitesize...:");
  display.clearDisplay();

  display.drawRect(0, 0, display.width(), display.height(), SSD1306_WHITE);

  int16_t x,y;
  x = (display.width() - (3 * LOGO_WIDTH) + (2 * LOGO_PADDING)) / 2;
  x -= 4;
  y = 10;
  
  display.drawBitmap(x, y, b_bmp, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);
  x += LOGO_WIDTH+LOGO_PADDING;
  display.drawBitmap(x, y, b_bmp, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);
  x += LOGO_WIDTH+LOGO_PADDING;
  display.drawBitmap(x, y, c_bmp, LOGO_WIDTH, LOGO_HEIGHT, SSD1306_WHITE);

  y+= LOGO_HEIGHT+4;
  display.setTextSize(1); // Draw 1x-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(43, y);
  display.println(F("Bitesize"));
   y+= LOGO_HEIGHT+4;
  display.setCursor(12, y);
  display.println(F("bbc.co.uk/bitesize"));
  display.display();
}

void powerupanimation(void) {
  Serial.println("Power up...:");
  display.clearDisplay();

  for(int16_t i=display.height()/2; i>0; i-=2) {
    display.clearDisplay();
    display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
    display.display(); // Update screen with each newly-drawn rectangle
    delay(50);
  }

}


#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAX 2
#define DELTAY 3

void screensaver(const uint8_t *bitmap, uint8_t w, uint8_t h, uint8_t numfish) {
  int8_t f, icons[numfish][4];
  Serial.println("Screensaver...:");

  // Initialize 'fish' positions
  for(f=0; f< numfish; f++) {
    icons[f][XPOS]   = display.width();
    icons[f][YPOS]   = random(1 - h, display.height());
    icons[f][DELTAX] = random(2, 6);
    icons[f][DELTAY] = random(-1, 1);
    Serial.print("init f:");
    Serial.print(f, DEC);
    Serial.print(F(" x: "));
    Serial.print(icons[f][XPOS], DEC);
    Serial.print(F(" y: "));
    Serial.print(icons[f][YPOS], DEC);
    Serial.print(F(" dx: "));
    Serial.println(icons[f][DELTAX], DEC);
    Serial.print(F(" dy: "));
    Serial.println(icons[f][DELTAY], DEC);
  }

  for(;;) { // Loop forever...

    if (buttonPress) {
      buttonPress = false;
      break;
    }
    display.clearDisplay(); // Clear the display buffer

    // Draw each fish:
    for(f=0; f< numfish; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(100);        // Pause for 1/10 second

    // Then update coordinates of each fish...
    for(f=0; f< numfish; f++) {
      icons[f][XPOS] -= icons[f][DELTAX];
     // icons[f][YPOS] -= icons[f][DELTAY];
      // If fish is off the left of the screen...
      if (icons[f][XPOS] <= 0-w) {
        // Reinitialize to a random position, just off the right
        icons[f][XPOS]   = display.width();
        icons[f][YPOS]   = random(1 - h, display.height());
        icons[f][DELTAX] = random(2, 6);
        icons[f][DELTAY] = random(-1, 1);
      }
    }
  }
}
