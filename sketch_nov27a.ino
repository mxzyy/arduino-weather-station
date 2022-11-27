// ----
// WEATHER STATION 
// Created by @mxzyy
// ----
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPLmaHjKFz8"
#define BLYNK_DEVICE_NAME "Weather System"
#define BLYNK_AUTH_TOKEN "qf8uk1uT6tmvodHSD5H_fh6GNPOdf7fH"
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
 
// init 
char auth[] = "qf8uk1uT6tmvodHSD5H_fh6GNPOdf7fH"; 
char ssid[] = "andaikan";
char pass[] = "12345678";
 
#define DHTPIN 5          // D3
 
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
 

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
 
void setup()
{
  // Debug console
  Serial.begin(9600);
 
  Blynk.begin(auth, ssid, pass);
  
 
  dht.begin();
 

  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
}
