/*
/*
  Descendant of TFT_SDcard_jpg_v1.ino
  Sample code of JPEG Decoder for Arduino
  Public domain, Makoto Kurauchi <http://yushakobo.jp>
*/
/*
// Adapted to display images on a 320x240 on ILI9341
// This sketch renders JPEG images stored on In the SPIFF of the ESP866
//Originaly from: https://github.com/Bodmer/JPEGDecoder
*/
/*IMPORTANT INSTRUCTIONS
 * 

1. You must Upload the data folder to the SPIFFS of the ESP8266. 

2. In the User_Config.h You must change from:

#define USE_SD_CARD
//#define USE_SPIFFS

to: 

//#define USE_SD_CARD
#define USE_SPIFFS

3. don't forget to get the Adafruit_ILI9341 libraries from:

https://github.com/fredericplante/Adafruit_ILI9341

To get the most benefits set your CPU to 160mhz, so you will cut down the decode time by about half

4. Enjoy!
----------------------------------------------------------------------------------------------------*/

#include <JPEGDecoder.h>

#ifdef ESP8266
   
  #include <arduino.h>
  #include <FS.h>
  #include <SPI.h>
  #include <Adafruit_ILI9341.h>
  
  #define TFT_DC 4
  #define TFT_CS 5
  #define TFT_BLACK   0x0000
  #define TFT_BLUE    0x001F
  #define TFT_RED     0xF800
  #define TFT_GREEN   0x07E0
  #define TFT_CYAN    0x07FF
  #define TFT_MAGENTA 0xF81F
  #define TFT_YELLOW  0xFFE0  
  #define TFT_WHITE   0xFFFF

  Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
  uint32_t icount = 0;

  void setup() {
 
    Serial.begin(921600);
    tft.begin();
    tft.setRotation(1);  // landscape
    tft.fillScreen(TFT_BLACK);
    if (!SPIFFS.begin()) { Serial.println("initialisation failed!"); return;}
    Serial.println("\r\nInitialisation done.");
  
  }

  void loop() {

    tft.setRotation(1);
    tft.fillScreen(0x0);
    drawJpeg("/Splash.jpg", 1, 1);
    delay(2000);
    tft.setRotation(1);
    tft.fillScreen(random(0x0));
    drawJpeg("/Player.JPG", 1, 1);
    delay(2000);
    createArray("/Splash.jpg");

  }

  void drawJpeg(char *filename, int xpos, int ypos) {
  
    Serial.println(filename);
    JpegDec.decodeFile(filename);
    renderJPEG(xpos, ypos);
  
  }

  void renderJPEG(int xpos, int ypos) {

    jpegInfo(); 
    uint16_t  *pImg;
    uint16_t mcu_w = JpegDec.MCUWidth;
    uint16_t mcu_h = JpegDec.MCUHeight;
    uint32_t mcu_pixels = mcu_w * mcu_h;
    uint32_t drawTime = millis();

    while( JpegDec.read()){
    
      pImg = JpegDec.pImage;
      int mcu_x = JpegDec.MCUx * mcu_w + xpos;
      int mcu_y = JpegDec.MCUy * mcu_h + ypos;
      
      if ( (( mcu_x + mcu_w) <= tft.width()) && (( mcu_y + mcu_h) <= tft.height())){
      
        tft.setWindow(mcu_x, mcu_y, mcu_x + mcu_w - 1, mcu_y + mcu_h - 1);
        uint32_t count = mcu_pixels;
        while (count--) {tft.pushColor(*pImg++);}
        //tft.pushColor16(pImg, mcu_pixels); //  To be done

      }

      else if( ( mcu_y + mcu_h) >= tft.height()) JpegDec.abort();
  
    }

    showTime(millis() - drawTime);
    //Serial.print(" Draw count:"); Serial.println(icount++);

  }

  void jpegInfo() {

    Serial.println("JPEG image info");
    Serial.println("===============");
    Serial.print("Width      :"); Serial.println(JpegDec.width);
    Serial.print("Height     :"); Serial.println(JpegDec.height);
    Serial.print("Components :"); Serial.println(JpegDec.comps);
    Serial.print("MCU / row  :"); Serial.println(JpegDec.MCUSPerRow);
    Serial.print("MCU / col  :"); Serial.println(JpegDec.MCUSPerCol);
    Serial.print("Scan type  :"); Serial.println(JpegDec.scanType);
    Serial.print("MCU width  :"); Serial.println(JpegDec.MCUWidth);
    Serial.print("MCU height :"); Serial.println(JpegDec.MCUHeight);
    Serial.println("===============");
    Serial.println("");
  }

  void showTime(uint32_t msTime) {

    //tft.setCursor(0, 0);
    //tft.setTextFont(1);
    //tft.setTextSize(2);
    //tft.setTextColor(TFT_WHITE, TFT_BLACK);
    //tft.print(F(" JPEG drawn in "));
    //tft.print(msTime);
    //tft.println(F(" ms "));
    Serial.print(F(" JPEG drawn in "));
    Serial.print(msTime);
    Serial.println(F(" ms "));

  }

  void createArray(const char *filename) {
  
    File jpgFile;
  // uint8_t  SPIFFSbuffer[256];   // SPIFFS read pixel buffer (16 bits per pixel)
    if ( ( jpgFile = SPIFFS.open( filename, "r")) == NULL){ Serial.println(F("JPEG file not found")); return;}
  
    uint8_t data;
    byte line_len = 0;

    Serial.print("const uint8_t ");
    while (*filename != '.') Serial.print(*filename++);
    Serial.println("[] PROGMEM = {"); // PROGMEM added for AVR processors, it is ignored by Due
  
    while ( jpgFile.available()){

      data = jpgFile.read();
      Serial.print("0x"); if (abs(data) < 16) Serial.print("0");
      Serial.print(data, HEX); Serial.print(",");// Add value and comma
      line_len++;
      if ( line_len >= 32){ line_len = 0; Serial.println();}
    
    }
  
    Serial.println("};\r\n");
    jpgFile.close();
  
  }

#else

  void setup() {

    Serial.begin(115200);
    Serial.println("\r\nThis sketch exemple need to run on SPIFFS based system, like ESP8266.");
 
  }

  void loop() {;}

#endif 

