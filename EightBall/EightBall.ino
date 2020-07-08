/**************************************************************************
  This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

  This example is for a 128x32 pixel display using I2C to communicate
  3 pins are required to interface (two I2C and one reset).

  Adafruit invests time and resources providing this open
  source code, please support Adafruit and open-source
  hardware by purchasing products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries,
  with contributions from the open source community.
  BSD license, check license.txt for more information
  All text above, and the splash screen below must be
  included in any redistribution.
 **************************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
// Library for Neopixel effects
#include <Adafruit_NeoPixel.h>
#include "Bitmaps.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
//#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin) - use w/ Trinket and SSD1306
#define OLED_RESET     16 // For built in OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define NUMFLAKES     10 // Number of snowflakes in the animation example

const int buttonPin = 0;  // D3 on WiFiKit8 built in OLED
int buttonState = 0;  // variable to store state of pin 4
int lastpick = 1;
int pick = random(1, 10);

const int LED_PIN = 2; //WifiKit8 SDA Pin
#define LED_COUNT 1
/* Create neopixel strip object *******************/
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  //pinMode(buttonPin, INPUT);  // set pin for tilst switch input
  pinMode(buttonPin, INPUT_PULLUP);  //set pin for tilt switch input - added pullup for 8266 WiFiKit8 w/ OLED

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3C for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.setRotation(2);  //0 is normal, 1 is 90, 2 is 180 and 3 is 270deg
  display.display();
  delay(500); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();
  display.setTextSize(2);             // Normal 1:1 pixel scale
  display.setTextColor(WHITE);        // Draw white text
  display.setCursor(0, 0);            // Start position
  display.println(F("Ask me"));
  display.println(F("Something"));
  //display.display();

  display.drawBitmap(
    (display.width()  - 26 ) / 2 + 35,
    (display.height() - 26) / 2 - 8,
    lips, 24, 24, 1);
  display.display();
  delay(1000);

  // Clear the buffer
  display.clearDisplay();

  // Setup Neopixel LED
  //pinMode(LED_PIN, OUTPUT);
  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(20); // Set BRIGHTNESS to about 1/5 (max = 255)
  theaterChaseRainbow(50); // Rainbow-enhanced theaterChase variant
  strip.clear();
  strip.show();

  //randomSeed(random(1,500));
  randomSeed(analogRead(1));
  Serial.println("setup complete");

}

void loop() {


  // if button is pressed, randomly pick a new response, trigger the neopixel light effect then display the random answer

  buttonState = digitalRead(buttonPin);

  if (buttonState == 0) {   // Press button for new random pick
    
    // neopixel light show to indicate thinking
    strip.setBrightness(20); // Set BRIGHTNESS to about 1/5 (max = 255)
    rainbow(10);
    strip.clear();
    strip.show();
    // draw starflakes to indicate the answer is near
    testdrawbitmap();
    testanimate(logo_bmp, LOGO_WIDTH, LOGO_HEIGHT); // Animate bitmaps

    int pick = random(1, 10);

    if (pick == lastpick) {
      //Serial.println(F("Repeat Fixed"));
      pick = random(1, 10);
    }

    Serial.println(pick);
    delay(100);
    lastpick = pick;
    
    switch (pick) {
      case 1:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(0, 0);            // Start position
        display.println(F("Outlook"));
        display.println(F(" Good!"));
        display.drawBitmap(
          ((display.width()  - 26 ) / 2) + 35,
          (display.height() - 26) / 2,
          heart, 26, 26, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 2:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(0, 0);            // Start Position
        display.println(F("Most "));
        display.println(F("Likely..."));
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 3:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(5, 0);            // Start Position
        display.println(F("  Very "));
        display.println(F(" Doubtful"));
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 4:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(5, 0);            // Start Position
        display.println(F("Hazy"));
        display.println(F("try again"));
        display.drawBitmap(
          ((display.width()  - 24 ) / 2) + 35,
          ((display.height() - 24) / 2) - 10,
          lips, 24, 24, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 5:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(0, 0);            // Start Position
        display.println(F("It is"));
        display.println(F("Certain"));
        display.drawBitmap(
          ((display.width()  - 32 ) / 2) + 35,
          ((display.height() - 32) / 2) - 3,
          olyve, 32, 32, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 6:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(5, 0);            // Start Position
        display.println(F("Outlook"));
        display.println(F("  Poor"));
        display.drawBitmap(((display.width()  - LOGO_WIDTH ) / 2) + 48, ((display.height() - LOGO_HEIGHT) / 2) - 0,
                           logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 7:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(5, 0);            // Start Position
        display.println(F("Better"));
        display.println(F("not say"));
        display.drawBitmap(
          ((display.width()  - 30 ) / 2) + 35,
          ((display.height() - 30) / 2) - 3,
          Winter, 30, 30, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 8:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(5, 0);            // Start Position
        display.println(F("  No"));
        display.println(F(" doubt!"));
        display.drawBitmap(
          ((display.width()  - 30 ) / 2) + 35,
          ((display.height() - 30) / 2) - 3,
          Spring, 30, 30, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;
      case 9:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(5, 0);            // Start Position
        display.println(F(" For"));
        display.println(F(" sure!"));
        display.drawBitmap(
          ((display.width()  - 30 ) / 2) + 35,
          ((display.height() - 30) / 2) - 3,
          Flame, 30, 30, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;    
      case 10:
        display.clearDisplay();
        display.setTextSize(2);             // Normal 1:1 pixel scale
        display.setTextColor(WHITE);        // Draw white text
        display.setCursor(5, 0);            // Start Position
        display.println(F(" No"));
        display.println(F(" never!"));
        display.drawBitmap(
          ((display.width()  - 32 ) / 2) + 35,
          ((display.height() - 32) / 2) - 3,
          Spring32, 32, 32, 1);
        display.display();
        delay(1000);
        // Scroll in various directions, pausing in-between:
        display.startscrollright(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrollleft(0x00, 0x0F);
        delay(2000);
        display.stopscroll();
        delay(1000);
        display.startscrolldiagright(0x00, 0x07);
        delay(2000);
        display.startscrolldiagleft(0x00, 0x07);
        delay(2000);
        display.stopscroll();
        delay(1000);
        break;              
      default:
        // if nothing else matches, do the default
        // default is optional
        //randomSeed(random(1,500));
        break;
    }
  }
  delay(2000);
}

// ************************************** Adafruit Logo Draw ***************************************************

void testdrawbitmap(void) {
  display.clearDisplay();

  display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}


// *************************************** Adafruit Snoflake Animation *******************************************

#define XPOS   0 // Indexes into the 'icons' array in function below
#define YPOS   1
#define DELTAY 2

void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
  int8_t f, icons[NUMFLAKES][3];

  // Initialize 'snowflake' positions
  for (f = 0; f < NUMFLAKES; f++) {
    icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
    icons[f][YPOS]   = -LOGO_HEIGHT;
    icons[f][DELTAY] = random(1, 6);
    /*Serial.print(F("x: "));
      Serial.print(icons[f][XPOS], DEC);
      Serial.print(F(" y: "));
      Serial.print(icons[f][YPOS], DEC);
      Serial.print(F(" dy: "));
      Serial.println(icons[f][DELTAY], DEC);*/
  }

  for (int i = 0; i <= 10; i++) { // Loop
    display.clearDisplay(); // Clear the display buffer

    // Draw each snowflake:
    for (f = 0; f < NUMFLAKES; f++) {
      display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, WHITE);
    }

    display.display(); // Show the display buffer on the screen
    delay(200);        // Pause for 1/10 second

    // Then update coordinates of each flake...
    for (f = 0; f < NUMFLAKES; f++) {
      icons[f][YPOS] += icons[f][DELTAY];
      // If snowflake is off the bottom of the screen...
      if (icons[f][YPOS] >= display.height()) {
        // Reinitialize to a random position, just off the top
        icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
        icons[f][YPOS]   = -LOGO_HEIGHT;
        icons[f][DELTAY] = random(1, 6);
      }
    }
  }
}
