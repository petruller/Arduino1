#define CLK 7
#define DT 8
#define SW 2
#include "GyverEncoder.h"
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
//Encoder enc1(CLK, DT);      // для работы без кнопки
Encoder enc1(CLK, DT, SW);  // для работы c кнопкой
//Encoder enc1(CLK, DT, SW, TYPE2);  // для работы c кнопкой и сразу выбираем тип
//Encoder enc1(CLK, DT, ENC_NO_BUTTON, TYPE2);  // для работы без кнопки и сразу выбираем тип

int value = 0;
String myStr; 
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
int I;
char s[9];

void setup() {
  Serial.begin(9600);
  u8g2.begin();
  enc1.setType(TYPE1);  // тип энкодера TYPE1 одношаговый, TYPE2 двухшаговый. Если ваш энкодер работает странно, смените тип
}

void loop() {
	// обязательная функция отработки. Должна постоянно опрашиваться
  enc1.tick();

  if (enc1.isRight()) value++;     	// если был поворот направо, увеличиваем на 1
  if (enc1.isLeft()) value--;	    // если был поворот налево, уменьшаем на 1
  
  if (enc1.isRightH()) value += 5; 	// если было удержание + поворот направо, увеличиваем на 5
  if (enc1.isLeftH()) value -= 5;	// если было удержание + поворот налево, уменьшаем на 5  

  if (enc1.isTurn()) {       // если был совершён поворот (индикатор поворота в любую сторону)
    Serial.println(value);  // выводим значение при повороте
       
   
  }
   tone(3, value*40); 
    sprintf (s, "%d", value*40);
   u8g2.clearBuffer();          // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29,s);  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display
}
