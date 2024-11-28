#include "HX711.h"
#include <LiquidCrystal_I2C.h>
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
#include <Adafruit_NeoPixel.h>

const char* WIFINAME = "JAINAM";
const char* PASS = "12341234";
const char* FIREBASE_HOST = "iv-gaurdian-default-rtdb.asia-southeast1.firebasedatabase.app/";
const char* FIREBASE_AUTH = "zEd4wcOstQQsPB4XJRO93t7mSUcHQyL6xx94KErd";

#define Clock 13  // HX711 SCK D7
#define Data 12   // HX711 DT D6   
#define LED_PIN 14 // LED DI D5
#define NUM_LEDS 8  

HX711 scale;
LiquidCrystal_I2C lcd(0x27, 16, 4);
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);
FirebaseData fbdo;

String DEVICE_ID;
float MaxWeight = 0;
float CurrWeight = 0;
float Reading = 0;
bool Alert1 = false;
bool Alert2 = false;

void setup() {
  lcd.init();
  lcd.backlight();
  strip.begin();
  strip.show();
  strip.setBrightness(32); // Lower brightness to save memory

  WiFi.begin(WIFINAME, PASS);
  lcd.setCursor(0, 0);
  lcd.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  lcd.clear();
  lcd.print("WiFi Connected");
  delay(1000);

  DEVICE_ID = WiFi.macAddress();
  DEVICE_ID.replace(":", "");
  Serial.begin(9600);
  Serial.print("Device ID: ");
  Serial.println(DEVICE_ID);

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

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
  MaxWeight = scale.get_units(20) * 1000;
  Firebase.setFloat(fbdo, "/Device/" + DEVICE_ID + "/MaxWeight", MaxWeight);
}

void loop() {
  CurrWeight = scale.get_units(20) * 1000;
  Firebase.setFloat(fbdo, "/Device/" + DEVICE_ID + "/CurrWeight", CurrWeight);
  Reading = (CurrWeight * 100) / MaxWeight;

  if (Reading <= 0) Reading = 0;
  if (Reading >= 100) Reading = 100;

  static float lastReading = -1;
  if (abs(Reading - lastReading) > 1) {
    Firebase.setFloat(fbdo, "/Device/" + DEVICE_ID + "/Level", Reading);
    lastReading = Reading;
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Level : ");
  Serial.println(Reading);
  lcd.print(Reading);
  lcd.print("%");

  strip.clear();
  if (Reading >= 60) {
    strip.fill(strip.Color(0, 255, 0), 0, NUM_LEDS);
  } else if (Reading >= 30) {
    strip.fill(strip.Color(255, 255, 0), 0, NUM_LEDS);
  } else {
    strip.fill(strip.Color(255, 0, 0), 0, NUM_LEDS);
  }
  strip.show();

  // scale.power_down();
  delay(2000);
  // scale.power_up();
}

