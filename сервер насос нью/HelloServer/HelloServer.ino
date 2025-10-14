#include <Servo.h>

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#ifndef STASSID
#define STASSID "TP-Link_Dimon"
#define STAPSK  "55556666"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;

//ESP8266WebServer server(80);
//#include <Servo.h>

// Replace with your network credentials
//const char* ssid= "TP-Link_Dimon";
//const char* password = "55556666";
IPAddress ip(192, 168, 0, 200);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
// Set web server port number to 80
WiFiServer server(80);
Servo servo;
// Variable to store the HTTP request
String header,grad;
int rotate, rele;
// Auxiliar variables to store the current output state
String output5State = "off";
String output4State = "off";
String output6State = "off";
String output7State = "off";
String output8State = "off";
String output9State = "off";
bool nasos = true;
bool poliv=false;
unsigned long nasOnTime;
// Assign output variables to GPIO pins
const int output6 = 15;//d8
const int pultb = 13;//d7
const int pult = 12;//d6
const int outser = 14; //D5
unsigned long timing;

void setup() {
 Serial.begin(9600);
 // Initialize the output variables as outputs
pinMode(pult, INPUT);
pinMode(pultb, INPUT);
   pinMode(outser, OUTPUT);
  // Set outputs to LOW

 
//  digitalWrite(output4, LOW);
//servo.attach(14); 
// Connect to Wi-Fi network with SSID and password
Serial.print("Connecting to ");
  Serial.println(ssid);
//  WiFi.begin(ssid, password);

 WiFi.softAP(ssid, password);
 WiFi.config(ip, gateway, subnet);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
 Serial.print(".");
  }
  // Print local IP address and start web server
Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
 server.begin();
  servo.attach(14); 
             
              servo.write(55); //положение покоя 55
         
              delay(100);
              servo.detach();
            
}

void loop(){

   if (millis() - timing > 240000){ //пауза 4 мин 
  timing = millis(); 
   //------------проверка на месте ли сервопривод
   servo.attach(14);
   delay(500);
    servo.write(55);
      delay(500);
      servo.detach(); 
      Serial.println("TIMING");
      Serial.println(timing);
      //-------------
 }
 if(digitalRead(pult)==HIGH)
  {
   servo.attach(14); 
              servo.write(40);
              delay(500);
              servo.write(55);
         
              delay(500);
              servo.detach();   
  }

   if(digitalRead(pultb)==HIGH)
  {
   servo.attach(14); 
              servo.write(65);
              delay(500);
              servo.write(55);
         
              delay(500);
              servo.detach();   
  }
  WiFiClient client = server.available();   // Listen for incoming clients


/*if(digitalRead(output4)==HIGH && nasos==true) //включился насос
{
   digitalWrite(output5, HIGH);
   nasos=false;
    nasOnTime = millis();
  }
  else
  {
     //  digitalWrite(output5, LOW);
    }
if (millis() - nasOnTime > 10000 && digitalRead(output4)==HIGH && poliv ==false)//nasos==false) 
{// if (millis() - nasOnTime < 12000){
  digitalWrite(output5, LOW); //выключился насос
  servo.attach(14); 
              servo.write(60);
              delay(500);
              servo.write(25); //положение покоя 25
         
              delay(500);
              servo.detach();
  delay(1000);
 nasos=true;
 nasOnTime=0;//}
   }*/
   
    
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // turns the GPIOs on and off
            if (header.indexOf("GET /5/on") >= 0) {
              Serial.println("GPIO 5 on");
              output5State = "on";
//              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >= 0) {
              Serial.println("GPIO 5 off");
              output5State = "off";
//              digitalWrite(output5, LOW);
            } else if (header.indexOf("GET /4/on") >= 0) {
              Serial.println("GPIO 4 on");
              output4State = "on";
//              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >= 0) {
              Serial.println("GPIO 4 off");
             // output4State = "off";
            //  digitalWrite(output4, LOW);
            }
             else if (header.indexOf("GET /6/off") >= 0) {
              Serial.println("GPIO 6 off");
              output6State = "off";
               servo.attach(14);
              servo.write(0);
             // digitalWrite(output4, LOW);
              delay(500);
              servo.detach(); 
            }
              else if (header.indexOf("GET /6/on") >= 0) {
              Serial.println("GPIO 6 on");
              output6State = "on";
              servo.attach(14); 
              servo.write(90);
             // digitalWrite(output4, HIGH);
              delay(500);
              servo.detach(); 
            }
            else if (header.indexOf("/7/on") >= 0) {
              Serial.println("GPIO MY string");
              output7State = "on";
              Serial.println(header.indexOf("/7/on")); //4
            grad = header.substring(9,12);
            rotate = grad.toInt();
              Serial.println(rotate);

           if (0<=rotate<=180)
           {
           
                            servo.attach(14); 
              servo.write(rotate);
            //  digitalWrite(output4, HIGH);
              delay(500);
              servo.detach();
           }else{
            Serial.println("error gradus");
            }
            
              }
               else if (header.indexOf("GET /8/on") >= 0) {
              Serial.println("GPIO on pump");
             // output6State = "on";
              servo.attach(14); 
              servo.write(40);
              delay(500);
              servo.write(55);
         
              delay(500);
              servo.detach(); 
            } 
              else if (header.indexOf("GET /9/on") >= 0) {
               servo.attach(14); 
              servo.write(65);
              delay(500);
              servo.write(55);
         
              delay(500);
              servo.detach();   
              }
              else if (header.indexOf("GET /9/off") >= 0) {
            
              }
                            
              
            // Display the HTML web page
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=windows-1251\">");//<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS to style the on/off buttons 
            // Feel free to change the background-color and font-size attributes to fit your preferences
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #195B6A; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #77878A;}</style></head>");
            
            // Web Page Heading
            client.println("<body><h1>ESP8266 Web Server</h1>");
           /* 
            // Display current state, and ON/OFF buttons for GPIO 5  
            client.println("<p>GPIO 13 (D7) - State " + output5State + "</p>");
            // If the output5State is off, it displays the ON button       
            if (output5State=="off") {
              client.println("<p><a href=\"/5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/5/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Display current state, and ON/OFF buttons for GPIO 4  
            client.println("<p>GPIO 12 (D6) - State " + output4State + "</p>");
            // If the output4State is off, it displays the ON button       
            if (output4State=="off") {
              client.println("<p><a href=\"/4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
             if (output6State=="off") {
              client.println("<p><a href=\"/6/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/6/off\"><button class=\"button button2\">OFF</button></a></p>");
            }*/
             
             if (output8State=="off") {
              client.println("<p><a href=\"/8/on\"><button class=\"button\">PUMP</button></a></p>");
            } else {
              client.println("<p><a href=\"/8/on\"><button class=\"button\">PUMP</button></a></p>");
            }

            if (output9State=="off") {
              client.println("<p><br><br><br><br><br><br><br><br><a href=\"/9/on\"><button class=\"button\">OFF</button></a></p>");
            } else {
              client.println("<p><a href=\"/9/on\"><button class=\"button\">OFF</button></a></p>");
            }

            if (output7State=="off") {
              client.println("<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><p><a href=\"/7/on30\"><button class=\"button\">CLICK</button></a></p>");
            } else {
              client.println("<p><a href=\"/7/on55\"><button class=\"button\">CLICK</button></a></p>");
            }
            /*
            if (output9State=="off") {
              client.println("<p><a href=\"/9/on\"><button class=\"button\">Poliv</button></a></p>");
            } else {
              client.println("<p><a href=\"/9/off\"><button class=\"button button2\">Poliv off</button></a></p>");
            }//

 client.println("<p>Temperature in Celsius: ");
         //   client.println(celsiusTemp);
            client.println("*C </p><p>Temperature in Fahrenheit: ");
           // client.println(fahrenheitTemp);
            client.println("*F</p><p>Humidity: ");
         //   client.println(humidityTemp);
            
            client.println("</p>");//Vlazhnost: </p>");
            /*
            client.print(h);
            client.println("<p>Temp: </p>");
             client.print(t);*/
            client.println("</body></html>");
            
            // The HTTP response ends with another blank line
            client.println();
            // Break out of the while loop
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }

}
