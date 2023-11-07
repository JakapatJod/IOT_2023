#include <LiquidCrystal_I2C.h>
#define TRIGGERPIN D6
#define ECHOPIN D7


LiquidCrystal_I2C lcd(0x27, 16, 2);  // เลขฐาน 16 set LCD address to 0x27

int screenWidth = 16;
int screenHeight = 2;
void setup () {
  Serial.begin(57600);
  pinMode(TRIGGERPIN , OUTPUT);
  pinMode(ECHOPIN, INPUT);
  lcd.init();
  lcd.backlight();
  lcd.begin(screenWidth, screenHeight); // เซ็ตขนาดจอ
}
void loop(){

  lcd.setCursor(0, 0); // set บรรทัดแรก
  lcd.print("Distance: ");

  lcd.setCursor(0, 1); // set บรรทัดสอง
  lcd.print("Distance: ");

  long duration, distance;
  digitalWrite(TRIGGERPIN ,LOW);
  delayMicroseconds(3);

  digitalWrite(TRIGGERPIN, HIGH);
  delayMicroseconds(12);

  digitalWrite(TRIGGERPIN , LOW);
  duration = pulseIn(ECHOPIN, HIGH);
  distance = (duration/2) / 29.1; //ได้ระยะทาง เซนติเมตร

  lcd.setCursor(9, 0); // ตำแหน่ง X , Y ในจอ
  lcd.print(distance);
  lcd.print(" cm");
  lcd.setCursor(9, 1);
  lcd.print(distance * 0.39370,0);
  lcd.print(" inch");


  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" Cm");
  Serial.print("Distance: ");
  Serial.print(distance * 0.39370,0);
  Serial.println(" inch");
  delay(2000);
}