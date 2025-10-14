// Определяем пины для каждого дисковода
#include <SPI.h>
#include <SD.h>

#define SD_CS 10 

#define DRIVE1_STEP 2
#define DRIVE1_DIR 3    //18 с полосой
#define DRIVE2_STEP 4
#define DRIVE2_DIR 5
#define DRIVE3_STEP 6
#define DRIVE3_DIR 7
#define BUTTON 8

int but1,but2,ST=0;

 String fileList[20];  // Максимум 20 файлов
    int fileCount = 0, currentf;

void Ghome(){ //головки в начельное положение
 digitalWrite (DRIVE1_DIR, HIGH);
 digitalWrite (DRIVE2_DIR, HIGH);
 digitalWrite (DRIVE3_DIR, HIGH);

 for(int i = 0; i < 80; i++){ //Прогоняем считывающую головку по всей длине
digitalWrite(DRIVE1_STEP, HIGH);
delay(10);
digitalWrite(DRIVE1_STEP, LOW);
}
//------------------

for(int i = 0; i < 80; i++){ //Прогоняем считывающую головку по всей длине
digitalWrite(DRIVE2_STEP, HIGH);
delay(10);
digitalWrite(DRIVE2_STEP, LOW);
}
//------------------
for(int i = 0; i < 80; i++){ //Прогоняем считывающую головку по всей длине
digitalWrite(DRIVE3_STEP, HIGH);
delay(10);
digitalWrite(DRIVE3_STEP, LOW);
}
//------------------
}


void findCSVFiles(String* fileList, int& fileCount) {
    File root = SD.open("/");
    fileCount = 0;
Serial.println("поиск");
    while (true) {
        File entry = root.openNextFile();
        if (!entry) {
            // Нет больше файлов
            Serial.println("нет файлов");
            break;
        }

        // Проверяем расширение файла
        String filename = entry.name();
        if (filename.endsWith(".CSV")) {
            fileList[fileCount] = filename;
            fileCount++;
        }

        entry.close();
    }

    root.close();
}



int noteToDelay(int note) {
    return 1000000 / (440 * pow(2, (note - 69) / 12.0)); // Формула для частоты ноты
}

void playNote(int stepPin, int dirPin, int freq, int duration) {
int tempo=5;
float val =(925000/freq) / 2;
//float noteDuration= 2200 / duration; 
float time = millis() +duration;// noteDuration; 

  while (millis () < time) { 
     if(ST<=80){
        digitalWrite (stepPin, HIGH);
delayMicroseconds (val);
digitalWrite (stepPin, LOW);
delayMicroseconds (val);
ST++;
     }else
     {
      ST=0;
      digitalWrite (dirPin, !digitalRead(dirPin));
        }

  }
delay (tempo);
}

void playMelody(const char* filename) {
    File file = SD.open(filename);
    if (!file) {
        Serial.print("Ошибка открытия файла ");
        Serial.print(filename);
        return;
    }






    unsigned long startTime = millis();
    while (file.available()) {
        // Читаем строку из файла
        String line = file.readStringUntil('\n');
        int inst = line.substring(0, line.indexOf(',')).toInt();
        line = line.substring(line.indexOf(',') + 1);
        int time = line.substring(0, line.indexOf(',')).toInt();
        String line1 = line.substring(line.indexOf(',') + 1);
        int note =  line1.substring(0, line1.indexOf(',')).toInt();
        String line2 = line1.substring(line1.indexOf(',') + 1);
        int duration = line2.substring(line2.indexOf(',') + 1).toInt();


        while (millis() - startTime < time) {}

        // Воспроизводим ноту на одном из дисководов
        //int delayTime = noteToDelay(note);
      switch (inst){
        case 0:
            playNote(DRIVE1_STEP, DRIVE1_DIR, note, duration);
            break;
       case 1:
            playNote(DRIVE2_STEP, DRIVE2_DIR, note, duration);
             break;
      case 2:         
           playNote(DRIVE3_STEP, DRIVE3_DIR, note, duration);
            break;
           default: 
           Serial.println("проблема выбора инструмента");
            break;
       }

      //кнопка
         but1= digitalRead(BUTTON);
         if(but1!=but2){

         delay(10);
       if (digitalRead(BUTTON) == HIGH) {

            if (currentf<fileCount) {
               currentf=currentf+1;
               file.close();
                Serial.println(fileList[currentf]);
        playMelody(fileList[currentf].c_str());
                                    }else
                                    {
                                      currentf=0;  
                                    }
                                       }
            but1=but2;                            
         }
        
  }   

    file.close();

   /* if (currentf<fileCount) {
      currentf=currentf+1;
      playMelody(fileList[currentf].c_str());
        }else
                                    {
                                      currentf=0;  
                                    }*/
}




void setup() {
  // Настраиваем пины как выходы
  pinMode(DRIVE1_STEP, OUTPUT);
  pinMode(DRIVE1_DIR, OUTPUT);
  pinMode(DRIVE2_STEP, OUTPUT);
  pinMode(DRIVE2_DIR, OUTPUT);
  pinMode(DRIVE3_STEP, OUTPUT);
  pinMode(DRIVE3_DIR, OUTPUT);

pinMode(BUTTON, INPUT);

Ghome();

     Serial.begin(9600);

    // Инициализация SD-карты
    if (!SD.begin(SD_CS)) {
        Serial.println("Ошибка инициализации SD-карты!");
        return;
    }
    Serial.println("SD-карта инициализирована.");

    // Поиск CSV-файлов
   
    findCSVFiles(fileList, fileCount);
   //список файлов 
   Serial.println("Список файлов: ");
   for (int i = 0; i < fileCount; i++) {
               Serial.println(fileList[i]);
       
    }


    // Воспроизведение всех найденных мелодий
    for (int i = 0; i < fileCount; i++) {
        Serial.print("Воспроизведение: ");
        Serial.println(fileList[i]);
        playMelody(fileList[i].c_str());
       delay(500);  // Пауза между мелодиями
      Ghome();
      delay(500);
    }
}

void loop() {
  
 
}