// Установка выводов
const int dirPin = 2;
const int stepPin = 5;
const int stepsPerRevolution = 200;

void setup()
{
  // Объявить контакты как выходы
  pinMode(stepPin, OUTPUT);
  pinMode(dirPin, OUTPUT);
}
void loop()
{
  // Установка направления вращения двигателя по часовой стрелке.
  digitalWrite(dirPin, HIGH);

  // Медленное вращение двигателя
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(4000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(4000);
  }
 /* delay(1000); // Ждем секунду
  
  // Установка направления вращения двигателя против часовой стрелке.
  digitalWrite(dirPin, LOW);

  // Быстрое вращение двигателя
  for(int x = 0; x < stepsPerRevolution; x++)
  {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(1000);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(1000);
  }
  delay(1000); // Ждем секунду*/
}