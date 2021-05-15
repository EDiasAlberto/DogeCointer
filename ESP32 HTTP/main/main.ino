//Includes all necessary libraries
#include <WiFi.h>
#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <LiquidCrystal_I2C.h>


//Data used to setup the Display
const int lcdColumns = 16; //Num of columns on the LCD display.
const int lcdRows = 2; //Num of rows on the LCD display
const int SDAPin = 25; //GPIO pin on the ESP32 that the I2C's SDA pin is connected to 
const int SCLPin = 33; //GPIO pin on the ESP32 that the I2C's SCL pin is connected to
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows); //Creates the object that represents the LCD display.

//Sets up necessary network and API credentials.
const char* ssid = "";
const char* pass = "";
const String binanceAPI = "https://api.binance.com/api/v3/ticker/price?symbol=DOGEGBP";


void setup() {
  

  //This turns on the LCD and sets the cursor to 0,0 with a blank screen.
  lcd.begin(SDAPin, SCLPin); //SDA, SCL
  lcd.backlight();
  lcd.home();
  
  //Starts Serial connection and connects to LAN.
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println(WiFi.localIP());



}

//Function used to fetch and process the dogecoin price, returning a string of the price.
String fetchDoge(){
  HTTPClient http;
  http.begin(binanceAPI.c_str());
  
  int responseCode = http.GET();
  Serial.println("HTTP: " + String(responseCode));
  
  String rawBinanceData = http.getString();
  JSONVar JSONDataParsed = JSON.parse(rawBinanceData);
  String dogePrice = JSON.stringify(JSONDataParsed["price"]);
  
  dogePrice.remove(0,1);
  dogePrice.remove(10,1);

  Serial.println(dogePrice);

  return dogePrice;
}

void loop() {

  //Requests and outputs the Dogecoin price every 1 second.
  String price = fetchDoge();
  lcd.home();
  lcd.print("DOGE/GBP");
  lcd.setCursor(0,1);
  lcd.print(price);
  delay(1000);
  
}
