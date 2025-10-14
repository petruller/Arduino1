#include <TimerOne.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 10          // Пин CS для SD-карты
#define RESOLUTION 30        // Разрешение таймера (мкс) был 40
#define BUFFER_SIZE 512      // Размер буфера чтения
#define FIRST_PIN 2          // Первый пин дисковода
#define PIN_MAX 7  
#define BUTTON_PIN 8

unsigned int trackBPM = 120; // Значение по умолчанию
unsigned long noteDuration;

 struct RingBuffer {
  byte data[BUFFER_SIZE];
  unsigned int head = 0;
  unsigned int tail = 0;
  unsigned int count = 0;
}; 


struct NoteCommand {
  byte pin;
  unsigned int period;
};
const char fileHeader[4] = {'F','L','P','1'}; // ← Добавьте эту строку
File musicFile;
//byte fileBuffer[BUFFER_SIZE];
unsigned int bufferPos = 0;
unsigned int bytesInBuffer = 0;
boolean firstRun = true;
int currentTrack=-1;

byte MAX_POSITION[] = {
  0,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0,158,0};
  
byte currentPosition[18] = {0};
int currentState[18] = {0};
unsigned int currentPeriod[18] = {0};
unsigned int currentTick[18] = {0};
  String trackList[] ={ "1.bin", "2.bin", "3.bin", "4.bin"};

RingBuffer fileBuffer;

void setup(){
  pinMode(13, OUTPUT);// Pin 13 has an LED connected on most Arduino boards
  pinMode(2, OUTPUT); // Step control 1
  pinMode(3, OUTPUT); // Direction 1
  pinMode(4, OUTPUT); // Step control 2
  pinMode(5, OUTPUT); // Direction 2
  pinMode(6, OUTPUT); // Step control 3
  pinMode(7, OUTPUT); // Direction 3
  pinMode(8, OUTPUT); // Step control 4
  pinMode(9, OUTPUT); // Direction 4
 // pinMode(10, OUTPUT); // Step control 5
  pinMode(11, OUTPUT); // Direction 5
  pinMode(12, OUTPUT); // Step control 6
  pinMode(13, OUTPUT); // Direction 6
  pinMode(14, OUTPUT); // Step control 7
  pinMode(15, OUTPUT); // Direction 7
  pinMode(16, OUTPUT); // Step control 8
  pinMode(17, OUTPUT); // Direction 8

 if (!SD.begin(SD_CS_PIN)) {
    digitalWrite(13, HIGH); // Ошибка - включаем LED
    return;
  }
  memset(&fileBuffer, 0, sizeof(fileBuffer));
  // Открываем файл с музыкой
  
  musicFile = SD.open("prod.bin", FILE_READ);
  if (!musicFile) {
    digitalWrite(13, HIGH); // Ошибка - включаем LED
    return;
  }

  if (musicFile.available() >= 6) {
    char header[4];
    musicFile.read(header, 4); // Пропускаем "FLP1"
    
    // Читаем BPM (2 байта)
    trackBPM = (musicFile.read() << 8) | musicFile.read();
    
    // Рассчитываем длительность четвертной ноты
    noteDuration = 60000 / trackBPM / 4; // Для четвертных нот
  }

  Timer1.initialize(RESOLUTION); // Set up a timer at the defined resolution
  Timer1.attachInterrupt(tick); // Attach the tick function

  Serial.begin(9600);
}


void loop(){

 if (firstRun) {
    firstRun = false;
    resetAll();
    delay(2000);
    fillBuffer(); // Первоначальное заполнение буфера
  }

play();
}

void play(){

   if (digitalRead(BUTTON_PIN) == HIGH) {
    musicFile.close();
      memset(&fileBuffer, 0, sizeof(fileBuffer));
    delay(500);
    currentTrack++;
    if(currentTrack <= 3){
      Serial.println(trackList[currentTrack]);
     musicFile = SD.open(trackList[currentTrack], FILE_READ);
  if (!musicFile) {
    digitalWrite(13, HIGH); // Ошибка - включаем LED
    return;
  }

  if (musicFile.available() >= 6) {
     Serial.println("проверил 6");
    char header[4];
    musicFile.read(header, 4); // Пропускаем "FLP1"
    
    // Читаем BPM (2 байта)
    trackBPM = (musicFile.read() << 8) | musicFile.read();
    
    // Рассчитываем длительность четвертной ноты
    noteDuration = 60000 / trackBPM / 4; // Для четвертных нот
    //доп
    Serial.print("скорость - ");
    Serial.println(noteDuration);
    resetAll();
    delay(2000);
   
  }
  } else{

  currentTrack=-1;
  }
    delay(300); // Антидребезг
  }

 static unsigned long lastNoteTime = 0;
  //const unsigned long noteDuration = 115; // Длительность ноты в мс

  if (millis() - lastNoteTime > noteDuration) {
    NoteCommand cmd = readNextNote();
    
   if (cmd.pin == 100) {
      resetAll();
    } 
    else if (cmd.pin != 0) {
      currentPeriod[cmd.pin] = cmd.period;
    } 
    else {
      musicFile.seek(sizeof(fileHeader));
      fillBuffer();
    }
    
    lastNoteTime = millis();
  }
}

// Чтение следующей ноты из буфера
NoteCommand readNextNote() {
  NoteCommand cmd = {0, 0};
  
 if (fileBuffer.count < 3) {
    if (!fillBuffer()) return cmd; // Не удалось прочитать данные
  }
  
  cmd.pin = readFromBuffer();
  byte high = readFromBuffer();
  byte low = readFromBuffer();
  cmd.period = (high << 8) | low;

  return cmd;
}
// Заполнение буфера из файла
bool fillBuffer() {
  if (fileBuffer.count >= BUFFER_SIZE - 256) return true;
  
  // Читаем двумя порциями для эффективности
  int firstRead = min(256, BUFFER_SIZE - fileBuffer.head);
  int secondRead = min(256, BUFFER_SIZE - fileBuffer.count - firstRead);
  
  int totalRead = 0;
  if (firstRead > 0) {
    int bytesRead = musicFile.read(&fileBuffer.data[fileBuffer.head], firstRead);
    fileBuffer.head = (fileBuffer.head + bytesRead) % BUFFER_SIZE;
    fileBuffer.count += bytesRead;
    totalRead += bytesRead;
  }
  
  if (secondRead > 0 && totalRead == firstRead) {
    int bytesRead = musicFile.read(&fileBuffer.data[fileBuffer.head], secondRead);
    fileBuffer.head = (fileBuffer.head + bytesRead) % BUFFER_SIZE;
    fileBuffer.count += bytesRead;
    totalRead += bytesRead;
  }
  
  return totalRead > 0;
}

// Чтение байта из буфера
byte readFromBuffer() {
  if (fileBuffer.count == 0) {
    if (!fillBuffer()) return 0; // Буфер пуст и файл закончился
  }
  
  byte result = fileBuffer.data[fileBuffer.tail];
  fileBuffer.tail = (fileBuffer.tail + 1) % BUFFER_SIZE;
  fileBuffer.count--;
  return result;
}

/*
Called by the timer inturrupt at the specified resolution.
*/
void tick() {
  for (byte p = FIRST_PIN; p <= PIN_MAX; p += 2) {
    if (currentPeriod[p] > 0) {
      if (++currentTick[p] >= currentPeriod[p]) {
        togglePin(p, p + 1);
        currentTick[p] = 0;
      }
    }
  }
}

void errorBlink(int count) {
  pinMode(13, OUTPUT);
  while (1) {
    for (int i = 0; i < count; i++) {
      digitalWrite(13, HIGH);
      delay(300);
      digitalWrite(13, LOW);
      delay(300);
    }
    delay(1000);
  }
}

void togglePin(byte pin, byte direction_pin) {
  
  //Switch directions if end has been reached
  if (currentPosition[pin] >= MAX_POSITION[pin]) {
    currentState[direction_pin] = HIGH;
    digitalWrite(direction_pin,HIGH);
  }
  else if (currentPosition[pin] <= 0) {
    currentState[direction_pin] = LOW;
    digitalWrite(direction_pin,LOW);
  }
  
    //Update currentPosition
  if (currentState[direction_pin] == HIGH){
    currentPosition[pin]--;
  }
  else {
    currentPosition[pin]++;
  }
  
  //Pulse the control pin
  digitalWrite(pin,currentState[pin]);
  currentState[pin] = ~currentState[pin];
}


//
//// UTILITY FUNCTIONS
//

//Not used now, but good for debugging...
void blinkLED(){
  digitalWrite(13, HIGH); // set the LED on
  delay(250); // wait for a second
  digitalWrite(13, LOW);
}

//For a given controller pin, runs the read-head all the way back to 0
void reset(byte pin)
{
  digitalWrite(pin+1,HIGH); // Go in reverse
  for (byte s=0;s<MAX_POSITION[pin];s+=2){ //Half max because we're stepping directly (no toggle)
    digitalWrite(pin,HIGH);
    digitalWrite(pin,LOW);
    delay(5);
  }
  currentPosition[pin] = 0; // We're reset.
  digitalWrite(pin+1,LOW);
  currentPosition[pin+1] = 0; // Ready to go forward.
}

//Resets all the pins
void resetAll(){
  
  // Old one-at-a-time reset
  //for (byte p=FIRST_PIN;p<=PIN_MAX;p+=2){
  // reset(p);
  //}
  
  // New all-at-once reset
  for (byte s=0;s<80;s++){ // For max drive's position
    for (byte p=FIRST_PIN;p<=PIN_MAX;p+=2){
      digitalWrite(p+1,HIGH); // Go in reverse
      digitalWrite(p,HIGH);
      digitalWrite(p,LOW);
    }
    delay(5);
  }
  
  for (byte p=FIRST_PIN;p<=PIN_MAX;p+=2){
    currentPosition[p] = 0; // We're reset.
    digitalWrite(p+1,LOW);
    currentState[p+1] = 0; // Ready to go forward.
  }
  
}