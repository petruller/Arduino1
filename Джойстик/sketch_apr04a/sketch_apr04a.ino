#include <Joystick.h>
#include <Arduino.h>
//#include "Keyboard.h"
const int data = 3;
const int latch = 4;
const int clock = 2;
Joystick_ Joystick;
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
 Joystick.begin();
 //  Serial.begin(57600);
   //Keyboard.begin();
}

void loop()
{/*
 Serial.println(get_keys_state_joystick(data, latch, clock));
delay(500);
*/
if(get_keys_state_joystick(data, latch, clock)==254)//righ
    {//Keyboard.write('d');
      Joystick.pressButton(2);
      
     delay(300);
    } else if(get_keys_state_joystick(data, latch, clock)==251) //down
    { // Keyboard.write('s');
      Joystick.pressButton(3);
     delay(300);
    }else if(get_keys_state_joystick(data, latch, clock)==253)//left
    { //  Keyboard.write('a');
      Joystick.pressButton(1);
     delay(300);
    }else if(get_keys_state_joystick(data, latch, clock)==223) //select
    { //   Keyboard.write('v');
      Joystick.pressButton(4);
     delay(300);
    } else if(get_keys_state_joystick(data, latch, clock)==239) //start
    {//    Keyboard.write('b');
      Joystick.pressButton(5);
     delay(300);
    } else if(get_keys_state_joystick(data, latch, clock)==127) //red
    { //   Keyboard.write('o');
      Joystick.pressButton(6);
     delay(300);
    }else if(get_keys_state_joystick(data, latch, clock)==191) //black
    { //   Keyboard.write('p');
      Joystick.pressButton(7);
      //  Serial.println("7");
     delay(300);
    }else if(get_keys_state_joystick(data, latch, clock)==247)//up
    { 
     Joystick.pressButton(0);
      // Serial.println("0");
      // Keyboard.write('w');
      delay(300);
     }
      
     
   
}
