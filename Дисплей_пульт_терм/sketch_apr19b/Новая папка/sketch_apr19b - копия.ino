#include <Wire.h>

//include <LiquidCrystal_I2C.h>
#include <LCD_1602_RUS.h>
#include <Adafruit_Sensor.h>

#include "DHT.h"

#define DHTPIN 2 // номер пина, к которому подсоединен датчик
#define KNPIN 3

LCD_1602_RUS lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHT11);

bool knopka=false;



//LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей
void setup()
{
  pinMode(KNPIN,INPUT);

 lcd.init();             
 dht.begin();        
  lcd.backlight();// Включаем подсветку дисплея
  lcd.setCursor(0,0); /* 
  lcd.print("Hello word");
  lcd.setCursor(8, 1);
  lcd.print("1111!");*/

}

void term()
{
 delay(2000);

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
lcd.print(L"Влаж: ");
lcd.print(h);
lcd.print(" %");
 lcd.setCursor(0,1);  
lcd.print(L"Темп: ");
lcd.print(t);
lcd.print(" *C"); 
  
  }



void loop()
{
  term();
  //***************КНОПКА 1********************************//
/*
if(digitalRead(KNPIN)==LOW)//&&knopka==false)//если кнопка нажата и перемення "knopka" равна 0 , то ...

{
 delay(50);//защита от дребезга
lcd.print(L"Влаж: ");
// knopka=false;//пишем 1 в переменную кнопкаэто нужно для того что бы с каждым нажатием кнопки//происходило только одно действие

//GBCFNM
}else if(digitalRead(KNPIN)==HIGH)//&&knopka==true)//если кнопка НЕ нажата

{delay(100);
lcd.clear();
 lcd.setCursor(0,0);
lcd.print(L"За окошком");
lcd.setCursor(0,1);  
lcd.print(L"Апрель         ");  
  while(digitalRead(KNPIN)==HIGH)
  {delay(100);
lcd.clear();
 lcd.setCursor(0,0);
lcd.print(L"За окошком");
lcd.setCursor(0,1);  
lcd.print(L"Апрель         ");  
  }

//knopka=true;//обнуляем переменную "knopka"

}

//if(knopka==true)


  //******************************

  
  // Устанавливаем курсор на вторую строку и нулевой символ.
// lcd.setCursor(0, 1);
  // Выводим на экран количество секунд с момента запуска ардуины
// lcd.print(millis()/1000);*/
}
