
#include <TridentTD_LineNotify.h>
#include <DHT22.h>
#include <BH1750FVI.h>
#include <WiFiClientSecure.h>

#define data 13
float temb = 0.0;  // อุณหภูมิก่อนหน้า
float hunb = 0.0;
float lunb = 0.0;  // ความชื้นก่อนหน้า
int count_round = 1;


#define SSID        "Main_Home_2G"
#define PASSWORD    "0953529641"
#define LINE_TOKEN  "fw7T6yctjysHilpe5ETnMfzqIXCia0bWbuIVNqQEuKg"


const char* host = "script.google.com";
const int httpsPort = 443;

DHT22 dht22(data);
BH1750FVI LightSensor(BH1750FVI::k_DevModeContLowRes);

unsigned long previousMillis = 0;
const long interval = 60000; // หน่วงเวลา 1 นาที

WiFiClientSecure client; 

String GAS_ID = "AKfycbzWsdQJBjTQGsFE32JxTjdvz8CCd8pbZvmMPHZQVhs408R1PnSND9Qem-HG9Q3Faprf";

void setup() {


  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());
  
  WiFi.begin(SSID, PASSWORD);

  LINE.setToken(LINE_TOKEN);

  LightSensor.begin();
  
  client.setInsecure();

}

void sendData(float value,float value2,float value3) {
  if (!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }
  float string_temp = value;
  float string_humi = value2;
  float string_lux = value3;

  client.print(String("GET ") + "/macros/s/" + GAS_ID + "/exec?temp=" + string_temp + "&humi="+string_humi + "&lux="+string_lux + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" +
  "User-Agent: BuildFailureDetectorESP8266\r\n" +
  "Connection: close\r\n\r\n");

}

void loop() {
  unsigned long currentMillis = millis();

  float t = dht22.getTemperature();
  float h = dht22.getHumidity();
  uint16_t lux = LightSensor.GetLightIntensity();

  if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;

      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t Temperature: ");
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print(" \t Ligth index: ");
      Serial.print(lux);
      Serial.print(" round: ");
      Serial.println(count_round);
      count_round++;
      sendData(t,h,lux);
  }

}


