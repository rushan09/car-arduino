#include <Car.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiAP.h>
#include <ESP8266WiFiGeneric.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266WiFiScan.h>
#include <ESP8266WiFiSTA.h>
#include <ESP8266WiFiType.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>

const char* ssid="XXXXX";
const char* password="XXXXXX";
int car_delta = -20;
WiFiServer server(80);
Car car(D8,car_delta);

void setup() {
  pinMode(D7,OUTPUT);
  Serial.begin(115200);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(250);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("Wifi connected");

  server.begin();
  Serial.println("Web server started");

  Serial.print("Connect url- ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.println();
}

void loop() {
  WiFiClient client = server.available();
  client.setNoDelay(1);
  if(!client){
    return;
  }
  String request = client.readStringUntil('\r'); 
  Serial.println(request);
  if((request.indexOf("/left=0") != -1) || (request.indexOf("/right=0") != -1)){
    digitalWrite(D7,LOW);
    car.left(0);
  }
  if(request.indexOf("/left=1") != -1){
    digitalWrite(D7,LOW);
    car.left(1);
  }
  if(request.indexOf("/left=2") != -1){
    digitalWrite(D7,HIGH);
    car.left(2);
  }
  if(request.indexOf("/right=1") != -1){
    digitalWrite(D7,LOW);
    car.right(1);
  }
  if(request.indexOf("/right=2") != -1){
    digitalWrite(D7,HIGH);
    car.right(2);
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println("");
  client.println("<DOCTYPE HTML>");
  client.println("<html>");
  client.println("<style>");
  client.println("body {background-color: #ACAEAD;}");
  client.println("</style>");
  client.println("<h1>Car controller</h1>");
  client.println("<p> use arrow keys to controll </P> ");
  client.println("<script type=\"text/javascript\" src=\"http://yourjavascript.com/12817551511/main.js\"></script>");
  client.println("<div style=\"text-align:center;width:480px;\"> ");
  client.println("<button onmousedown=\"upKey()\" onmouseup=\"\" >UP</button><br><br> ");
  client.println("<button onmousedown=\"leftKey()\" onmouseup=\"\" >LEFT</button> ");
  client.println("<button onmousedown=\"rightKey()\" onmouseup=\"\" >RIGHT</button><br><br> ");
  client.println("<button onmousedown=\"downKey()\" onmouseup=\"\" >DOWN</button></div> ");
  client.println("</html> ");
  delay(10);
}





