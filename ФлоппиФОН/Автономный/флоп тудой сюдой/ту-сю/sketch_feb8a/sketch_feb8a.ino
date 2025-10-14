int step = 2, direct = 3; // Управляющие пины

void setup() {
pinMode(step, OUTPUT);
pinMode(direct, OUTPUT);
}

void loop() {
for(int i = 0; i < 80; i++){ //Прогоняем считывающую головку по всей длине
digitalWrite(step, HIGH);
delay(10);
digitalWrite(step, LOW);
}

digitalWrite(direct, !digitalRead(direct)); // Меняем направление движения
}

/*void playNote (float freq, float duration) {
int tempo=5;
float val =(925000/freq) / 2;
float noteDuration= 2200 / duration; 
float time = millis() + noteDuration; 

  while (millis () < time) { 
    digitalWrite (direction, LOW);
     digitalWrite (step, LOW);
delayMicroseconds (val);
digitalWrite (step, HIGH);
delayMicroseconds (val);
digitalWrite (direction, HIGH);
digitalWrite (step, LOW);
delayMicroseconds (val);
digitalWrite (step, HIGH); 
delayMicroseconds (val);
  }
delay (tempo);
}*/