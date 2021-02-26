
int ldr = A1;
int LedVerde = 4;
int ldrValor = 300;
int higlo = A3;
higlo


// the setup function runs once when you press reset or power the board
void setup()
  {
   pinMode(LedVerde,OUTPUT);
   pinMode(ldr,INPUT);
   pinMode(higlo,INPUT);
  }

// the loop function runs over and over again forever
void loop()
{
  if(analogRead(higlo) < ldrValor)
     {
      digitalWrite(LedVerde,LOW);
    }
    else 
    {
      digitalWrite(LedVerde,HIGH);
     }

if(analogRead(ldr) < ldrValor)
     {
      digitalWrite(LedVerde,LOW);
    }
    else 
    {
      digitalWrite(LedVerde,HIGH);
     }

 
}
