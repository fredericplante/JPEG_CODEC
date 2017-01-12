#TFT_SPIFFS_jpg_v3

ESP8266 example that will actualy use internal SPI flash. 4MB SPI flash version of the ESP8266, like ESP-12x, is recommended.
 

You must Upload the data folder to the SPIFFS of the ESP8266. 
In the User_Config.h You must change from:

### #define USE_SD_CARD
//#define USE_SPIFFS

to: 

//#define USE_SD_CARD
### #define USE_SPIFFS

Get the [ILI9341](https://github.com/fredericplante/Adafruit_ILI9341) libraries. 

To get the most benefits set your CPU to 160mhz, so you will cut down the decode time by about half, 466ms instead of 932ms.

Note, new pictures with 320x240 resulution are now On. Check  [/data](https://github.com/fredericplante/JPEGDecoder/edit/master/examples/TFT_SPIFFS_jpg_v3/data/) to see the new files that needs to be uploaded to SPIFFS before or after uploading example.

The Serial port is set to 921600bps, so make sure to set you reader device to proper pace. It send the data from the "createArray" fuction at blazing speed.
