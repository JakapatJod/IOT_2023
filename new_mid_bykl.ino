
#define BLYNK_TEMPLATE_ID "TMPL6Mwe8w9t3"
#define BLYNK_TEMPLATE_NAME "Mid"
#define BLYNK_AUTH_TOKEN "yKaVWd-oCNPIE8JhlutL4A6EPt2oJRfy"



#define BLYNK_PRINT Serial

#include "DHT.h"

#define DHTPIN D4
#define DHTTYPE DHT22


DHT dht(DHTPIN, DHTTYPE);
const int pingPin = D5; // Trig Ultrasonic
int inPin = D6;  // Echo Ultrasonic

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "jakapat";
char pass[] = "Jakapat12";

BlynkTimer timer;
int count = 0;

BLYNK_WRITE(V0) {
  int value = param.asInt();  // แปลงเป็น integer
  Blynk.virtualWrite(V1, value);

}

BLYNK_CONNECTED() {
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent() {

  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup() {
  // Debug console
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);
  dht.begin();
}

void loop() {
  long duration, distance;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  distance = (duration/2) / 29.1; //ได้ระยะทาง เซนติเมตร
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println(" cm");
  

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  Serial.print(F("Temperature: "));
  Serial.print(temperature , 1);
  Serial.print(F("°C : "));

  Serial.print(F("Humidity: "));
  Serial.print(humidity , 1);
  Serial.println(F("%"));


  delay(500);
  
  Blynk.run();
  Blynk.virtualWrite(V5, distance);
  Blynk.virtualWrite(V6, temperature);
  Blynk.virtualWrite(V7, humidity);

  timer.run();

}
