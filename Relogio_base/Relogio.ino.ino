#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"
//#include "sensorData.h"

#define DHTPIN 6 // pin connected to the temperature sensor
#define DHTTYPE DHT11 //DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int ldr = A1;
int ldrval = 0;
int ldrled = 4;



//Array simbolo grau
byte grauC[8] ={ 
                B11000,
                B11000,
                B00110,
                B01001,
                B01000,
                B01000,
                B01001,
                B00110
                        };
                       
void setup() {
  pinMode(ldr, INPUT);
  pinMode(ldrled, OUTPUT);
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Hello, World!!");
  delay(2000);
  lcd.clear();
  lcd.createChar(0, grauC); //cria caractere de grau e C

  dht.begin();

}

void loop()
{
  sensors_event_t event;
  
//imprime temperatura
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.setCursor(6, 0);
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature))
  {
    lcd.print(event.temperature);
   }
  lcd.setCursor(11, 0);
  //lcd.print((char) 223); //imprime º
  lcd.write((byte)0); //caracrete de grau + C, montado anteriormente
  //lcd.setCursor(12, 0);
  //lcd.print("C");

 

//imprime umidade
  lcd.setCursor(0, 1);
  lcd.print("Umid: ");
  lcd.setCursor(6, 1);
  dht.humidity().getEvent(&event);
   if (!isnan(event.relative_humidity))
  {
    lcd.print(event.relative_humidity);
  }
  lcd.setCursor(11, 1);
  //lcd.print("%");
  lcd.print((char) 37); //imprime %

//imprime LDR
  lcd.setCursor(13, 0);
  //lcd.print("LDR");
  lcd.println(millis());  
  lcd.setCursor(13, 1);
  ldrval = analogRead(ldr);
  lcd.print(ldrval);
  delay(1000);

//Display led
  if (ldrval>450) {
    digitalWrite(ldrled, LOW);
    }
  else  {
    digitalWrite(ldrled, HIGH);
    }
}
