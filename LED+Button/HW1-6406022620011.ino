// C++ code
//
int LED_RED = 3;
int LED_GREEN = 13;
int LED_YELLOW = 4;
int count = 1 ;

void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
}

void loop()
{
    for (int i = 1; i<6 ; i++){
  	digitalWrite(LED_RED,HIGH);
  	delay(1000);
    
    Serial.print("Round Count = ");
  	Serial.println(count);
  	count++; // count += 1
    
    digitalWrite(LED_RED,LOW);
  	delay(1000);
   
  } 
   for (int i = 1; i<6 ; i++){
    digitalWrite(LED_GREEN, HIGH);

  	delay(1000);
     
    Serial.print("Round Count = ");
  	Serial.println(count);
  	count++; // count += 1
     
  	digitalWrite(LED_GREEN, LOW);
  	digitalWrite(LED_YELLOW, HIGH);
  	delay(1000); 
     
    digitalWrite(LED_YELLOW,LOW);
    Serial.print("Round Count = ");
  	Serial.println(count);
  	count++; // count += 1
  }
}