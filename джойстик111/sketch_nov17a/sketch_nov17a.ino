#include <Arduino.h>

const int latch = 4; // 12pin of joystick
const int clock = 2; // 9pin of joystick
const int data = 3;  // 8pin of joystick

const int TICK = 3;

int x = 0;
int y = 0;
  
uint8_t btns = 0;

void init_joystick(int latch, int clock, int data)
{
    pinMode(latch, OUTPUT);
    pinMode(clock, OUTPUT);
    pinMode(data, INPUT);

    digitalWrite(clock, HIGH);
}

int get_keys_state_joystick(int latch, int clock, int data)
{
    digitalWrite(latch, HIGH);
    delayMicroseconds(TICK);
    digitalWrite(latch, LOW);

    int keys_state = 0;

    for (int i = 1; i <= 8; ++i) {
        delayMicroseconds(TICK);
        digitalWrite(clock, LOW);

//        keys_state <<= 1;
//        keys_state += digitalRead(data);

        keys_state >>= 1;
        (digitalRead(data)!=0) ?  keys_state |= 0x80 : keys_state &= 0x7F ;

        delayMicroseconds(TICK);
        digitalWrite(clock, HIGH);
    }

    return (keys_state ^ 0xFF);
}

void setup()
{
    init_joystick(latch, clock, data);

//    Serial.begin(9600);
}

void loop()
{
  btns = get_keys_state_joystick(latch, clock, data);
 
  if (bitRead(btns, 4) && bitRead(btns, 5)) y = 0; else if bitRead(btns, 4) y = -127; else if bitRead(btns, 5) y = 127; else y=0;
  if (bitRead(btns, 6) && bitRead(btns, 7)) x = 0; else if bitRead(btns, 6) x = -127; else if bitRead(btns, 7) x = 127; else x=0;
  
/*
  Serial.print(x);
  Serial.print(" ");
  Serial.print(y);
  Serial.print(" ");
  Serial.println(btns, HEX);
  delay(100);
*/  
  
  Joystick.move(x, y, btns);

}
