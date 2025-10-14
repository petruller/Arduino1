#include <VarSpeedServo.h>



//#include <Servo.h>

#include <IRremote.h>
#include <IRremoteInt.h>



#include <Wire.h>

//include <LiquidCrystal_I2C.h>
#include <LCD_1602_RUS.h>
#include <Adafruit_Sensor.h>

#include "DHT.h"

#define DHTPIN 2 // номер пина, к которому подсоединен датчик
#define KNPIN 3

LCD_1602_RUS lcd(0x27, 16, 2);
DHT dht(DHTPIN, DHT11);
//Servo servo;
VarSpeedServo myServo;
bool knopka=false;
int r = 8;

int g = 7;

int b = 9;
IRrecv irrecv(3); // указываем вывод, к которому подключен приемник

decode_results results;

long IR2 = "FF18E7";//код пульта для кнопки 2 — ВПЕРЕД

//LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей
void setup()
{
  Serial.begin (9600); //Включаем серйиный порт — скрость 9600
    irrecv.enableIRIn(); // Запускаем прием
  pinMode(KNPIN,INPUT);
pinMode(4, OUTPUT);
pinMode(5, OUTPUT);
 lcd.init();             
 dht.begin();        
  lcd.backlight();// Включаем подсветку дисплея
 myServo.attach (10);
//servo.attach(10); 
pinMode(r, OUTPUT);

pinMode(g, OUTPUT);

pinMode(b, OUTPUT);
const int irReceiverPin = 3; // Инфокрасный датчик (D12)

}

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
lcd.print(L"Темп: ");
lcd.print(t);
lcd.print(" *C "); 
    
  }



void loop()
{    myServo.slowmove (180, 100);

  if (irrecv.decode(&results)) // Если данные пришли 
  {
   Serial.println(results.value, HEX); // Отправляем полученную данную в консоль
    irrecv.resume(); // Принимаем следующую команду
    
   // Serial.println(res, HEX);
    if(results.value==0x00FF30CF || results.value==0x4BB6E916)// Если нажата кнопка "1"
    {
      if(digitalRead(4)==LOW)
      {
      digitalWrite(4,HIGH);
          }else
      {
      digitalWrite(4,LOW);
      
      
     }
    }
     if(results.value==0x00FF18E7)// Если нажата кнопка "2"
    {
      if(digitalRead(5)==LOW)
      {
      digitalWrite(5,HIGH);
      }else
      digitalWrite(5,LOW);
    }
    
  /*   if(results.value==0x00FF02FD)// стрелка движок
    {
       //servo.write(120); 
      myServo.slowmove (0, 40);
      
         if(digitalRead(5)==LOW)
      {
      digitalWrite(5,HIGH);
      }else
      digitalWrite(5,LOW);
    }
    if(results.value==0x00FF22DD)// стрелка движок
    {
    myServo.slowmove (180, 40);
     //servo.write(180); 
          if(digitalRead(5)==LOW)
      {
      digitalWrite(5,HIGH);
      }else
      digitalWrite(5,LOW);
    }
    int res = results.value;*/
  }

   if(digitalRead(4)==HIGH)
      {
    //  digitalWrite(4,HIGH);
     //RGB 
  digitalWrite(5,LOW);
digitalWrite(r, HIGH); //включаем красный

delay(800); //ждем 500 Мс

digitalWrite(r, LOW); //выключаем красный

digitalWrite(g, HIGH); //включаем зеленый

delay(800); //ждем 500 Мс

digitalWrite(g, LOW); //выключаем зеленый

digitalWrite(b, HIGH); //включаем синий

delay(800); //ждем 500 Мс

digitalWrite(b, LOW); //выключаем синий
//RGBend
      }else


      {delay(5000);
        }
  term();
      myServo.slowmove (0, 100);
  //   
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
