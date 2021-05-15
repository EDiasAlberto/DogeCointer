# DogeCointer

## Requirements:
* NodeJS:
  * https
  * ws
* ESP32:
  * LiquidCrystalI2C
  * Arduino JSON
  * WebSocketsClient
  * HTTPClient

##Project description:
This is a simple pair of programs. The whole function is to print the price of dogecoin on a connected LCD.
It has two methods of doing this, either the websocket edition or the HTTPS edition. The former involves a websocket server
on a computer which queries Binance and processes the JSON, whilst the microprocessor just fetches the price from the server.
The HTTPS edition involves all the processing occurring on the microprocessor and it outputting the price, without the need
for a separate computer.

## Instructions:

#### For Websockets version:
1. Install the requirements mentioned above, for NodeJS
2. Install the required libraries for the ESP32
3. In "WebsocketVersion\ESP32Websocket\main\main.ino", set the ssid and pass on lines 6 and 7 to your own network credentials.
4. Set the server IP on line 9 to whatever IP address you have your own server hosted on.
5. Set the pins in lines 15 and 16 to the pins you have your own LCD connected to.
6. Run "node server.js" in "WebsocketVersion\computerWebSocket" to start the server.
7. Upload the sketch to the ESP32 and turn it on.
8. :D

#### For HTTPS version:
1. Install the required libraries for the ESP32
2. Set the pins in lines 10 and 11 to the pins you have your own LCD connected to.
3. set the ssid and pass on lines 14 and 15 to your own network credentials.
