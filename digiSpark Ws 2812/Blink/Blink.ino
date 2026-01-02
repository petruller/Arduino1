// Пин для ленты WS2812
#define LED_PIN 3
#define NUM_LEDS 25

// Быстрая функция отправки бита
void sendBit(bool bitVal) {
  if (bitVal) {
    // Отправка "1"
    PORTB |= (1 << LED_PIN);   // HIGH
    asm volatile("nop\nnop\nnop\nnop"); // 4 такта
    PORTB &= ~(1 << LED_PIN);  // LOW
    asm volatile("nop\nnop");  // 2 такта
  } else {
    // Отправка "0"
    PORTB |= (1 << LED_PIN);   // HIGH
    asm volatile("nop");       // 1 такт
    PORTB &= ~(1 << LED_PIN);  // LOW
    asm volatile("nop\nnop\nnop\nnop\nnop\nnop"); // 6 тактов
  }
}

// Отправка байта
void sendByte(unsigned char byte) {
  for (int i = 0; i < 8; i++) {
    sendBit(byte & 0x80);
    byte <<= 1;
  }
}

// Преобразование HSV в RGB (0-255)
void getRainbowColor(int hue, unsigned char &r, unsigned char &g, unsigned char &b) {
  if (hue < 85) {
    r = 255 - hue * 3;
    g = hue * 3;
    b = 0;
  } else if (hue < 170) {
    hue -= 85;
    r = 0;
    g = 255 - hue * 3;
    b = hue * 3;
  } else {
    hue -= 170;
    r = hue * 3;
    g = 0;
    b = 255 - hue * 3;
  }
}

// Обновить всю ленту
void updateStrip() {
  delayMicroseconds(50); // Сброс ленты
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  // ===== РЕЖИМ 1: ПООЧЕРЕДНОЕ ЗАЖИГАНИЕ РАДУГОЙ =====
  for (int hue = 0; hue < 256; hue += 5) { // Плавный переход цветов
    for (int led = 0; led < NUM_LEDS; led++) {
      // Текущий светодиод получает текущий цвет
      unsigned char r, g, b;
      getRainbowColor((hue + led * 10) % 256, r, g, b);
      
      // Включаем ВСЕ светодиоды до текущего
      for (int i = 0; i <= led; i++) {
        unsigned char ri, gi, bi;
        getRainbowColor((hue + i * 10) % 256, ri, gi, bi);
        sendByte(gi);
        sendByte(ri);
        sendByte(bi);
      }
      
      // Остальные выключены
      for (int i = led + 1; i < NUM_LEDS; i++) {
        sendByte(0);
        sendByte(0);
        sendByte(0);
      }
      updateStrip();
      delay(50); // Задержка между светодиодами
    }
  }
  
  // ===== РЕЖИМ 2: БЕГУЩИЙ ОГОНЬ =====
  for (int i = 0; i < NUM_LEDS + 10; i++) {
    for (int pos = 0; pos < NUM_LEDS; pos++) {
      unsigned char r, g, b;
      
      // Определяем цвет для каждой позиции
      int huePos = (pos * 20) % 256;
      getRainbowColor(huePos, r, g, b);
      
      // Если светодиод в "хвосте" бегущего огня
      if (pos >= i - 10 && pos <= i) {
        // Плавное затухание к хвосту
        int brightness = 255 - (i - pos) * 25;
        if (brightness < 0) brightness = 0;
        
        sendByte(g * brightness / 255);
        sendByte(r * brightness / 255);
        sendByte(b * brightness / 255);
      } else {
        sendByte(0);
        sendByte(0);
        sendByte(0);
      }
    }
    updateStrip();
    delay(80);
  }
  
  // ===== РЕЖИМ 3: ЗАПОЛНЕНИЕ И ОЧИСТКА =====
  // Заполнение радугой
  for (int led = 0; led < NUM_LEDS; led++) {
    for (int pos = 0; pos < NUM_LEDS; pos++) {
      if (pos <= led) {
        unsigned char r, g, b;
        getRainbowColor((pos * 10) % 256, r, g, b);
        sendByte(g);
        sendByte(r);
        sendByte(b);
      } else {
        sendByte(0);
        sendByte(0);
        sendByte(0);
      }
    }
    updateStrip();
    delay(80);
  }
  
  // Очистка в обратном порядке
  for (int led = NUM_LEDS - 1; led >= 0; led--) {
    for (int pos = 0; pos < NUM_LEDS; pos++) {
      if (pos <= led) {
        unsigned char r, g, b;
        getRainbowColor((pos * 10) % 256, r, g, b);
        sendByte(g);
        sendByte(r);
        sendByte(b);
      } else {
        sendByte(0);
        sendByte(0);
        sendByte(0);
      }
    }
    updateStrip();
    delay(80);
  }
}