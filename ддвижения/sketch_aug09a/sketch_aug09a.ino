const int movPin = 2;

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
    pinMode(movPin, INPUT);
    pinMode(3, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
 int val = digitalRead(movPin);
    Serial.println(val);
    delay(100);
    if(val ==1)
    {
    //  digitalWrite(4,true);
   digitalWrite(3,true);
   delay(500);
  /*  digitalWrite(3,true);
   digitalWrite(4,false);
      delay(1000);*/
      }
      else
      {
         digitalWrite(3,false); 
        }
}
