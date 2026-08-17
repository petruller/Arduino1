// асинхронный опрос одного датчика на пине
// простейший вариант - библиотека сама запрашивает температуру
// и сигналит по готовности, можно забрать результат

#include <GyverDS18.h>
GyverDS18Single ds(6);  // пин

void setup() {
    Serial.begin(115200);
    ds.setResolution(12);
}
void loop() {
    // тикер, вызывать в loop
    // по готовности и успешному чтению
    if (!ds.tick()) {
        Serial.println(ds.getTemp());
        Serial.println("Привет с датчиком");
    }else
     Serial.println("Привет без");
     delay(1000);
}