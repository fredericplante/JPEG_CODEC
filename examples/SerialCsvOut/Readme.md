#Info for ESP8266 users.

1. It is currently set to send the uncompresse picture on Serial(), could be sent using Serial2().

2. It is currently set to send the uncompressed picture at a pace of 921600bps, so make sure you have a proper USB2Serial or you will have data lost.

3. You can lower the pace at line# 34.

4. At later version, I will impliment SPIFFS in this example.


#Info for Mega256 Due users.

1. Nothing has changed, same old good libraries. :D
