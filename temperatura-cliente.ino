#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>
#include "DHT.h"

const char* ssid = "network";
const char* password = "password";
#define DHTTYPE DHT11
#define DHTPIN 2

DHT dht(DHTPIN,DHTTYPE);

ESP8266WiFiMulti wifiMulti;

IPAddress staticIP(192,168,0,98);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

void setup() {

  delay(10);  

  WiFi.mode(WIFI_STA);
  WiFi.config(staticIP, gateway, subnet);
  wifiMulti.addAP(ssid,password);
  
  dht.begin();
}

void loop() {

    if (wifiMulti.run() != WL_CONNECTED) {    
      delay(1000);
    }

    delay(60000);

    WiFiClient client;
    HTTPClient http;

    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();

    String web = "http://192.168.0.2/temp.php?t=";
    web += temperature;
    web += "&h=";
    web += humidity;
    
    if (http.begin(client, web)) {
      int httpCode = http.GET(); 
      http.end();      
    }
    client.stop();
}
