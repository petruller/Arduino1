
#include <Adafruit_Sensor.h>

#include "DHT.h"

#define DHTPIN 2

#define TEMP_PIN  5
unsigned long timing, timing1, timing2, timingD, timingH;
void OneWireReset(int Pin);
void OneWireOutByte(int Pin, byte d);
byte OneWireInByte(int Pin);
 
int latchPin = 8;    
//Пин "защелки" первого регистра подключен к ST_CP входу первого регистра отвечающего за сегменты 
int clockPin = 12;    //Пин подключен к SH_CP входу 74HC595
int dataPin = 11;     //Пин подключен к DS входу 74HC595------------------------------------------------------------+
int coutpin =5;
#include <Wire.h>
int number, disp, tem, tem1,h,k=1;
int TimeLight = 5;  //время для разогрева сегментов
unsigned long millis1=0;
byte SegDisplay; // переменная для вывода символов на индикаторе
byte RazrDisplay; // переменная для включения разрядов

// Настройка комбинации для отображения каждого номера на дисплее.

byte g_digits[12]={
B00111111, B00000110,    // 0 1
B01011011, B01001111,    // 2 3
B01100110, B01101101,    // 4 5
B01111101, B00000111,    // 6 7
B01111111, B01101111,    // 8 9
B00000000, B01000000 };       // все сегменты выключены

byte g_registerArray[4]={~8,~4,~2,~1}; //массив цифр, указывающий разряды
boolean buttonWasUp = true;
boolean minus = false;

DHT dht(DHTPIN, DHT11);
void setup()
{
  dht.begin();
   Serial.begin(9600);
   Serial.print("temperature measurement setup in progress\n");

   pinMode(TEMP_PIN, INPUT);      // sets the digital pin as input (logic 1)
   digitalWrite(TEMP_PIN, LOW);
   delay(100);
   Wire.begin();
  
// обозначаем все пины как выходы
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop()
{

if (millis() - timing > 45000){ // Вместо 10000 подставьте нужное вам значение паузы 
  timing = millis(); 
  tem = temp();
 h = dht.readHumidity();

// Считываем температуру

tem1 = dht.readTemperature();

// Проверка удачно прошло ли считывание.

if (isnan(h) || isnan(tem1)) {

Serial.println("Не удается считать показания");

return;

}
Serial.print(tem1);
 Serial.print(" C\n");
 Serial.print(h);
 Serial.print(" H\n");
  
 }

 timing2 =millis() - timing1;
if (timing2  >0){ // Вместо 10000 подставьте нужное вам значение паузы 
    k=1;  
   disp = tem;
  
     } 
     
     if(timing2 >15000 )
     {
    k=2;
         disp = tem1;
   
      }
      
      if( timing2 > 30000 )
      {
        k=3 ;      
       disp = h;
    }
    
              if (timing2 > 45000){ // Вместо 10000 подставьте нужное вам значение паузы 
           timing1 = millis(); }
          
        
        

 if (minus==true && k==1) // If its negative
 {
    Indicate(2,11 );
 }else
 {
  
  Indicate(2,10 );
  }

 for( int i = 0; i < 4; i++ )
{
   if( i == 0 || disp != 0 )
      Indicate( i, disp % 10 );
   else   
      Indicate( i, 10 );
      
  disp /= 10;
    
} 
  Indicate(3,k);  
}


int temp (){
   int HighByte, LowByte, TReading, SignBit, Tc_100, Tf_100, Whole, Fract;
   
 OneWireReset(TEMP_PIN);       // reset
 OneWireOutByte(TEMP_PIN, 0xcc); // skip ROM code
 OneWireOutByte(TEMP_PIN, 0x44); // perform temperature conversion, strong pullup for one sec

 OneWireReset(TEMP_PIN);         // reset
 OneWireOutByte(TEMP_PIN, 0xcc); // skip ROM code
 OneWireOutByte(TEMP_PIN, 0xbe); // Read scratchpad code (temperature in this case)

 LowByte = OneWireInByte(TEMP_PIN);
 //Serial.print("Low byte = ");
 //Serial.print( LowByte );
 //Serial.println();
 
 HighByte = OneWireInByte(TEMP_PIN);
 //Serial.print("High byte = ");
 //Serial.print( HighByte );
 //Serial.println();

 TReading = (HighByte << 8) + LowByte;
 //Serial.print("Raw temp = ");
 //Serial.print( TReading );
 //Serial.println();

 SignBit = TReading & 0x8000;  // test most sig bit
 if (SignBit) // negative
 {
   TReading = (TReading ^ 0xffff) + 1; // 2's complement the answer
 }
 Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25

 Whole = Tc_100 / 100;  // separate off the whole and fractional portions
 Fract = Tc_100 % 100;

 if (SignBit) // If its negative
 {
    Serial.print("-");
    minus=true;
 }
 else
 {minus=false;
  }
 
 Serial.print(Whole);
 Serial.print(".");
 if (Fract < 10)
 {
    Serial.print("0");
 }
 Serial.print(Fract);
 Serial.print("C\n");
  return Whole; //"Собираем" значения часов и минут в одну цифру
     
}

/*
 Tf_100 = ((Tc_100 * 9) / 5) + 3200;
 Whole = Tf_100 / 100;  // separate off the whole and fractional portions
 Fract = Tf_100 % 100;

 
 if (SignBit) // If its negative
 {
    Serial.print("-");
 }
 
 Serial.print(Whole);
 Serial.print(".");
 if (Fract < 10)
 {
    Serial.print("0");
 }
 Serial.print(Fract);
 Serial.print("F\n");

 Serial.print("\n");

 //delay(5);    // 2 second delay.  Adjust as necessary


for( int i = 0; i < 2; i++ )
{
   if( i == 0 || disp != 0 )
      Indicate( i, disp % 10 );
   else
      Indicate( i, 10 );

   disp /= 10;
}disp = Whole;

*/


void Indicate(int r,int x)
{
SegDisplay=g_digits[x]; // получаем цифру и выводим символ, из массива цифр, соответствующий этой цифре.
RazrDisplay=g_registerArray[r];  // получаем цифру и выводим номер регистра, из массива цифр, соответствующий этой цифре.
  digitalWrite(latchPin, LOW);  // устанавливаем синхронизацию "защелки" на LOW
      shiftOut(dataPin, clockPin, MSBFIRST, RazrDisplay); // Записываем информацию для второго регистра (Номер разряда)
      shiftOut(dataPin, clockPin, MSBFIRST, SegDisplay);  // Записываем информацию для первого регистра (Номер символа)
  digitalWrite(latchPin, HIGH);  //"защелкиваем" регистр, тем самым устанавливая значения на выходах

   delay(TimeLight); // пауза, чтобы сегменты "разгорелись"
}

void OneWireReset(int Pin) // reset.  Should improve to act as a presence pulse
{
    digitalWrite(Pin, LOW);
    pinMode(Pin, OUTPUT); // bring low for 500 us
    delayMicroseconds(500);
    
    pinMode(Pin, INPUT);
    delayMicroseconds(500);
}

void OneWireOutByte(int Pin, byte d) // output byte d (least sig bit first).
{
  byte n;

  for(n = 8; n != 0; n--)
  {
     if ((d & 0x01) == 1)  // test least sig bit
     {  // if it is "1", pull low for just 5uS
        //digitalWrite(Pin, LOW);
        pinMode(Pin, OUTPUT);
        delayMicroseconds(5);
        
        // then wait (external resistor pulls line back high)
        pinMode(Pin, INPUT);
        delayMicroseconds(60);
     }
     else
     {  //lsb is "0", so pull low for 60uS
        //digitalWrite(Pin, LOW);
        pinMode(Pin, OUTPUT);
        delayMicroseconds(60);
        
        // release, allowing external resistor to pull high
        pinMode(Pin, INPUT);
     }

     d = d >> 1; // now the next bit is in the least sig bit position.
  }
  
}

byte OneWireInByte(int Pin) // read byte, least sig byte first
{
   byte d, n, b;

   for ( n = 0; n < 8; n++ )
   {
       // digitalWrite(Pin, LOW);
       // pull pin low for 5uS
       pinMode(Pin, OUTPUT);
       delayMicroseconds(5);
       
       // release pin, allowing external resistor to pull line back high for 5uS
       pinMode(Pin, INPUT);
       delayMicroseconds(5);
       
       // DS18B20 either pulls line low, or leaves it high
       // find out which...
       b = digitalRead(Pin);
       
       // wait bit time
       delayMicroseconds(50);
       
       // assemble our collected bits
       d = (d >> 1) | (b << 7); // shift d to right and insert b in most sig bit position
   }
   return(d);
}
