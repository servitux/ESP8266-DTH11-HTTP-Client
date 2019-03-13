#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include "DHTesp.h"

const char* ssid = "www.servitux.es";
const char* password = "password";
DHTesp dht;

void setup() {
  Serial.begin(115200);
  delay(10);
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Print the IP address
  Serial.println(WiFi.localIP());

  dht.setup(2, DHTesp::DHT11); 
}

void loop() {

    WiFiClient client;
    HTTPClient http;

    delay(dht.getMinimumSamplingPeriod());

    float humidity = dht.getHumidity();
    float temperature = dht.getTemperature();

    String web = "http://10.6.0.20/?t=";
    web += temperature;
    web += "&h=";
    web += humidity;
    
    if (http.begin(client, web)) {
      int httpCode = http.GET(); 
      http.end();      
    }
    delay(60000);

}
