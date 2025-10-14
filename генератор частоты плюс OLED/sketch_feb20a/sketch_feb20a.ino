
/*I had some confusion initially but later found out 
that SDA and SCL on Arduino Nano are available on A4 and A5 pins.

SDA -> A4
SCL -> A5*/
#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
String myStr; 
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
int I;
char s[9];
 void setup(void) {
   u8g2.begin();
}

  void loop(void) {
  // s="Hello!!!";
   //sprintf (s, "%d", I);
  //tone(7, I); 
   u8g2.clearBuffer();          // clear the internal memory
   u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   u8g2.drawStr(8,29," Hello");  // write something to the internal memory
   u8g2.sendBuffer();         // transfer internal memory to the display

   
}
