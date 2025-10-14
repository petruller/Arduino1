
#include <LCD_1602_RUS.h>
//#include <Adafruit_Sensor.h>

#include "DHT.h"

#define DHTPIN 10 // номер пина, к которому подсоединен датчик

LCD_1602_RUS lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHT11);
int cout;
#define FIRST_SEGMENT_PIN   2
#define SEGMENT_COUNT       8
int V= 0; //вольтметр
// Всего цифр 10, поэтому в массиве 10 чисел.
  int dat;
  float V220;
  char s;
byte numberSegments[10] = {
  0b01110111, 
  0b00010100, 
  0b10110011, 
  0b10110110, 
  0b11010100, 
  0b11100110, 
  0b11100111, 
  0b00110100, 
  0b11110111,
  0b11110110,
};
byte my[6] = {
  0b01000000, 
  0b00100000, 
  0b00010000, 
  0b00000100, 
  0b00000010, 
  0b00000001,
 };

void term()
{
 //delay(2000);

 //  digitalWrite(5,HIGH);
//delay(100); //ждем 500 Мс
//Считываем влажность

int h = dht.readHumidity();

// Считываем температуру

int t = dht.readTemperature();

// Проверка удачно прошло ли считывание.

if (isnan(h) || isnan(t)) {

 lcd.setCursor(0,0);  
  lcd.print("Error");

return;

}
lcd.clear();
lcd.setCursor(0,0);
lcd.print(L"Влаж:");
lcd.print(h);
lcd.print("%");
// Выводим на экран количество секунд с момента запуска ардуины
int time=millis()/1000;
if (time/60/60<10) { lcd.print ("0"); }
lcd.print (time/60/60);
lcd.print (":");
if (time/60%60<10) { lcd.print ("0"); }
lcd.print ((time/60)%60);
lcd.print (":");
if (time%60<10) {lcd.print ("0"); }
lcd.println (time%60);
 lcd.setCursor(0,1);  
lcd.print(L"Темп:");
lcd.print(t);
lcd.print("*C ");

 //вольтметр
  
  dat=analogRead(V);
   V220=dat/2.84;
 lcd.print(float(V220),0);
    lcd.print(" B");
  }

 void setup()
{
  
  Serial.begin(9600);
  
   lcd.init();             
 dht.begin();        
  lcd.backlight();// Включаем подсветку дисплея
  
    for (int i = 0; i < SEGMENT_COUNT; ++i)
     pinMode(i + FIRST_SEGMENT_PIN, OUTPUT);
  /* 
   //digitalWrite(i + FIRST_SEGMENT_PIN, enableSegment);
    int mask = numberSegments[2];
  // для каждого из 7 сегментов индикатора
  for (int i = 0; i < SEGMENT_COUNT; ++i) {
    // определяем: должен ли он быть включён.
    boolean enableSegment = bitRead(mask, i);
    // включаем/выключаем сегмент на основе полученного значения
    digitalWrite(i + FIRST_SEGMENT_PIN, enableSegment);
  }  //*/
 
// myServo.attach (10);
/* lcd.init();             
       
  lcd.backlight();

 lcd.setCursor(0,0);  
  lcd.print("Ларчи и компания");*/


}







void loop()
{//вольтметр
  /*
  dat=analogRead(V);
   V220=dat/2.845;
  Serial.print(float(V220),0);
//Serial.print(V220);
Serial.print(" ");
Serial.println(dat);
 delay(2000);
*/
term();
       // для каждого из 7 сегментов индикатора
  for (int a = 0; a < 6; ++a) {
     delay(100);
// определяем число, которое следует отобразить.
  //  Пусть им будет номер текущей секунды, зацикленный на десятке
 // int number = (millis() / 1000) % 10;
  // получаем код из массива, в котором содержится полученная цифра
  int mask = my[a];
  // для каждого из 7 сегментов индикатора
  for (int i = 0; i < SEGMENT_COUNT; ++i) {
    // определяем: должен ли он быть включён.
    boolean enableSegment = bitRead(mask, i);
    // включаем/выключаем сегмент на основе полученного значения
    digitalWrite(i + FIRST_SEGMENT_PIN, enableSegment);
  }
  }//*/
 
}
