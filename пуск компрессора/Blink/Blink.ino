bool a=true;
// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(4, OUTPUT);
}


// the loop function runs over and over again forever
void loop() {
  if(a){
  digitalWrite(4, HIGH);  // turn the LED on (HIGH is the voltage level)
  delay(550);                      // wait for a second
  digitalWrite(4, LOW);   // turn the LED off by making the voltage LOW
  delay(500);
  digitalWrite(4, HIGH);
  delay(700);
  digitalWrite(4, LOW);  
  delay(500);
  digitalWrite(4, HIGH);
  delay(900);
  digitalWrite(4, LOW);
   delay(500);
  digitalWrite(4, HIGH);
  
  a=false;
      }
  else   
   digitalWrite(4, HIGH);
                  // wait for a second
}
