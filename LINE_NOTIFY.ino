#include <TridentTD_LineNotify.h>

#define SSID "jakapat"
#define PASSWORD "Jakapat12"
#define LINE_TOKEN "DKNdukObKwh27HtV0N4AN4ZZEgyNyRTX2mClrMr16n9"

void setup() {
  Serial.begin(115200); Serial.println();
  Serial.println(LINE.getVersion());

  WiFi.begin(SSID, PASSWORD);
  Serial.printf("WiFi connecting to %s\n");
  while (WiFi.status() != WL_CONNECTED) { Serial.print("."); delay(400);}
  Serial.printf("\nWiFi connected\nIP : ");
  Serial.println(WiFi.localIP());

  LINE.setToken(LINE_TOKEN);

  LINE.notify("TEST Hello LINE NOTIFY");

  LINE.notify(1234);
  LINE.notify(212.43434,5);

  LINE.notifySticker(3,240);
  LINE.notifySticker("Hello",1,2);

  LINE.notifyPicture("https://www.ai-corporation.net/wp-content/uploads/2021/10/the-innovation-3.png");
  LINE.notifyPicture("โลโก้เว็บไซต์","https://www.ai-corporation.net/wp-content/uploads/2021/10/the-innovation-3.png");

}
void loop (){
  delay(1000);
}