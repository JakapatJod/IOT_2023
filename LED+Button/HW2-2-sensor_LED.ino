// C++ code
//
int sensorPin = A5;
int ledRed = 12;
int ledGreen = 10;
int ledYellow = 8;

void setup()
{
  Serial.begin(9600);
  pinMode(ledRed , OUTPUT);
  pinMode(ledGreen , OUTPUT);
  pinMode(ledYellow , OUTPUT);

}

void loop()
{
	int sensorValue = analogRead(sensorPin);
  	Serial.print("LDR Value = ");
  	Serial.println(sensorValue);
  	delay(1000);
  	if ( sensorValue > 250 ) {
    	digitalWrite (ledRed , HIGH); 
    	digitalWrite (ledGreen , LOW);
    	digitalWrite (ledYellow , LOW);}
  	
  	else if( sensorValue < 100 ) {
    	digitalWrite (ledGreen , LOW); 
    	digitalWrite (ledRed , LOW);
    	digitalWrite (ledYellow , HIGH);}
  
  	else {
    	digitalWrite (ledYellow , LOW); 
    	digitalWrite (ledRed , LOW);
    	digitalWrite (ledGreen , HIGH);}
}