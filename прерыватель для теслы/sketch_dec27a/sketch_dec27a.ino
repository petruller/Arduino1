void setup() {
  // put your setup code here, to run once:
 pinMode(2, OUTPUT);

}
int a, b;

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(2, HIGH);
a = analogRead(0);
delay(a);
  digitalWrite(2, LOW);
 b = analogRead(1);
delay(b); 
}
