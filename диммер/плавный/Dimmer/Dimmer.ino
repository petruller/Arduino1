/*
  Dimmer

  Demonstrates sending data from the computer to the Arduino board, in this case
  to control the brightness of an LED. The data is sent in individual bytes,
  each of which ranges from 0 to 255. Arduino reads these bytes and uses them to
  set the brightness of the LED.

  The circuit:
  - LED attached from digital pin 9 to ground through 220 ohm resistor.
  - Serial connection to Processing, Max/MSP, or another serial application

  created 2006
  by David A. Mellis
  modified 30 Aug 2011
  by Tom Igoe and Scott Fitzgerald

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Dimmer
*/

const int ledPin = 5;  // the pin that the LED is attached to
   int t;
void setup() {
  // initialize the serial communication:
  Serial.begin(9600);
  // initialize the ledPin as an output:
  pinMode(ledPin, OUTPUT);

for (int i=1; i<=255; i++)
 {
    // read the most recent byte (which will be from 0 to 255):
    // set the brightness of the LED:
    analogWrite(ledPin, i);
Serial.println(i);
delay(60);

  }


}

void loop() {
 

  //delay(10000);
}
