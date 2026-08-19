#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <GyverDS18.h>

// ========== НАСТРОЙКИ ==========
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_ADDR 0x3C

#define ENC_CLK 2
#define ENC_DT  3
#define ENC_SW  4
#define RELAY_PIN 5

#define T_ON_DEFAULT 50.0     // Температура включения по умолчанию
#define T_OFF_DEFAULT 62.0    // Температура выключения по умолчанию
#define T_MIN 10.0            // Минимальная температура
#define T_MAX 150.0           // Максимальная температура

// ========== ОБЪЕКТЫ ==========
GyverDS18Single ds(6);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// ========== ПЕРЕМЕННЫЕ ==========
volatile int encoderPos = 0;
volatile bool encoderTurned = false;
bool lastClkState;
bool buttonPressed = false;      // Кнопка зажата?
float T_on = T_ON_DEFAULT;       // Температура включения
float T_off = T_OFF_DEFAULT;     // Температура выключения
float currentTemp = 0.0;
bool relayState = false;
unsigned long lastDisplayUpdate = 0;
unsigned long lastTempRead = 0;
bool lastButtonState = HIGH;
unsigned long buttonPressTime = 0;

// ========== ОБРАБОТЧИК ЭНКОДЕРА ==========
void encoderISR() {
  bool clk = digitalRead(ENC_CLK);
  bool dt = digitalRead(ENC_DT);
  
  if (clk != lastClkState) {
    if (dt != clk) {
      encoderPos++;
    } else {
      encoderPos--;
    }
    encoderTurned = true;
    lastClkState = clk;
  }
}

// ========== ИНИЦИАЛИЗАЦИЯ ==========
void setup() {
  pinMode(ENC_CLK, INPUT_PULLUP);
  pinMode(ENC_DT, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  lastClkState = digitalRead(ENC_CLK);
  
  attachInterrupt(digitalPinToInterrupt(ENC_CLK), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(ENC_DT), encoderISR, CHANGE);
  
 
   ds.setResolution(12);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDR)) {
    while (true) {
      digitalWrite(LED_BUILTIN, HIGH);
      delay(200);
      digitalWrite(LED_BUILTIN, LOW);
      delay(200);
    }
  }
  
  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);
  display.display();
  
  // Заставка
  display.setTextSize(1);
  display.setCursor(20, 10);
  display.println("Thermostat");
  display.display();
  delay(1000);
  
  // Начальное состояние реле - ВКЛ (греем)
  relayState = true;
  digitalWrite(RELAY_PIN, HIGH);
}

// ========== ОБНОВЛЕНИЕ ПАРАМЕТРОВ ЭНКОДЕРОМ ==========
void updateParameters() {
  if (!encoderTurned) return;
  
  int steps = encoderPos;
  encoderPos = 0;
  encoderTurned = false;
  
  // Шаг изменения температуры (0.5°C)
  float delta = steps * 0.5;
  
  if (buttonPressed) {
    // ===== РЕЖИМ С ЗАЖАТОЙ КНОПКОЙ: меняем T_off =====
    T_off += delta;
    
    // Ограничения
    if (T_off > T_MAX) T_off = T_MAX;
    if (T_off < T_on + 1.0) T_off = T_on + 1.0;  // Не может быть ниже T_on
  } else {
    // ===== ОБЫЧНЫЙ РЕЖИМ: меняем T_on =====
    T_on += delta;
    
    // Ограничения
    if (T_on < T_MIN) T_on = T_MIN;
    if (T_on > T_off - 1.0) T_on = T_off - 1.0;  // Не может быть выше T_off
  }
}

// ========== ОБРАБОТКА КНОПКИ ЭНКОДЕРА ==========
void handleButton() {
  bool btnState = digitalRead(ENC_SW);
  
  // Кнопка НАЖАТА (LOW)
  if (btnState == LOW && lastButtonState == HIGH) {
    buttonPressTime = millis();
    buttonPressed = true;
  }
  
  // Кнопка ОТПУЩЕНА (HIGH)
  if (btnState == HIGH && lastButtonState == LOW) {
    buttonPressed = false;
    
    // Если кнопка была нажата коротко (менее 500 мс) без вращения
    // можно добавить какое-то действие (например, сброс к значениям по умолчанию)
    if (millis() - buttonPressTime < 500 && !encoderTurned) {
      // Двойное нажатие или короткое нажатие - сброс
      // Раскомментируйте строки ниже, если хотите сброс по нажатию
      // T_on = T_ON_DEFAULT;
      // T_off = T_OFF_DEFAULT;
    }
  }
  
  lastButtonState = btnState;
}

// ========== УПРАВЛЕНИЕ РЕЛЕ ==========
void controlRelay() {
  // Реле ВКЛЮЧАЕТСЯ при T_on и ВЫКЛЮЧАЕТСЯ при T_off
  if (currentTemp >= T_off && relayState) {
    relayState = false;
    digitalWrite(RELAY_PIN, LOW);
  } else if (currentTemp <= T_on && !relayState) {
    relayState = true;
    digitalWrite(RELAY_PIN, HIGH);
  }
}

// ========== ВЫВОД НА ДИСПЛЕЙ 128x32 ==========
void updateDisplay() { 
  display.clearDisplay();
  
  // ===== СТРОКА 1: Статус + текущая температура (крупно) =====
  display.setTextSize(2);  // Крупный шрифт
  display.setCursor(0, 0);
  
  // Статус реле (коротко)
  if (relayState) {
    display.print("ON |");   // H - Heat (нагрев)
  } else {
    display.print("OFF |");   // I - Idle (ожидание)
  }
  
  display.print(" ");
  display.print(currentTemp, 1);
  display.print("C");
  
  // ===== СТРОКА 2: T_on и T_off (крупно) =====
  display.setTextSize(1);  // Для параметров используем мелкий шрифт
  display.setCursor(0, 20);
  
  // T_on (температура включения)
  if (!buttonPressed) {
    display.print(">");   // Указатель, если активен режим T_on
  } else {
    display.print(" ");
  }
  display.print("On:");
  display.print(T_on, 1);
  
  // T_off (температура выключения)
  display.setCursor(64, 20);
  if (buttonPressed) {
    display.print(">");   // Указатель, если активен режим T_off
  } else {
    display.print(" ");
  }
  display.print("Off:");
  display.print(T_off, 1);
  
  display.display();
}

// ========== ГЛАВНЫЙ ЦИКЛ ==========
void loop() {
  // Чтение датчика (каждые 500 мс)
  if (millis() - lastTempRead > 500) {
   if (!ds.tick()) {
           currentTemp = ds.getTemp();
            }
    if (currentTemp == -127.0) currentTemp = 0.0;
    lastTempRead = millis();
  }
  
  // Обновление параметров
  updateParameters();
  handleButton();
  controlRelay();
  
  // Обновление дисплея (каждые 200 мс)
  if (millis() - lastDisplayUpdate > 200) {
    updateDisplay();
    lastDisplayUpdate = millis();
  }
  
  delay(10);
}