#include <Servo.h> //используем библиотеку для работы с сервоприводом

int inByte=180;
Servo servo;

void setup() {
  // put your setup code here, to run once:
  
servo.attach(6);

  Serial.begin(9600);
  
  servo.write(180);
}

void loop() {
  // put your main code here, to run repeatedly:
  servo.write(180); //ставим вал под 0

delay(2000); //ждем 2 секунды

servo.write(140); //ставим вал под 180

delay(2000); //ждем 2 секунды
}
