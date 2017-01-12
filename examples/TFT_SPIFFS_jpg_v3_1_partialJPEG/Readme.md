#TFT_SPIFFS_jpg_v3_1_partialJPEG

ESP8266 example that will actualy use internal SPI flash. 4MB SPI flash version of the ESP8266, like ESP-12x, is recommended.

+ In the User_Config.h:
      
      #define USE_SD_CARD
      
      //#define USE_SPIFFS
      
  These lines must change to:
      
      #define USE_SPIFFS
      
      //#define USE_SD_CARD
      
+ Get the [ILI9341](https://github.com/fredericplante/Adafruit_ILI9341) libraries.

+ To get the most benefits set your CPU to 160mhz, so you will cut down the decode time by about half. 

+ Check [/data](https://github.com/fredericplante/JPEGDecoder/edit/master/examples/TFT_SPIFFS_jpg_v3_1_partialJPEG/data/) to see the new file that needs to be uploaded to SPIFFS before or after uploading example.

<img src="https://github.com/fredericplante/JPEGDecoder/blob/master/Site_picture/construction.jpg" width="50%"/>

[EOF]
