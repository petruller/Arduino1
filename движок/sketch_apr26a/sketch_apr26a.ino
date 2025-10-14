#include <Servo.h>

#include <IRremote.h>
#include <IRremoteInt.h>


Servo servo;

IRrecv irrecv(3); // указываем вывод, к которому подключен приемник

decode_results results;

long IR2 = "FF18E7";//код пульта для кнопки 2 — ВПЕРЕД

//LiquidCrystal_I2C lcd(0x27,16,2);  // Устанавливаем дисплей
void setup()
{

    irrecv.enableIRIn(); // Запускаем прием*

servo.attach(10); 

pinMode(8, OUTPUT);

/*pinMode(g, OUTPUT);

pinMode(b, OUTPUT);*/
const int irReceiverPin = 3; // Инфокрасный датчик (D12)

}




void loop()
{

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
    int res = results.value;
  }

   if(digitalRead(4)==HIGH)
      {
    //  digitalWrite(4,HIGH);
     //RGB 
  digitalWrite(5,LOW);
/*digitalWrite(r, HIGH); //включаем красный

delay(800); //ждем 500 Мс

digitalWrite(r, LOW); //выключаем красный

digitalWrite(g, HIGH); //включаем зеленый

delay(800); //ждем 500 Мс

digitalWrite(g, LOW); //выключаем зеленый

digitalWrite(b, HIGH); //включаем синий

delay(800); //ждем 500 Мс

digitalWrite(b, LOW); //выключаем синий*/
//RGBend
      }




      
servo.write(0); //ставим вал под 0
 digitalWrite(8,HIGH);
delay(2000); //ждем 2 секунды

servo.write(180); //ставим вал под 180
 digitalWrite(8,LOW);
delay(2000); //ждем 2 секунды
 
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
