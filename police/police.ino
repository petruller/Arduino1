//boolean statuslamp; // состояние лампы: true - включено, false - выключено

void setup() // процедура setup
{
pinMode(2,OUTPUT); // пин 12 со светодиодом будет выходом (англ. «output»)
pinMode(3,OUTPUT);
}

void loop() // процедура loop
{
  digitalWrite(2,true);
   digitalWrite(3,false);
   delay(1000);
    digitalWrite(3,true);
   digitalWrite(2,false);
      delay(1000);
}
