#include <WiFi.h>
#include <Arduino.h>
#include <WebSocketsClient.h>
#include <LiquidCrystal_I2C.h>

char* ssid = "TALKTALK48237E";
char* pass = "8Y4ETH64";

//Data used to setup the Display
const int lcdColumns = 16; //Num of columns on the LCD display.
const int lcdRows = 2; //Num of rows on the LCD display
const int SDAPin = 25; //GPIO pin on the ESP32 that the I2C's SDA pin is connected to 
const int SCLPin = 33; //GPIO pin on the ESP32 that the I2C's SCL pin is connected to
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); //Creates the object that represents the LCD display.

WebSocketsClient client;

void webSocketEvent (WStype_t eventType, uint8_t* payload, size_t dataLength){
  Serial.println(eventType);
  switch(eventType){
    case WStype_DISCONNECTED:
      Serial.printf("[WSc] Disconnected!\n");
      break;
    case WStype_CONNECTED:
      Serial.printf("[WSc] Connected to url: %s\n", payload);
      break;
    case WStype_TEXT:
      lcd.home();
      lcd.print("DOGE/GBP");
      lcd.setCursor(0,1);
      lcd.print((char*)payload);
      Serial.println((char*)payload);
      break;
    case WStype_ERROR:
      Serial.println((char*)payload);
      break;
    case WStype_BIN:
    case WStype_PING:
    case WStype_PONG:
    case WStype_FRAGMENT_TEXT_START:
    case WStype_FRAGMENT_BIN_START:
    case WStype_FRAGMENT:
    case WStype_FRAGMENT_FIN:
      break;
    default:
      Serial.println("Invalid data from Server");
      
    
  }
}

void setup(){
  Serial.begin(115200);
  
  WiFi.begin(ssid, pass);
  while(WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Connected to WiFi.");

 
  client.begin("192.168.1.56", 4200);
  Serial.println("Connection successful.");
  client.onEvent(webSocketEvent);

  //This turns on the LCD and sets the cursor to 0,0 with a blank screen.
  lcd.begin(SDAPin, SCLPin); //SDA, SCL
  lcd.backlight();
  lcd.home();
  
  
}

void loop(){
  String dogePrice;
  String passphrase = "Gib.";

  

  Serial.println("Sending passphrase...");

  client.sendTXT(passphrase);

  Serial.println("Gib.");
  
  

  for(int i=0;i<10;i++){
    delay(150);
    client.loop();
  }

  
  
}
