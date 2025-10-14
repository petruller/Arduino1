#include <Adafruit_Sensor.h>

#include "DHT.h"

#define DHTPIN 2 // номер пина, к которому подсоединен датчик

// Раскомментируйте в соответствии с используемым датчиком

// Инициируем датчик

//DHT dht(DHTPIN, DHT22);

DHT dht(DHTPIN, DHT11);

void setup() {

Serial.begin(9600);

dht.begin();

}

void loop() {

// Задержка 2 секунды между измерениями

delay(2000);

//Считываем влажность

int h = dht.readHumidity();

// Считываем температуру

int t = dht.readTemperature();

// Проверка удачно прошло ли считывание.

if (isnan(h) || isnan(t)) {

Serial.println("Не удается считать показания");

return;

}
Serial.print(" Hum: ");
Serial.print(h);
Serial.print(" %\t");
Serial.print("Temp: ");
Serial.print(t);
Serial.println(" *C");
//Serial.println(«Humidity : «+String(h, 1)+»%\t Temperature : «+String(t, 1)+» *C»);
//Serial.println(«Влажность: «+h+» %\t»+»Температура: «+t+» *C «);
//Serial.print((String)»Влажность: «+h+» %\t»+»Температура: «+t+» *C «);
//Serial.print("Влажность: "+h+" %\t"+"Температура: "+t+" *C ");

}
