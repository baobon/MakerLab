#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const char* ssid = "Maker_RC_Car";
const char* pass = "makerbot123";
ESP8266WebServer server(80);

String command, lastcommand = "makershop";

void setup() {
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
  server.handleCleient();
  command = server.arg("MakerCar");
  //  if (command != "" && command != lastcommand)
  //  {
  //    Serial.println(command);
  //    lastcommand = command;
  //    command = "";
  //  }

  if (command != "")
  {
    Serial.println(command);
    command = "";
  }

}

void HTTP_handleRoot(void) {

  if ( server.hasArg("MakerCar") ) {
    Serial.println(server.arg("MakerCar"));
  }
  server.send ( 200, "text/html", "" );
  delay(1);
}
