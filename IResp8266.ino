/*  since we were not told about the method to take input in the esp8266, by default I took as android app
 *  Submitted by Sudipta Pahar on 31.03.2020 @ 3:00 pm
 *  Comments are welcome
 */
#include<SoftwareSerial.h>
#include <IRrecv.h>
#include <ESP8266WiFi.h>
WiFiClient client;
WiFiServer server(80);
const char* ssid = "ssid"; //WiFi name
const char* password = "password"; //WiFi Password
String command = "";
int R1 = 1;// NodeMCU pins 1,2
int R2 = 2;
int RECV_PIN = 3;// IR receive pin
int wake_up_PIN = 4;
int state;
IRrecv irrecv(RECV_PIN);
unsigned int oldircode;
unsigned int newircode;
decode_results results;
int i;
void setup(void)
{ 

  server.begin();
  irrecv.enableIRIn();  // Start the receiver
  Serial.begin(115200);// Connect to WiFi
  WiFi.begin(ssid, password);
  connectWiFi();
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
}

void loop() 
{
  for(i=0; i<=5000; i++)
  if(irrecv.decode(&results))
  {
    newircode = results.value;
    if(newircode!= oldircode)
    {
      i=0;
    }
        if(newircode==33444015)
        {
          digitalWrite(R1, HIGH);
        }
        else if(newircode==33478695)
        {
          digitalWrite(R2, HIGH);
        }
        else if(newircode==33486855)
        {
          digitalWrite(R1, LOW);
        }
        else if(newircode==33435855)
        {
          digitalWrite(R2, LOW);
        }
        
        newircode = oldircode;
  }irrecv.resume();
  delay(100);
  if(i== 5000)
  {
    ESP.deepSleep(10e6);
  }

  
  
}
/* what happens here is the code checks for 5000 ms if there is any change in IR receive variable, if yes, the counter "i" gets reset. The moment the counter reaches 5000
 *  the deepsleep mode is activated for 10sec and again checks for any change in variable. If no then again in deepsleep mode for 0sec after 5000
 */
void connectWiFi()
{
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}
