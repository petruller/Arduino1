/*
  Меняем значение переменной при помощи энкодера
  Обычный поворот +-1
  "Нажатый" поворот +-5
*/

#include <EncButton.h>
EncButton enc(2, 3, 4);  // выводы энкодера на 2 и 3, кнопка на 4

void setup() {
  Serial.begin(115200);
}

int val = 0;  // будем управлять этой переменной

void loop() {
  // опрос энкодера происходит тут
  enc.tick();

  // вправо
  if (enc.right()) {
    val -= 1;
    Serial.println(val);
  }

  // влево
  if (enc.left()) {
    val += 1;
    Serial.println(val);
  }

  // вправо нажатый
  if (enc.rightH()) {
    val -= 5;
    Serial.println(val);
  }

  // влево нажатый
  if (enc.leftH()) {
    val += 5;
    Serial.println(val);
  }
}