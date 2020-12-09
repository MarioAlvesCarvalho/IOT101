
void setup()
{
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}

void loop()
{                    
  digitalWrite(13, HIGH);
  Serial.println("Ligado")
  delay(1000);                     
  digitalWrite(13, LOW);
  Serial.println("Desligado")
  delay(1000);                      
}
