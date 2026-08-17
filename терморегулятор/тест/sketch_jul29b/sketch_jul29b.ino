// Пин для подключения датчика
const int tempPin = A0;

void setup() {
  // Инициализация последовательного порта
  Serial.begin(9600);
}

void loop() {
  // Считываем «сырое» значение с аналогового входа (0–1023)
  int reading = analogRead(tempPin);
  
  // Рассчитываем температуру в градусах Цельсия
  // Формула: температура (°C) = (значение * 5 В / 1023) * 1000 / 10
  float temperatureC = reading ;
  
  // Выводим результат
  Serial.print("Температура: ");
  Serial.print(temperatureC);
  Serial.println(" °C");
  

  
  delay(1000); // Задержка 1 секунда
}
