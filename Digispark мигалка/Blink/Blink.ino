/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/Blink
*/
int a, tim = 1000;
bool d;

boolean currentButton = LOW;
boolean lastButton=LOW;
//olean last

boolean kn = false;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(1, OUTPUT);
    pinMode(0, OUTPUT);
    pinMode(2, INPUT);   
}

// the loop function runs over and over again forever

boolean deb(boolean last)
{
  boolean current = digitalRead(2);
  if(last !=current)
  {
    delay(5);
    current = digitalRead(2);
    return current;
  }
  }

void loop() {
currentButton = deb(lastButton);
  if(lastButton ==LOW && currentButton ==HIGH)
    {tim=tim-200;
        if(tim<=0)
        {
          tim=2000;
          }
   /*    if(kn==false)
       {
        //digitalWrite(0, HIGH);
        
        
        }
        else
        {
          digitalWrite(0, LOW);
        kn=false;
          }*/
      }


  
  digitalWrite(1, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(0,LOW); 
  delay(tim);                       // wait for a second
  digitalWrite(1, LOW);    // turn the LED off by making the voltage LOW
digitalWrite(0, HIGH); 
  delay(tim);                       // wait for a second
}
