#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include "index.h"

#ifndef APSSID
#define APSSID "ESPap"
#define APPSK  "thereisnospoon"
#endif

#define LED 2

/*variables for temperature and humidity getting*/
String str;
String temp;
String hum;
char character;
char holder;
int flag = 0;
  
/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

/*flags for leds control*/
String led_state; //2: cool,blue led; 3: warm,red led; 4: wind, yellow led;
String power_state; //1: power on; 0: power off;

ESP8266WebServer server(80);

/* Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/

void handleRoot() {
   String s = MAIN_page;
   server.send(200, "text/html", s);
}

void handleTEMP() {
 String TEMP = tempRead();
 server.send(200, "text/plane", TEMP);
}

void handleHUM() {
 String HUM = humRead();
 server.send(200, "text/plane", HUM);
}

void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Refer  xhttp.open("GET", "setLED?LEDstate="+led, true);
// Serial.println(t_state);
 if(t_state == "1")
 {
  power_state = "A";
  digitalWrite(LED,LOW); //LED ON
  ledState = "ON"; //Feedback parameter
 }
 else
 {
  power_state = "B";
  digitalWrite(LED,HIGH); //LED OFF
  ledState = "OFF"; //Feedback parameter  
 }
 Serial.println(power_state);
 server.send(200, "text/plane", ledState); //Send web page
}

void handleMode() {
 String modeState = " ";
 String t_flag = server.arg("MODEstate"); 
// Serial.println(t_flag);
 if(t_flag == "1")
 {
  led_state = "C" ; //Cool
  modeState = "COOL"; 
 }
 if(t_flag == "2")
 {
  led_state = "D"; //Warm
  modeState = "HEAT";
 }
 Serial.println(led_state);
 server.send(200, "text/plane", modeState); //Send web page
}

int control = 24;
void handleControl() {
 String showtemp = "24";
 String temp_flag = server.arg("TEMPstate"); 

 if(temp_flag == "1")
 {
  control++;
  if (control > 30 ) control = 18;
 }
 else
  {
   control--;
   if (control< 18) control = 30; 
  }   
  showtemp = showTEMP(control);
  Serial.println(showtemp);
  server.send(200, "text/plane", showtemp); //Send web page
}

String showTEMP(int control)
{
  String showtemp;
  if (control== 18) showtemp = "18";
  if (control== 19) showtemp = "19";
  if (control== 20) showtemp = "20";
  if (control== 21) showtemp = "21";
  if (control== 22) showtemp = "22";
  if (control== 23) showtemp = "23";
  if (control== 24) showtemp = "24";
  if (control== 25) showtemp = "25";
  if (control== 26) showtemp = "26";
  if (control== 27) showtemp = "27";
  if (control== 28) showtemp = "28";
  if (control== 29) showtemp = "29";
  if (control== 30) showtemp = "30";
  return showtemp;
}

String tempRead(){
  while (Serial.available()) {
//        character = char(Serial.readString()); 
        str = Serial.readString(); 
//        if (isSpace(character)){
//          continue;
//        }
        str.replace(" ", "");
//        Serial.println(str);
//        holder += character;
        flag = 1;
        delay(2);
    }
  if(flag == 1){
    temp = str.substring(7, 12);
//    Serial.println(temp);
  }
return temp;
}


String humRead(){
  while (Serial.available()) {
//        character = char(Serial.readString()); 
        str = Serial.readString(); 
//        if (isSpace(character)){
//          continue;
//        }
        str.replace(" ", "");
//        Serial.println(str);
//        holder += character;
        flag = 1;
        delay(2);
    }
  if(flag == 1){
    hum = str.substring(1, 6);
//    Serial.println(hum);
  }
return hum;
}

void setup() {
  delay(1000);
  Serial.begin(19200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.softAP(ssid, password);
  pinMode(LED, OUTPUT);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.on("/", handleRoot);
  server.on("/setLED", handleLED);
  server.on("/readTEMP", handleTEMP);
  server.on("/readHUM", handleHUM);
  server.on("/setMODE", handleMode);
  server.on("/settemp", handleControl);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  delay(1);
}
