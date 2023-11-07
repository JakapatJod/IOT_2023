User
# define ledRed 7
# define ledGreen 8
# define ledYellow 10

void setup () { 
  Serial.begin(9600);

  pinMode(2,INPUT_PULLUP);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledRed,OUTPUT);
  pinMode(ledGreen,OUTPUT);
  pinMode(ledYellow,OUTPUT);

}
void loop () {
  int sensorVal = digitalRead(2);
  Serial.println(sensorVal);
  if (sensorVal == LOW) {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(ledRed, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(ledRed, LOW);
  }
}