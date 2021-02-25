#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"

#define DHTPIN 6 // pin connected to the temperature sensor
#define DHTTYPE DHT11 //DHT22
DHT_Unified dht(DHTPIN, DHTTYPE);

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int ldr = A1;
int ldrval = 0;
int ldrled = 4;
int buzina = 2;

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
sensors_event_t event;  //Evento para receber os valores do sensor de temp/umid
                       
void setup() {
  pinMode(ldr, INPUT);  //Define o 'ldr' como pine de entrada
  pinMode(ldrled, OUTPUT);  //Define o 'ldrled' com pino de saida

  digitalWrite(ldrled, HIGH);

  tone(buzina,1000,1000);
  delay(200);
  noTone(buzina);
  delay(1000);
  tone(buzina,100,1000);
  delay(200);
  noTone(buzina);
  tone(buzina,1000);
  delay(200);
  noTone(buzina);
  
  lcd.begin(16, 2); //Seta curso na coluna e linha
  lcd.setCursor(0, 0);  //Seta curso na coluna e linha
  lcd.print(" Hello, World!!");  //Imprime mensagem do LCD
  lcd.setCursor(0, 1);  //Seta curso na coluna e linha
  lcd.print("OI sou o Babuino");  //Imprime mensagem do LCD
  delay(3000);  //Aguarda 2seg
  lcd.clear();  //Limpa tela
  lcd.createChar(0, grauC); //Cria caractere de grau e C
  dht.begin();  //Inicia sensor DHT11
 }

void loop(){
//  sensors_event_t event;  //Evento para receber os valores do sensor de temp/umid
  tarefa1();  // Imprime Temperatura
  tarefa2();  // Imprime Umidade
  tarefa3();  // Imprime LDR
  tarefa4();  // Controla led Display
  delay(1000);
 }

void tarefa1(){ // Imprime Temperatura
  lcd.setCursor(0, 0);  //Seta curso na coluna e linha
  lcd.print("Temp: ");  //Imprime mensagem do LCD
  lcd.setCursor(6, 0);  //Seta curso na coluna e linha
  dht.temperature().getEvent(&event); //Recebe temperatura do sensor
  if (!isnan(event.temperature))  //Valida se valor é numerico (se não é isnan)
  {
    lcd.print(event.temperature);
   }
  //Seta Cursor
  lcd.setCursor(11, 0);
  //lcd.print((char) 223); //imprime º - Outra forma de imprimir o grau
  //lcd.setCursor(12, 0);  //Seta curso na coluna e linha
  //lcd.print("C"); //Imprime mensagem do LCD
  lcd.write((byte)0); //caracrete de grau + C, montado anteriormente
}
 
void tarefa2(){
//Imprime Umidade
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
}

// Controla led Display
void tarefa3(){
  lcd.setCursor(13, 0);
  //lcd.print("LDR");
  lcd.println(millis());  
  lcd.setCursor(13, 1);
  ldrval = analogRead(ldr);
  lcd.print(ldrval);
}

// Controla led Display
void tarefa4(){
  if (ldrval>450) {
    digitalWrite(ldrled, LOW);
    }
  else  {
    digitalWrite(ldrled, HIGH);
    }
}
