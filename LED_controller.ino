
#define BLYNK_TEMPLATE_ID "TMPL6T2v2jUxE"
#define BLYNK_TEMPLATE_NAME "LEDController"
#define BLYNK_AUTH_TOKEN "_q39Si1NgHWy3ZCJciTze93wGCLThAbk"

#define BLYNK_PRINT Serial

#define relay1 D5
#define relay2 D6

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>


char ssid[] = "jakapat";
char pass[] = "jakapat12";

BlynkTimer timer;

BLYNK_WRITE(V0)
{
  int value = param.asInt();

  Blynk.virtualWrite(V1, value);
}

BLYNK_WRITE(V5)
{
    if (param.asInt() == 0) {
        digitalWrite(relay1, !digitalRead(relay1));
        if (digitalRead(relay1) == LOW) {

        }
        else {

        }
    }

    if (param.asInt() == 1) {
        digitalWrite(relay1, !digitalRead(relay1));
        if (digitalRead(relay1) == HIGH) {

        }
        else {

        }
    }
}

BLYNK_WRITE(V6)
{
    if (param.asInt() == 0) {
        digitalWrite(relay2, !digitalRead(relay2));
        if (digitalRead(relay2) == LOW) {

        }
        else {

        }
    }

    if (param.asInt() == 1) {
        digitalWrite(relay2, !digitalRead(relay2));
        if (digitalRead(relay2) == HIGH) {

        }
        else {

        }
    }
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
  // Debug console
  Serial.begin(115200);
    
  pinMode(relay2, OUTPUT);

  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(1000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run();

}
