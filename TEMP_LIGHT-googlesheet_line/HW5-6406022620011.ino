  #include <ESP8266WiFi.h>
  #include <WiFiClientSecure.h>
  #include "DHT.h"
  #include <Wire.h>
  #include <BH1750.h>

  BH1750 lightMeter;
  #define DHTTYPE DHT22 // DHT 11
  const int DHTPin = D4;
  String t;
  #define ON_Board_LED 2 

  const char* ssid = "่jakapat";     
  const char* password = "Jakapat12";  
#define LINE_TOKEN "Ggfxi5QdivPMCJsqtvJCl7omFgYtSkGFA64eAOfkWxg"

  const char* host = "script.google.com";
  const int httpsPort = 443;

  DHT dht(DHTPin, DHTTYPE);
  WiFiClientSecure client; 

  long now = millis();
  long lastMeasure = 0;
  String GAS_ID = "AKfycbzrlr2lMhFv4lMOcUPr6zKGkQKFE1_RUqwpCntUh90eyFE7QV0EsgvXGk-Is6Y1IddHPw"; 
  void setup() {
    Serial.begin(115200);
    delay(500);
    dht.begin();
    WiFi.begin(ssid, password); 
    Serial.println("");
    pinMode(ON_Board_LED, OUTPUT); 
    digitalWrite(ON_Board_LED, HIGH); 

    Wire.begin();
    lightMeter.begin();

    Serial.print("Connecting");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      digitalWrite(ON_Board_LED, LOW);
      delay(250);
      digitalWrite(ON_Board_LED, HIGH);
      delay(250);
    }

    digitalWrite(ON_Board_LED, HIGH); 

    Serial.println("");
    Serial.print("Successfully connected to : ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
    Serial.println();

    client.setInsecure();
  }

  void loop() {
    now = millis();
    if (now - lastMeasure > 3000) {
      lastMeasure = now;

      float h = dht.readHumidity();
      float t = dht.readTemperature();
      float f = dht.readTemperature(true);
      float lux = lightMeter.readLightLevel();

      if (isnan(h) || isnan(t) || isnan(f)) {
        Serial.println("Failed to read from DHT sensor!");
        return;
      }

      float hic = dht.computeHeatIndex(t, h, false);
      static char temperatureTemp[7];
      dtostrf(hic, 6, 2, temperatureTemp);

      static char humidityTemp[7];
      dtostrf(h, 6, 2, humidityTemp);

      Serial.print("Humidity: ");
      Serial.print(h);
      Serial.print(" %\t Temperature: ");
      Serial.print(t);
      Serial.print(" *C ");
      Serial.print(f);
      Serial.print(" *F\t Heat index: ");
      Serial.print(hic);
      Serial.println(" *C ");

      Serial.print("Light: ");
      Serial.print(lux);
      Serial.println(" lx");
      sendData(t, h, lux);
      delay(60000);

    }
  }

  void sendData(float value, float value2 ,float value3 ) {
    Serial.println("==========");
    Serial.print("connecting to ");
    Serial.println(host);

    if (!client.connect(host, httpsPort)) {
      Serial.println("connection failed");
      return;
    }

    float string_temp = value;
    float string_humi = value2;
    float string_light = value3;
    String url = "/macros/s/" + GAS_ID + "/exec?temp=" + string_temp + "&humi=" + string_humi + "&light=" + string_light;
    Serial.print("requesting URL: ");
    Serial.println(url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                "Host: " + host + "\r\n" +
                "User-Agent: BuildFailureDetectorESP8266\r\n" +
                "Connection: close\r\n\r\n");
    Serial.println("request sent");

    while (client.connected()) {
      String line = client.readStringUntil('\n');
      if (line == "\r") {
        Serial.println("headers received");
        break;
      }
    }

    String line = client.readStringUntil('\n');
    if (line.startsWith("{\"state\":\"success\"")) {
      Serial.println("esp8266/Arduino CI successfull!");
    } else {
      Serial.println("esp8266/Arduino CI failed");
    }

    Serial.print("reply was : ");
    Serial.println(line);
    Serial.println("closing connection  ");
    Serial.println("==========");
    Serial.println();
  }