#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
File myFile; 
// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
 int i=0;
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
 
 
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
 
 
void setup()   {
  Serial.begin(9600);


  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 64x48)
  // init done
 
  display.display();
  delay(2000);
 
  // Clear the buffer.
  display.clearDisplay();
 
  // text display tests
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(20,10);
  display.println("Initializing SD card...");
  display.display();
  delay(2000);
  display.clearDisplay();
  
  display.setCursor(20,10);
  display.println("initialization done.");
  display.display();
  delay(1000);
  display.clearDisplay();

  
  display.setCursor(20,10);
  display.println("Writing to test.txt...");
  display.display();
  delay(1000);
  display.clearDisplay();

  
  display.setCursor(20,10);
  display.println("done.");
  display.display();
  delay(1000);
  display.clearDisplay();

  

   Serial.print("Initializing SD card...");

  if (!SD.begin(15)) {
    Serial.println("initialization failed!");
    return;
  }
  Serial.println("initialization done.");

  myFile = SD.open("test.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to test.txt...");
    myFile.println("testing 1, 2, 3.");
    // close the file:
    myFile.close();
    Serial.println("done.");
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }

  // re-open the file for reading:
  myFile = SD.open("test.txt");
  if (myFile) {
    Serial.println("test.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      
      
      display.setCursor(0,0);
      String listt = myFile.readStringUntil('\r');
   display.println(listt);
  display.display();
   
  display.clearDisplay();
  
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
}
 
 
void loop() {
  
  display.setCursor(0,0);
   display.println("dgdhgcghhdgh");
  display.display();
  
  display.clearDisplay();
 
}
