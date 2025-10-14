#include "DHT.h"

#define DHTPIN 2 // номер пина, к которому подсоединен датчик

// Раскомментируйте в соответствии с используемым датчиком

// Инициируем датчик

DHT dht(2, "DHT22");

//DHT dht(DHTPIN, DHT11);

void setup() {

Serial.begin(9600);

dht.begin();

}

void loop() {

// Задержка 2 секунды между измерениями

delay(2000);

//Считываем влажность

//float h = dht.readHumidity();

// Считываем температуру

float t = dht.readTemperature();

// Проверка удачно прошло ли считывание.

if (isnan(t)) {

Serial.println("Не удается считать показания");

return;

}

Serial.print("Температура: "+t+" *C ");

}

