

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
#define DHTPIN 12          
#define DHTTYPE DHT22 
 
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <LiquidCrystal_I2C.h>

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
int lcdColumns = 16;
int lcdRows = 2; 
LiquidCrystal_I2C lcd(0x3F, lcdColumns, lcdRows);  

// Wi - Fi Configuration
char auth[] = "qf8uk1uT6tmvodHSD5H_fh6GNPOdf7fH"; 
char ssid[] = "4RBIK TEMULAWAK";
char pass[] = "H3rb4l04";


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
 
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
 
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
}
 
void setup()
{

  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
 
  dht.begin();
  lcd.init();
  lcd.backlight();

  timer.setInterval(1000L, sendSensor);
}
 
void loop()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  
  Blynk.run();
  timer.run();
  lcd.setCursor(0,0);
  lcd.print("SUHU : ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0,1);
  lcd.print("LEMBAB : ");
  lcd.print(h);
  lcd.print(" %");
}
