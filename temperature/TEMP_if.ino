#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22 example!"));

  dht.begin();
}

void loop() {
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();

  if (isnan(temperature) || isnan(humidity)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Serial.print(F("Temperature: "));
  Serial.print(temperature, 1);
  Serial.print(F("°C : "));
  Serial.print((temperature * 9 / 5) + 32, 1);
  Serial.print(F("°F"));

  if (temperature > 32 || temperature < 28) {
    Serial.println(F(" - Not within standard range"));
  } else {
    Serial.println();
  }

  Serial.print(F("Humidity: "));
  Serial.print(humidity, 1);
  Serial.println(F("%"));

  delay(2000);
}
