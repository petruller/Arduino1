
#define step 2 
#define direction 3
#define A2 110
#define D3 147
#define E3 165
#define F3 175
#define G3 196
#define A3 220
#define B3 247
#define D4 294

int ST=0;

int note[] = { 
A2, D3, D3, D3, A2,
G3, G3, G3, A2, F3,
F3, F3, E3, D3, E3,
F3, A2, E3, A2, E3,
E3, E3, A2, A3, A3,
A3, A2, G3, G3, G3,
F3, E3, F3, G3, A2,
F3, A2, E3, E3, E3,
A2, B3, B3, B3, A2,
G3, G3, G3, F3, E3,
F3, G3, A2, F3, A2,
E3, E3, E3, A2, D4,
D4, D4, A2, A3, A3,
A3, G3, F3, G3, A3,
A2, F3 };


int duration[] = { 
8, 8, 8, 8, 8,
8, 8, 8, 8, 8,
8, 16, 16, 16, 16,
8, 8, 8, 8, 8,
8, 8, 8, 8, 8,
8, 8, 8, 8, 16, 
16, 16, 16, 8, 8,
8, 8, 8, 8, 8,
8, 8, 8, 8, 8,
8, 8, 16, 16, 16, 
16, 8, 8, 8, 8,
8, 8, 8, 8, 8,
8, 8, 8, 8, 8,
16, 16, 16, 16, 8,
8, 8 };

void setup () {
pinMode (direction, OUTPUT);
pinMode (step, OUTPUT);
delay (500);
for (int i = 0; i < 80; i++) {
digitalWrite (step, !digitalRead(step)); 
delay(2);
}
}

void loop() { 
   for (int i=0; i < 73; i++) {
playNote (note[i], duration[i]);
}
}

void playNote (float freq, float duration) {
int tempo=5;
float val =(925000/freq) / 2;
float noteDuration= 2200 / duration; 
float time = millis() + noteDuration; 

  while (millis () < time) { 
         if(ST<=80){
          digitalWrite (step, HIGH);
delayMicroseconds (val);
digitalWrite (step, LOW);
delayMicroseconds (val);
ST++;
}
else{
  ST=0;
  digitalWrite (direction, !digitalRead(direction));
}
/*
delayMicroseconds (val);
digitalWrite (direction, HIGH);
digitalWrite (step, LOW);
delayMicroseconds (val);
digitalWrite (step, HIGH); 
delayMicroseconds (val);*/
  }
delay (tempo);
}