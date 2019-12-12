#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
// SCL GPIO5
// SDA GPIO4
#define OLED_RESET 0  // GPIO0
Adafruit_SSD1306 display(OLED_RESET);
 int i=0;
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2



// 'logooo', 9x12px
const unsigned char myBitmap [] PROGMEM = {
  0x08, 0x00, 0x1c, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x36, 0x00, 0x3e, 0x00, 0x3e, 0x00, 0x3e, 0x00, 
  0x7f, 0x00, 0xff, 0x80, 0x88, 0x80, 0x00, 0x00
};

 
 
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16
//////////////////////////////
 const int MPU_addr=0x68;  // I2C address of the MPU-6050
int16_t AcX,AcY,AcZ,Tmp,GyX,GyY,GyZ;
int minVal=265;
int maxVal=402;

double x;
double y;
double z;
 int displacement=0;
///////////////////////////////////
 
void setup()   {

  
 Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
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
  display.println("Hello, world!");
  display.display();
  delay(2000);
  display.clearDisplay();
  display.setTextSize(1);
}
 
 
void loop() {
Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,14,true);
  AcX=Wire.read()<<8|Wire.read();
  AcY=Wire.read()<<8|Wire.read();
  AcZ=Wire.read()<<8|Wire.read();
    int xAng = map(AcX,minVal,maxVal,-90,90);
    int yAng = map(AcY,minVal,maxVal,-90,90);
    int zAng = map(AcZ,minVal,maxVal,-90,90);

       x= RAD_TO_DEG * (atan2(-yAng, -zAng)+PI);
       y= RAD_TO_DEG * (atan2(-xAng, -zAng)+PI);
       z= RAD_TO_DEG * (atan2(-yAng, -xAng)+PI);





  if((z<100)&& (displacement>-60)&&(z>50))
  displacement=displacement-5;
  if((z>300)&& (displacement<60)&&(z<350))
  displacement=displacement+5;
  Serial.println(displacement);
  int j = 58+displacement;
 
  display.drawBitmap(j, 20, myBitmap, 9, 12, WHITE);
   
    
  display.display();
   
  display.clearDisplay();
 
 
}
