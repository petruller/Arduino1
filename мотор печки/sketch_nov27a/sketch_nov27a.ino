#include <Servo.h>

Servo  Motor;

void setup() {
  
  Motor.attach(2);

Motor.writeMicroseconds(2300);
delay(2000);
Motor.writeMicroseconds(800);
delay(2000);

}

void loop() {
  int val = map(analogRead(0), 0, 1023, 800, 2300);
  Motor.writeMicroseconds(val);
  // put your main code here, to run repeatedly:

}
