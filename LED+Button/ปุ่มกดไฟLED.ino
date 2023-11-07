#define ledRed 7
#define ledGreen 8
#define ledYellow 10

bool buttonStateRed = false;
bool buttonStateGreen = false;
bool buttonStateYellow = false;

bool ledStateRed = false;
bool ledStateGreen = false;
bool ledStateYellow = false;

void setup() {
  Serial.begin(9600);

  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledYellow, OUTPUT);
}
void loop() {
  buttonStateRed = digitalRead(2);
  buttonStateGreen = digitalRead(3);
  buttonStateYellow = digitalRead(4);
  if (buttonStateRed == LOW) {
    ledStateRed = !ledStateRed;  
    if (ledStateRed) {
      digitalWrite(ledRed, HIGH);
    } else {
      digitalWrite(ledRed, LOW);
    }
    delay(200);  
  }
  if (buttonStateGreen == LOW) {
    ledStateGreen = !ledStateGreen; 
    if (ledStateGreen) {
      digitalWrite(ledGreen, HIGH);
    } else {
      digitalWrite(ledGreen, LOW);
    }
    delay(200); 
  }
  if (buttonStateYellow == LOW) {
    ledStateYellow = !ledStateYellow; 
    if (ledStateYellow) {
      digitalWrite(ledYellow, HIGH);
    } else {
      digitalWrite(ledYellow, LOW);
    }
    delay(200);
  }
}