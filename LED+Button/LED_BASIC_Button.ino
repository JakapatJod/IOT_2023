// C++ code
//
int ledred =  7;
void setup()
{
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(ledred , OUTPUT);
}

void loop()
{
  int sensorVal = digitalRead(2);
  Serial.println(sensorVal);
  if (sensorVal == HIGH){
  	digitalWrite(LED_BUILTIN,LOW);
    digitalWrite(ledred,LOW);
  } else {
  	digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(ledred,HIGH);
  }
}