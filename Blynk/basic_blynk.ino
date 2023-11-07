
#define BLYNK_TEMPLATE_ID           "TMPL6o_O-0R6x"
#define BLYNK_TEMPLATE_NAME         "Quickstart Template"
#define BLYNK_AUTH_TOKEN            "JaAzCkavqzZ0a5-nU2jrBNuzqMTLyMXQ"


#define BLYNK_PRINT Serial

#include "DHT.h"

#define DHTPIN D4     
#define DHTTYPE DHT22   

DHT dht(DHTPIN, DHTTYPE);

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "jakapat";
char pass[] = "Jakapat12";

BlynkTimer timer;
int count = 0;

BLYNK_WRITE(V0)
{
  int value = param.asInt(); // แปลงเป็น integer
  Blynk.virtualWrite(V1, value);
  if (value == 1){
    count++;
   
  }
  
  Blynk.virtualWrite(V4, count);
}

BLYNK_CONNECTED()
{
  Blynk.setProperty(V3, "offImageUrl", "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations.png");
  Blynk.setProperty(V3, "onImageUrl",  "https://static-image.nyc3.cdn.digitaloceanspaces.com/general/fte/congratulations_pressed.png");
  Blynk.setProperty(V3, "url", "https://docs.blynk.io/en/getting-started/what-do-i-need-to-blynk/how-quickstart-device-was-made");
}

void myTimerEvent()
{

  Blynk.virtualWrite(V2, millis() / 1000);
}

void setup()
{
 
  Serial.begin(115200);

  pinMode(LED_RED,OUTPUT);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);
  dht.begin();

}

void loop()
{
  
  Blynk.run(); 
  timer.run();
}