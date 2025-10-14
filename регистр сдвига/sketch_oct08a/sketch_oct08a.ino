//**************************************************************//
//  Name    : shiftOutCode, Hello World                                
//  Author  : Carlyn Maw,Tom Igoe, David A. Mellis 
//  Date    : 25 Oct, 2006    
//  Modified: 21 Mar 2010  
//  Modified: 19 Feb 2011                               
//  Version : 2.0                                             
//  Notes   : Программа использует два сдвиговых регистра 74HC595 
//          : для вывода значений от 0 до 255                          
//****************************************************************

//Пин подключен к ST_CP входу 74HC595
int latchPin = 8; //latch
//Пин подключен к SH_CP входу 74HC595
int clockPin = 12;//SRCLC clock
//Пин подключен к DS входу 74HC595
int dataPin = 11; //RCLK 

int seq[3] = {2,4,8};     //int B1[] = {0x00001000, 0x00000010,0x0000100};

void setup() {
  //устанавливаем режим OUTPUT
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  //-------------------

  /*
      digitalWrite(latchPin, LOW);
       shiftOut(dataPin, clockPin, MSBFIRST, B00111100);  //B00110001
      digitalWrite(latchPin, HIGH);  */
}

void loop() {

for(int i=0; i<3; i++)
{
    digitalWrite(latchPin, LOW);
       shiftOut(dataPin, clockPin, MSBFIRST,seq[i]);  
      digitalWrite(latchPin, HIGH);
       delay(1000);
}
 
}
