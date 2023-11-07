const int pingPin = D1;
int inPin = D2;
int ledRed = D6;

void setup() {
  Serial.begin(115200);
  pinMode(ledRed , OUTPUT);

}
void loop()
{
  long duration,  distance;

  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(12);
  digitalWrite(pingPin, LOW);
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  distance = (duration/2) / 29.1;
  Serial.println(distance);

  Serial.println();
  delay(1000);
  if ( distance > 100 ) {
    digitalWrite (ledRed , HIGH);}
  else {
    	digitalWrite (ledRed , LOW);
  delay(100);}
}
