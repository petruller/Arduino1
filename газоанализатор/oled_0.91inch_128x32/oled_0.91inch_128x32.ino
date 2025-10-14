#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
const int AOUTpin=0;//the AOUT pin of the methane sensor goes into analog pin A0 of the arduino
const int DOUTpin=8;//the DOUT pin of the methane sensor goes into digital pin D8 of the arduino
const int ledPin=13;//the anode of the LED connects to digital pin D13 of the arduino

int limit;
int value;
int val;
String myval;
 void setup(void) {
   Serial.begin(9600);
   u8g2.begin();
   pinMode(DOUTpin, INPUT);//sets the pin as an input to the arduino
pinMode(ledPin, OUTPUT);//sets the pin as an output of the arduino
}

  void loop(void) {

value= analogRead(AOUTpin);//reads the analaog value from the methane sensor's AOUT pin
limit= digitalRead(DOUTpin);//reads the digital value from the methane sensor's DOUT pin
char buf[9];
  val = map(value, 0, 1023, 0, 100);
  String myval = String(val);
Serial.print("Methane value: ");
Serial.print(myval);
Serial.print(" ");
Serial.print(limit);
Serial.print(" ");
Serial.println(value);
    
   u8g2.clearBuffer();					// clear the internal memory
   u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
   sprintf (buf, "%d", val);
   u8g2.drawStr(8,29,buf);	// write something to the internal memory
   u8g2.sendBuffer();					// transfer internal memory to the display
   delay(500);


   
}

