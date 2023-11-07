int LED_RED = 1;
int LED_GREEN = 13;
int LED_YELLOW = 4;
int count = 1;

void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);  
}

void loop() {
  flashRedLED();
  flashGreenYellowLED();
}

void flashRedLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_RED, HIGH);
    delay(1000);

    Serial.print("Round Count = ");
    Serial.println(count);
    count++;

    digitalWrite(LED_RED, LOW);
    delay(1000);
  }
}

void flashGreenYellowLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(LED_GREEN, HIGH);
    delay(1000);

    Serial.print("Round Count = ");
    Serial.println(count);
    count++;

    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_YELLOW, HIGH);
    delay(1000);

    digitalWrite(LED_YELLOW, LOW);
    Serial.print("Round Count = ");
    Serial.println(count);
    count++;
  }
}