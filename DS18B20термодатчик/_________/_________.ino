#define TEMP_PIN  5

void OneWireReset(int Pin);
void OneWireOutByte(int Pin, byte d);
byte OneWireInByte(int Pin);

void setup()
{
   Serial.begin(9600);
   Serial.print("temperature measurement setup in progress\n");

   pinMode(TEMP_PIN, INPUT);      // sets the digital pin as input (logic 1)
   digitalWrite(TEMP_PIN, LOW);
   delay(100);
}

void loop()
{
 int HighByte, LowByte, TReading, SignBit, Tc_100, Tf_100, Whole, Fract;

 OneWireReset(TEMP_PIN);       // reset
 OneWireOutByte(TEMP_PIN, 0xcc); // skip ROM code
 OneWireOutByte(TEMP_PIN, 0x44); // perform temperature conversion, strong pullup for one sec

 OneWireReset(TEMP_PIN);         // reset
 OneWireOutByte(TEMP_PIN, 0xcc); // skip ROM code
 OneWireOutByte(TEMP_PIN, 0xbe); // Read scratchpad code (temperature in this case)

 LowByte = OneWireInByte(TEMP_PIN);
 //Serial.print("Low byte = ");
 //Serial.print( LowByte );
 //Serial.println();
 
 HighByte = OneWireInByte(TEMP_PIN);
 //Serial.print("High byte = ");
 //Serial.print( HighByte );
 //Serial.println();

 TReading = (HighByte << 8) + LowByte;
 //Serial.print("Raw temp = ");
 //Serial.print( TReading );
 //Serial.println();

 SignBit = TReading & 0x8000;  // test most sig bit
 if (SignBit) // negative
 {
   TReading = (TReading ^ 0xffff) + 1; // 2's complement the answer
 }
 Tc_100 = (6 * TReading) + TReading / 4;    // multiply by (100 * 0.0625) or 6.25

 Whole = Tc_100 / 100;  // separate off the whole and fractional portions
 Fract = Tc_100 % 100;

 
 if (SignBit) // If its negative
 {
    Serial.print("-");
 }
 
 Serial.print(Whole);
 Serial.print(".");
 if (Fract < 10)
 {
    Serial.print("0");
 }
 Serial.print(Fract);
 Serial.print("C\n");

 Tf_100 = ((Tc_100 * 9) / 5) + 3200;
 Whole = Tf_100 / 100;  // separate off the whole and fractional portions
 Fract = Tf_100 % 100;

 
 if (SignBit) // If its negative
 {
    Serial.print("-");
 }
 
 Serial.print(Whole);
 Serial.print(".");
 if (Fract < 10)
 {
    Serial.print("0");
 }
 Serial.print(Fract);
 Serial.print("F\n");

 Serial.print("\n");

 delay(2000);      // 2 second delay.  Adjust as necessary
}

void OneWireReset(int Pin) // reset.  Should improve to act as a presence pulse
{
    digitalWrite(Pin, LOW);
    pinMode(Pin, OUTPUT); // bring low for 500 us
    delayMicroseconds(500);
    
    pinMode(Pin, INPUT);
    delayMicroseconds(500);
}

void OneWireOutByte(int Pin, byte d) // output byte d (least sig bit first).
{
  byte n;

  for(n = 8; n != 0; n--)
  {
     if ((d & 0x01) == 1)  // test least sig bit
     {  // if it is "1", pull low for just 5uS
        //digitalWrite(Pin, LOW);
        pinMode(Pin, OUTPUT);
        delayMicroseconds(5);
        
        // then wait (external resistor pulls line back high)
        pinMode(Pin, INPUT);
        delayMicroseconds(60);
     }
     else
     {  //lsb is "0", so pull low for 60uS
        //digitalWrite(Pin, LOW);
        pinMode(Pin, OUTPUT);
        delayMicroseconds(60);
        
        // release, allowing external resistor to pull high
        pinMode(Pin, INPUT);
     }

     d = d >> 1; // now the next bit is in the least sig bit position.
  }
  
}

byte OneWireInByte(int Pin) // read byte, least sig byte first
{
   byte d, n, b;

   for ( n = 0; n < 8; n++ )
   {
       // digitalWrite(Pin, LOW);
       // pull pin low for 5uS
       pinMode(Pin, OUTPUT);
       delayMicroseconds(5);
       
       // release pin, allowing external resistor to pull line back high for 5uS
       pinMode(Pin, INPUT);
       delayMicroseconds(5);
       
       // DS18B20 either pulls line low, or leaves it high
       // find out which...
       b = digitalRead(Pin);
       
       // wait bit time
       delayMicroseconds(50);
       
       // assemble our collected bits
       d = (d >> 1) | (b << 7); // shift d to right and insert b in most sig bit position
   }
   return(d);
}
