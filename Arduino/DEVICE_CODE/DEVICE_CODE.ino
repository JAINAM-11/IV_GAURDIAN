// Display:
// 	GND : GND
// 	VCC : VIN
// 	SDA : D2
// 	SCL : D1

#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char* WIFINAME = "JAINAM";
const char* PASS = "12341234";

HTTPClient http;
WiFiServer server(80);
#define Clock 13  // HX711 SCK D7
#define Data 12   // HX711 DT D6    

HX711 scale;
LiquidCrystal_I2C lcd(0x27, 16, 4);

float MaxWeight = 0;
float CurrWeight = 0;
float Reading = 0;

void setup() {
  // Initializing LCD
  lcd.init();                    
  lcd.backlight();

  // Connecting to Wi-Fi
  WiFi.begin(WIFINAME, PASS);
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  lcd.clear();
  lcd.print("Starting");
  delay(1000);

  // Setting up Loadcell
  scale.begin(Data, Clock);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Setting Up...");                
  scale.tare();
  scale.set_scale(-58920); // Calibration factor
  delay(2000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hang Bottle");
  delay(10000);
  lcd.clear();
  MaxWeight = scale.get_units(20) * 1000;
  delay(2000);
  MaxWeight = scale.get_units(20) * 1000;
  delay(1000);
  Serial.begin(115200);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MaxLevel : ");
  lcd.print(MaxWeight);
}

void loop() {
  CurrWeight=scale.get_units(20) * 1000;
  Reading = (CurrWeight * 100) / MaxWeight;
  if(Reading<=0)
  {
    Reading=0;
  }
  if(Reading>=100)
  {
    Reading=100;
  }
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level : ");
  Serial.println(Reading);
  lcd.print(Reading);
  lcd.print("%");
  

  // Power down the scale to save energy
  scale.power_down();
  delay(15000);
  scale.power_up();
}
