
#include <dht11.h>



#include <SimpleTimer.h>


#define BLYNK_PRINT Serial    // Comment this out to disable prints and save space
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



#define DHT11_PIN 4 //d2
#define KNP 2 //d4
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "eacabd5f1b144197b211d2909dd673ba";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "TP-LINK_FA21AA";
char pass[] = "rellurtep12";

boolean KN=false;
SimpleTimer timer;
dht11 DHT;
int count;
 int chk; 
void setup()
{
  Serial.begin(9600); // See the connection status in Serial Monitor
   Blynk.begin(auth, ssid, pass);
    pinMode(KNP, INPUT_PULLUP);
      pinMode(16, OUTPUT);
  // Setup a function to be called every second
  timer.setInterval(1000L, sendUptime);
  attachInterrupt(KNP, notifyOnButtonPress, CHANGE);
}

// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendUptime()
{
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(10, DHT.temperature); //virtual pin
  Blynk.virtualWrite(11, DHT.humidity); // virtual pin 
}
void notifyOnButtonPress() {
  /*
 if(KNP == 1)
  {
    digitalWrite(16,true);
    BLYNK_LOG("Button is pressed");
        Blynk.notify("D4 is pressed");    
    }
*/
}

void loop()
{ 
    Blynk.run(); // Initiates Blynk
  timer.run(); // Initiates SimpleTimer

  
  KN= digitalRead(KNP);
  Serial.println(KN);
    delay(100);
  if (KN==true)
  
  {count= count+1;
   if (count >12){
    BLYNK_LOG("Button is pressed");
        Blynk.notify("D4 is pressed");   
        count=0;
   }
    }
    else
    {
       digitalWrite(5, HIGH);
      }

 
  chk = DHT.read(DHT11_PIN);    // READ DATA
 
  
}

