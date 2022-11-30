

//  __    __           _   _                 __           _                     
// / / /\ \ \___  __ _| |_| |__   ___ _ __  / _\_   _ ___| |_ ___ _ __ ___  ___ 
// \ \/  \/ / _ \/ _` | __| '_ \ / _ \ '__| \ \| | | / __| __/ _ \ '_ ` _ \/ __|
//  \  /\  /  __/ (_| | |_| | | |  __/ |    _\ \ |_| \__ \ ||  __/ | | | | \__ \
//   \/  \/ \___|\__,_|\__|_| |_|\___|_|    \__/\__, |___/\__\___|_| |_| |_|___/
//                                              |___/                           
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
 
#define DHTPIN 12          // D3
 
// Uncomment whatever type you're using!
//#define DHTTYPE DHT11     // DHT 11
#define DHTTYPE DHT22   // DHT 22, AM2302, AM2321
//#define DHTTYPE DHT21   // DHT 21, AM2301
 
DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
#include <LiquidCrystal_I2C.h>

// set the LCD number of columns and rows
int lcdColumns = 16;
int lcdRows = 2; 
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  
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
  lcd.init();
  lcd.backlight();

  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  Blynk.run();
  timer.run();
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  Serial.print("Temp : ");
  Serial.print(t);
  Serial.println(" ");
  lcd.setCursor(0,0);
  lcd.print("SUHU : ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("LEMBAB : ");
  lcd.print(h);
  lcd.print(" %");
}
