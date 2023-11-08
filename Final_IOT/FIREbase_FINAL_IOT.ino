#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS D3 //กำหนดขาที่จะเชื่อมต่อ Sensor
#include <Servo.h>
#include "DHT.h"
#include <TridentTD_LineNotify.h>
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <time.h> 

int timezone = 7;

char ntp_server1[20] = "ntp.ku.ac.th";
char ntp_server2[20] = "fw.eng.ku.ac.th";
char ntp_server3[20] = "time.uni.net.th";

int dst = 0;

const int pingPin = D1;
int inPin = D2;

#define FIREBASE_HOST "iotdb-5bc97-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "rJHfPNUfv6vyX2YZdIcnXV1Qb3yUfXWvEnzw0qno"

#define LINE_TOKEN "5dRhLyINoGodieLlkxHKmFfvGGxCn4vcgvv0wIgKCQr"

#define WIFI_SSID "Bunnapon"
#define WIFI_PASSWORD "Bunnapon123"

#define DHTPIN D6 
#define DHTTYPE DHT22 

int sensorPin = D5;
volatile long pulse;
unsigned long lastTime;
Servo myservo; //ประกาศตัวแปรแทน Servo
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DHT dht(DHTPIN, DHTTYPE);

float volume;

void setup(void) {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");

  while (WiFi.status() != WL_CONNECTED) {
  Serial.print("...");
  delay(500);
  }

  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  LINE.setToken(LINE_TOKEN);

  configTime(timezone * 3600, dst, ntp_server1, ntp_server2, ntp_server3);
  Serial.println("Waiting for time");
  while (!time(nullptr)) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.println("Now: " + NowString());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/TEST/SAVO"); 
  pinMode(sensorPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(sensorPin), increase, RISING);
  myservo.attach(2);
  Serial.println("Dallas Temperature IC Control Library");
  sensors.begin();
  dht.begin();
}

void loop(void) {
  long duration, cm;
  float h = dht.readHumidity();
  
  Serial.println("Requesting temperatures...");
  sensors.requestTemperatures();
  Serial.print("Temperature is: ");
  float tem_water = sensors.getTempCByIndex(0);
  Serial.print(sensors.getTempCByIndex(0));
  Serial.println(" *C");
  volume = 2.663 * pulse / 1000 * 30;
  if (millis() - lastTime > 2000) {
    pulse = 0;
    lastTime = millis();
  }

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  cm = microsecondsToCentimeters(duration);
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  Serial.print(volume);
  Serial.println(" L/m");
  Serial.print(F("Humidity: "));
  Serial.print(h);

  String foodStatus;
  if (cm < 50) {
    foodStatus = "อาหารเหลือเพียงพอ";
  } else {
    foodStatus = "อาหารเหลือน้อย !!";
    LINE.notify("อาหารเหลือน้อย !!");
  }

  if (Firebase.available()) {
     FirebaseObject event = Firebase.readEvent();
     String eventType = event.getString("type");
     eventType.toLowerCase();

     if (eventType == "") return ;
     Serial.print("event: ");
     Serial.println(eventType);
     
     if (eventType == "put") {
       String path = event.getString("path");
       int data = event.getInt("data");
       Serial.println("[" + path + "] " + String(data));
        
         if(data == 0){
          Serial.println("ปิดไฟ : 0 ");
          myservo.write(0);
         }else{
             Serial.println("เปิดไฟ : 1 ");
             myservo.write(180);
         }
        

     }
  }

  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject();
  root["temperature"] = tem_water;
  root["humidity"] = h;
  root["volume"] = volume;
  root["food"] = cm;
  root["foodStatus"] = foodStatus;
  root["time"] = NowString();

  String name = Firebase.push("logDHT", root);

  if (Firebase.failed()) {
    Serial.print("pushing /logs failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.print("pushed: /logDHT/");
  Serial.println(name);

  
  
  delay(1500);
}


ICACHE_RAM_ATTR void increase() {
  pulse++;
}

long microsecondsToCentimeters(long microseconds)
{

return microseconds / 29 / 2;
}

String NowString() {
  time_t now = time(nullptr);
  struct tm* newtime = localtime(&now);
 
String tmpNow = "";
  tmpNow += String(newtime->tm_year + 1900);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mon + 1);
  tmpNow += "-";
  tmpNow += String(newtime->tm_mday);
  tmpNow += " ";
  tmpNow += String(newtime->tm_hour);
  tmpNow += ":";
  tmpNow += String(newtime->tm_min);
  tmpNow += ":";
  tmpNow += String(newtime->tm_sec);
  return tmpNow;
}