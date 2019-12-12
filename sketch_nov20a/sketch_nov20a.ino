#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);

// 'logooo', 9x12px
const unsigned char myBitmap [] PROGMEM = {
  0x08, 0x00, 0x1c, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x36, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x3e, 0x00, 
  0x7f, 0x00, 0xff, 0x80, 0x88, 0x80, 0x00, 0x00
};

void setup(){
  display.begin(SSD1306_SWITCHCAPVCC, 0x3c); //or 0x3C
  display.clearDisplay(); //for Clearing the display
  display.drawBitmap(15, 15, myBitmap, 9, 12, WHITE); // display.drawBitmap(x position, y position, bitmap data, bitmap width, bitmap height, color)
  display.display();
}

void loop() { }
