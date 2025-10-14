
#include <MFRC522.h>
// константы подключения контактов SS и RST
#define RST_PIN 9
#define SS_PIN 10
//SDA
boolean kn=false;
// Инициализация MFRC522
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522 instance.
//kn = false;
void setup()
{
  pinMode(2,INPUT);
   pinMode(3,OUTPUT);
Serial.begin(9600); // инициализация последовательного порта
SPI.begin(); // инициализация SPI
mfrc522.PCD_Init(); // инициализация MFRC522
}
//#include <EEPROM.h> // Подключаем библиотеку для записи в энергонезависимую память "Card UID" / уникальный номер NFC карты.
//#include <SPI.h>
//#include <Wire.h> // Подключаем библиотеку для шины I2C / для работы дисплея.

// ---------------------------------
// Скачать библиотеки для дисплея. https://yadi.sk/d/9F_uW1wIZUDna
//#include <Adafruit_GFX.h> // Скачанная библиотека для дисплея.
//#include <Adafruit_SSD1306.h> // Скачанная библиотека для дисплея.
// ---------------------------------

// Библиотека "RFID", для RC522 Card Read. Скачать http://yadi.sk/d/6XLMLCuxSjdGa
#include <MFRC522.h> // скачанная библиотека "RFID" для RC522 Card Read Module.
// ****************************************

void loop() {
  if(digitalRead(2)==HIGH && kn==false)
    {
       digitalWrite(3, HIGH);
       kn=true;
    }
    else if (digitalRead(2)==HIGH && kn==true)
    {
      digitalWrite(3, LOW);
       kn=false;
      }
    // Look for new cards
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }
   Serial.println("New card");
    // Select one of the cards
    if ( ! mfrc522.PICC_ReadCardSerial()) {
        return;
    }

    // Dump debug info about the card; PICC_HaltA() is automatically called
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}
