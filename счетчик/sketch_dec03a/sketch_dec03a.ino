
 
int latchPin = 8;    
//Пин "защелки" первого регистра подключен к ST_CP входу первого регистра отвечающего за сегменты 
int clockPin = 12;    //Пин подключен к SH_CP входу 74HC595
int dataPin = 11;     //Пин подключен к DS входу 74HC595------------------------------------------------------------+
int coutpin =5;
#include <Wire.h>
int number, disp;
int TimeLight = 5;  //время для разогрева сегментов
unsigned long millis1=0;
byte SegDisplay; // переменная для вывода символов на индикаторе
byte RazrDisplay; // переменная для включения разрядов

// Настройка комбинации для отображения каждого номера на дисплее.

byte g_digits[11]={
B00111111, B00000110,    // 0 1
B01011011, B01001111,    // 2 3
B01100110, B01101101,    // 4 5
B01111101, B00000111,    // 6 7
B01111111, B01101111,    // 8 9
B00000000, };       // все сегменты выключены

byte g_registerArray[4]={~8,~4,~2,~1}; //массив цифр, указывающий разряды
boolean buttonWasUp = true;
void setup() {
  Wire.begin();
  
// обозначаем все пины как выходы
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
 /* if(millis()-millis1>=1000)
{millis1=millis1+1000;
  
 number=number+1; 


  
if(number==10000)
number=0;
}*/

if (buttonWasUp && !digitalRead(coutpin)) {
    delay(10);
    if (!digitalRead(coutpin))
    number=number+1; 
  }
 buttonWasUp  = digitalRead(coutpin);
  disp = number; //"Собираем" значения часов и минут в одну цифру
 
 // Разбиваем цифру по разрядам индикатора
for( int i = 0; i < 4; i++ )
{
   if( i == 0 || disp != 0 )
      Indicate( i, disp % 10 );
   else
      Indicate( i, 10 );

   disp /= 10;
}

 }

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
