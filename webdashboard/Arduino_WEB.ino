#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include <BH1750.h>

BH1750 lightMeter;


#include <DHT.h>
#define DHT_PIN D4
#define DHTTYPE DHT22

DHT dht(DHT_PIN, DHTTYPE);

const char* ssid = "jakapat";
const char* password = "jakapat12";

const char* SERVER_NAME = "http://jakapatdb.atwebpages.com/sensordata.php";

String PROJECT_API_KEY = "jakapatmysqldht";
unsigned long lastMillis = 0;
long interval = 5000;


void setup(){
  Serial.begin(115200);
  dht.begin();
  
  Wire.begin();
  
  lightMeter.begin();

  WiFi.begin(ssid,password);
  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
}


void loop(){
  if(WiFi.status()== WL_CONNECTED){
    if(millis() - lastMillis > interval){
      upload_temperature();
      lastMillis = millis();
  }
  else{
    Serial.println("WiFi Disconnected");
  }
  delay(1000);
  }
}

void upload_temperature(){
  float t = dht.readTemperature();

  float h = dht.readHumidity();

  if (isnan(h) || isnan(t)) {
     Serial.println(F("Failed to read DHT"));
     return;
  }

  float hic = dht.computeHeatIndex(t,h, false);

  String humidity = String(h,2);
  String temperature = String(t,2);
  String heat_index = String(hic,2);

  Serial.println("Temperature: "+temperature);
  Serial.println("Humidity: "+humidity);

  float l = lightMeter.readLightLevel();
  String lux = String(l,2);
  Serial.print("Light: ");
  Serial.print(lux);
  Serial.println(" lx");

  String temperature_data;
  temperature_data = "api_key="+PROJECT_API_KEY;
  temperature_data += "&temperature="+temperature;
  temperature_data += "&humidity="+humidity;
  temperature_data += "&light="+lux;

  Serial.print("temperature_data: ");
  Serial.println(temperature_data);

  WiFiClient client;
  HTTPClient http;

  http.begin(client,SERVER_NAME);
  http.addHeader("Content-Type","application/x-www-form-urlencoded");
  int httpResponseCode = http.POST(temperature_data);

  Serial.print("HTTP Response code: ");
  Serial.println(httpResponseCode);
  http.end();
}