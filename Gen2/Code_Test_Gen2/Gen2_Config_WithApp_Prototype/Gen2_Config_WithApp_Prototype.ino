#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Gen_EPROM.h>
ESP8266WebServer server(80);

/*
   Constructor
*/
Gen_EPROM Eprom;

/*
   Value
*/
String command // Command read from App !!!

void setup() {
  Serial.begin(115200);

  Eprom.begin();
  Serial.begin(115200);
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, pass);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  // Starting WEB-server
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );
  server.begin();
  Serial.println("Begin Send Data");

}

void loop() {
  gen_handleClient();
}
/*
   HandleRoot HTTP Data Read From App(x)
*/

void HTTP_handleRoot(void) {

  if ( server.hasArg("Gen2") ) {
    Serial.println(server.arg("Gen2"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}

void gen_handleClient() {
  server.handleClient();
  command = server.arg("Gen2");
  if (command != "") {
    Serial.println(command);
    command == "";
  }
}
