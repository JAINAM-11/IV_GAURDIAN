#include<ESP8266WiFi.h>
#include<ESP8266HTTPClient.h>

HTTPClient http;

const char* WIFINAME = "JAINAM";
const char* PASS = "12341234";
//int led = D0;
WiFiServer server(80);

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("");
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.print("Connecting To ");
  Serial.println(WIFINAME);


  WiFi.begin(WIFINAME, PASS);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop(){
  
}