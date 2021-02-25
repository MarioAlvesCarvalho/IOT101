//Bare metal LCD sample
//This sketch will show the light reading in the display
//TESTE

#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "SPI.h"
//#include "sensorData.h"
#include "RTClib.h"

RTC_DS1307 rtc;

#define DHTPIN 6 // pin connected to the temperature sensor
#define DHTTYPE DHT11
DHT_Unified dht(DHTPIN, DHTTYPE);

bool startstop = true;
volatile int second = 0, minute = 0, hour = 0;
volatile int day = 0, month = 0, year=1999;
volatile int hour_bip = hour;
int valor_luz = 200;


long debouncing_time = 150; //Debouncing Time in Milliseconds
volatile unsigned long last_micros = 0;
volatile unsigned long last_micros_clock = 0;

//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);


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

 byte AlarmeClock[8] ={
                        B11011,
                        B10001,
                        B01110,
                        B10101,
                        B10101,
                        B10111,
                        B10001,
                        B01110
                      };
byte doispontos[8] = {
  B01110,
  B01010,
  B01110,
  B00000,
  B00000,
  B01110,
  B01010,
  B01110
};

byte doispontosfull[8] = {
  B01110,
  B01110,
  B01110,
  B00000,
  B00000,
  B01110,
  B01110,
  B01110
};

void setup() 
{
  pinMode(A1,INPUT);
  pinMode(5,OUTPUT);
  pinMode(14,OUTPUT);
  digitalWrite(5,1);
  
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(2), buttons, FALLING);
  
  dht.begin();        //initialize the ambient sensor
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("Relogio Babuino!");  
  lcd.setCursor(0, 1);
  lcd.print("Carregando ..... ");  
  
  delay(2000);

  tone(14,1000);
  delay(200);
  noTone(14);
  delay(200);
  tone(14,1000);
  delay(200);
  noTone(14);

  lcd.clear();

  if (! rtc.begin()) 
  {
    lcd.print("Couldn't get RTC");  
    delay(2000);
    lcd.clear();
  }
  //rtc.adjust(DateTime(2020, 11, 7, 10, 29, 0));
  lcd.createChar(0, grauC);  //caracter de grau + C
  lcd.createChar(1, AlarmeClock);  //caracter de Despertador
  lcd.createChar(2, doispontos);  //caracter de dois pontos
  lcd.createChar(3, doispontosfull);  //caracter de dois pontos full
  }

void controlBacklight()
{
  if(analogRead(A1)>valor_luz)
  {
    digitalWrite(5,1);
  }
  else
  {
    digitalWrite(5,0);
  }
}


void printSensor()
{
  //get temperature and humidity
  sensors_event_t event;
      
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
    
    //lcd.setCursor(12, 0);
    //lcd.print("T");
    lcd.setCursor(13, 0);
    dht.temperature().getEvent(&event);
    int t = event.temperature;
    lcd.print(t);
    if (t<10) //prevent garbage for single digit temperature
    {
      lcd.setCursor(13, 0);
      lcd.print("0");
      lcd.print(t);      
    }
    //lcd.setCursor(11, 0);
//  lcd.print(char(223));
  lcd.setCursor(15, 0);
//  lcd.print("C");
    lcd.write((byte)0);
          
    //lcd.setCursor(12, 1);
    //lcd.print("U");
    lcd.setCursor(13, 1);
    dht.humidity().getEvent(&event);
    int h = event.relative_humidity;
    lcd.print(h);
      if (h<10) //prevent garbage for single digit temperature
    {
      lcd.setCursor(13, 1);
      lcd.print(" ");      
    }
    lcd.setCursor(15, 1);
    lcd.print("%");   
    delay(50);
    
}

//ISR to Start/Stop the clock
void buttons()
{
    if((long)(micros() - last_micros) >= debouncing_time * 1000) 
    {
    Interrupt();
    last_micros = micros();
    }
}
  
void Interrupt()
{
  lcd.clear();
  startstop = !startstop;
  }

void Clock()
{
    DateTime time = rtc.now();

    minute = time.minute(); 
    hour = time.hour();
   
    if (time.hour() != hour_bip)
    if (analogRead(A1) > valor_luz)
    {
     tone(14,1000,200);
     //noTone(14);
    }
       
    lcd.setCursor(0, 0);
//  lcd.print("Clock ");
    if (time.hour() < 10)
    {
      lcd.print("0");
      lcd.print(time.hour());
    }
    else
    {
      lcd.print(time.hour());
    }
    if ((time.second()%2) == 0)
      {
      //lcd.print(":");
      lcd.write((byte)2);
      }
     else 
        {
        //lcd.print(" ");
        lcd.write((byte)3);
        }
      
    
    if (time.minute() < 10)
    {
      lcd.print("0");
      lcd.print(time.minute());
    }
    else
    {
      lcd.print(time.minute());
    } 
    if ((time.second()%2) == 0)
      {
      //lcd.print(":");
      lcd.write((byte)2);
      }
      else 
        {
        //lcd.print(" ");
        lcd.write((byte)3);
        }
    if (time.second() < 10)
    {
      lcd.print("0");
      lcd.print(time.second());
    }
    else
    {
      lcd.print(time.second());
    }
    lcd.print(" ");

    hour_bip=time.hour();
  }

void Date()
{
    DateTime date = rtc.now();
    
    day = date.day(); 
    month = date.month();
    
    lcd.setCursor(0, 1);
//  lcd.print("Clock ");
    if (date.day() < 10)
    {
      lcd.print("0");
      lcd.print(date.day());
    }
    else
    {
      lcd.print(date.day());
    }
    lcd.print("/");
    if (date.month() < 10)
    {
      lcd.print("0");
      lcd.print(date.month());
    }
    else
    {
      lcd.print(date.month());

    } lcd.print("/");
    if (date.year() < 10)
    {
      lcd.print("0");
      lcd.print(date.year()-2000);
    }
    else
    {
      lcd.print(date.year()-2000);
    }
    lcd.print(" ");
}


void Alarme()
{
    lcd.setCursor(9, 0);
    lcd.write((byte)1);
    lcd.print("   ");
  }
   


void loop() 
{

  //Setting the time will stop the clock to set the time
  while (startstop == false)
  {
    lcd.setCursor(0, 1);
    lcd.print("-Clock set MODE- ");
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
    if(hour<10)
    {
    lcd.print("0");
    lcd.print(hour);
    }
    else
    lcd.print(hour);
    lcd.print(":");
    if(minute<10)
    {
    lcd.print("0");
    lcd.print(minute);
    }
    else
    lcd.print(minute);
    lcd.print(":");
    if(second<10)
    {
    lcd.print("0");  
    lcd.print(second);
    }
    else
    lcd.print(second);
    lcd.print(" ");
    
    if (digitalRead(1) == LOW)
    {
      hour++;
      if (hour > 23)
        hour = 0;
    }
    if (digitalRead(3) == LOW)
    {
      minute++;
      if (minute > 59)
        minute = 0;
    }


 /*
    lcd.setCursor(0, 1);
    lcd.print("-Cal.  set MODE- ");
    delay(100);
    lcd.setCursor(0, 0);
    lcd.print("Date: ");
    if(day<10)
    {
    lcd.print("0");
    lcd.print(day);
    }
    else
    lcd.print(day);
    lcd.print("/");
    if(month<10)
    {
    lcd.print("0");
    lcd.print(month);
    }
    else
    lcd.print(month);
    lcd.print("/");
    if(year<10)
    {
    lcd.print("0");
    lcd.print(year-2000);
    }
    else
    lcd.print(year-2000);
    lcd.print(" ");

    if (digitalRead(1) == LOW)
    {
      day++;
      if (day > 31)
        day = 1;
    }
    if (digitalRead(3) == LOW)
    {
      month++;
      if (month > 12)
        month = 1;
        year++;
        if (year > 2029)
        year = 2020;
    }
 
  */   

 
    //rtc.adjust(DateTime(year, month, day, hour, 59, 55));  // Testes de bip de minuto em minuto
    //rtc.adjust(DateTime(year, month, day, hour, minute, second ));  
    rtc.adjust(DateTime(2021, 02, 23, 10, 59, 55 ));  
  }

  if((long)(millis() - last_micros_clock) >= 1000) 
  {
    
    last_micros_clock = millis();
    Clock();
    Date();
    printSensor();  
    controlBacklight(); 
    Alarme();
  }  
}
