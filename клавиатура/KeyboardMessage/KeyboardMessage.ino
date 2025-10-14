#include <Arduino.h>

const int data = 3;
const int latch = 4;
const int clock = 2;

const int TICK = 2;

void init_joystick(int data, int latch, int clock)
{
    pinMode(data, INPUT);
    pinMode(clock, OUTPUT);
    pinMode(latch, OUTPUT);
      pinMode(5, OUTPUT);
 digitalWrite(5, LOW);
    digitalWrite(clock, HIGH);
}

int get_keys_state_joystick(int data, int latch, int clock)
{
    digitalWrite(latch, HIGH);
    delayMicroseconds(TICK);
    digitalWrite(latch, LOW);

    int keys_state = 0;

    for (int i = 0; i < 8; ++i) {
        delayMicroseconds(TICK);
        digitalWrite(clock, LOW);

        keys_state <<= 1;
        keys_state += digitalRead(data);

        delayMicroseconds(TICK);
        digitalWrite(clock, HIGH);
    }

    return keys_state;
}

void setup()
{
    init_joystick(data, latch, clock);

    Serial.begin(57600);
}

void loop()
{
/*
    if(get_keys_state_joystick(data, latch, clock)==247)
    {   Serial.println(1);
    delay(250);
      digitalWrite(5, HIGH);
      }else
      {
      digitalWrite(5, LOW);  
        }*/

if(get_keys_state_joystick(data, latch, clock)==254)
    {   Serial.println(2);
     delay(150);
    } else if(get_keys_state_joystick(data, latch, clock)==251)
    {   Serial.println(3);
     delay(150);
    }else if(get_keys_state_joystick(data, latch, clock)==253)
    {   Serial.println(4);
     delay(150);
    }else if(get_keys_state_joystick(data, latch, clock)==223)
    {   Serial.println(5);
     delay(150);
    } else if(get_keys_state_joystick(data, latch, clock)==239)
    {   Serial.println(6);
     delay(150);
    } else if(get_keys_state_joystick(data, latch, clock)==127)
    {   Serial.println(7);
     delay(150);
    }else if(get_keys_state_joystick(data, latch, clock)==247)
    { delay(150)  ;
      Serial.println(1);}
     else if(get_keys_state_joystick(data, latch, clock)==255){
       Serial.println(0);
      }
   
}
