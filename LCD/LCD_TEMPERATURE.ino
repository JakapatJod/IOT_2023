#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22   // DHT 22 (AM2302), AM2321

DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);  // เลขฐาน 16 set LCD address to 0x27

int screenWidth = 16;
int screenHeight = 2;

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 example!"));

  dht.begin();

  lcd.init();
  lcd.backlight();
  lcd.begin(screenWidth, screenHeight); // เซ็ตขนาดจอ
}

void loop() {
  lcd.setCursor(0, 0); // set บรรทัดแรก
  lcd.print("Temp: ");

  lcd.setCursor(0, 1); // set บรรทัดสอง
  lcd.print("Humid: ");

  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    lcd.setCursor(6, 0);
    lcd.print("Error");
    lcd.setCursor(6, 1);
    lcd.print("Error");
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Display temperature and humidity on the LCD
  lcd.setCursor(6, 0); // ตำแหน่ง X , Y ในจอ
  lcd.print(temperature, 1);
  lcd.print("C ");
  lcd.setCursor(6, 1);
  lcd.print(humidity, 1);
  lcd.print("%");

  // Display temperature and humidity on the Serial Monitor
  Serial.print(F("Temperature: "));
  Serial.print(temperature , 1);
  Serial.print(F("°C : "));
  Serial.print((temperature * 9/5) + 32 , 1); 
  Serial.println(F("°F")); // println คือการปริ้นต่อท้ายอยู่ ปรืิ้นเสร็จนี้จะขึ้นบรรทัดใหม่
  

  Serial.print(F("Humidity: "));
  Serial.print(humidity , 1);
  Serial.println(F("%"));


  delay(2000);
}