#include <Adafruit_NeoPixel.h>

// Константы - используем define для экономии памяти
#define LED_PIN     3
#define NUM_LEDS    10    // Уменьшите если лента большая
#define BRIGHTNESS  30    // Уменьшите яркость

// Глобальные переменные - только необходимые
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

byte currentLed = 0;
byte currentMode = 0;
bool stripState = false;

unsigned long previousBlinkMillis = 0;
unsigned long previousModeMillis = 0;
unsigned long previousStripBlinkMillis = 0;

const uint16_t blinkInterval = 100;
const uint16_t modeInterval = 10000;
const uint16_t stripBlinkInterval = 500;

void setup() {
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show();  // Очистка ленты
}

void loop() {
  unsigned long currentMillis = millis();
  
  // Смена режима каждые 10 секунд
  if (currentMillis - previousModeMillis >= modeInterval) {
    previousModeMillis = currentMillis;
    currentMode = (currentMode + 1) % 6;
    clearStrip();
    currentLed = 0;
    stripState = false;
  }
  
  // Обработка режимов 0-2 (поочередное мигание)
  if (currentMode < 3) {
    if (currentMillis - previousBlinkMillis >= blinkInterval) {
      previousBlinkMillis = currentMillis;
      
      // Выключаем текущий светодиод
      strip.setPixelColor(currentLed, 0, 0, 0);
      
      // Переходим к следующему
      currentLed++;
      if (currentLed >= NUM_LEDS) currentLed = 0;
      
      // Включаем новый светодиод
      setColorByMode(currentLed, currentMode);
      
      strip.show();
    }
  }
  // Обработка режимов 3-5 (вся лента мигает)
  else {
    if (currentMillis - previousStripBlinkMillis >= stripBlinkInterval) {
      previousStripBlinkMillis = currentMillis;
      stripState = !stripState;
      
      if (stripState) {
        // Включаем всю ленту
        for (byte i = 0; i < NUM_LEDS; i++) {
          setColorByMode(i, currentMode);
        }
      } else {
        // Выключаем всю ленту
        clearStrip();
      }
      strip.show();
    }
  }
}

// Функция установки цвета в зависимости от режима
void setColorByMode(byte ledIndex, byte mode) {
  switch(mode) {
    case 0: // Синий поочередно
    case 3: // Вся лента синим
      strip.setPixelColor(ledIndex, 0, 0, 255);
      break;
    case 1: // Зеленый поочередно
    case 4: // Вся лента зеленым
      strip.setPixelColor(ledIndex, 0, 255, 0);
      break;
    case 2: // Красный поочередно
    case 5: // Вся лента красным
      strip.setPixelColor(ledIndex, 255, 0, 0);
      break;
  }
}

// Очистка ленты
void clearStrip() {
  for (byte i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, 0, 0, 0);
  }
}