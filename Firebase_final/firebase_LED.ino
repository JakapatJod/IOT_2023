#include <FirebaseArduino.h>
#include <ESP8266WiFi.h>

#define LED_PIN D4

// Config Firebase
#define FIREBASE_HOST "jakapat-dht22-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "AkGMAxUK0wLSyMNFlP1FmIXoZcjipVt2rejWuzRd"

#define WIFI_SSID "jakapat"
#define WIFI_PASSWORD "jakapat12"

void setup() {
  pinMode(LED_PIN, OUTPUT);
  //digitalWrite(LED_BUILTIN,LOW);
  Serial.begin(115200);
  
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.stream("/node1/LED");  
}

void loop() {
  if (Firebase.failed()) {
    Serial.println("streaming error");
    Serial.println(Firebase.error());
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
             digitalWrite(LED_PIN,LOW);
         }else{
            digitalWrite(LED_PIN,HIGH);
             Serial.println("เปิดไฟ : 1 ");
         }
        
       /*
       if (path == "/") {
         digitalWrite(LED_PIN, (data == 0 ? LOW : HIGH));
         
         }
         */
       
     }
  }   
  delay(1000);
}
