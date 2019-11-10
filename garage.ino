#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

static const uint8_t D0   = 16;
static const uint8_t D1   = 5;
static const uint8_t D2   = 4;
static const uint8_t D3   = 0;
static const uint8_t D4   = 2;
static const uint8_t D5   = 14;
static const uint8_t D6   = 12;
static const uint8_t D7   = 13;
static const uint8_t D8   = 15;
static const uint8_t D9   = 3;
static const uint8_t D10  = 1;

#include "passwd.h"

//const char* ssid = "...";
//const char* password = "...";
const char* WiFi_hostname = "Garage";
const int relayPin = D0;

ESP8266WebServer server(80);

void setup() {
  pinMode(relayPin, OUTPUT);
  Serial.begin(9600);
  connectToWiFi();
  server.on("/", handleRoot);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void connectToWiFi() {
  Serial.print("\n\nConnecting to ");
  Serial.println(ssid);
  WiFi.hostname(WiFi_hostname);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
}

void handleRoot() {
  if (server.arg(0)[0] == '0') {
    Serial.println("turn off");
    digitalWrite(relayPin, LOW);
  }
  if (server.arg(0)[0] == '1') {
    Serial.println("turn on");
    digitalWrite(relayPin, HIGH);
  }
  if (server.arg(0)[0] == '2') {
    Serial.print("impulse: ");
    digitalWrite(relayPin, HIGH);
    Serial.print("on ");
    delay(500);
    digitalWrite(relayPin, LOW);
    Serial.print("off");
    Serial.println("");
  }

  String msg = "";
  msg += "<!doctype html>\n";
  msg += "<html lang=\"en\">\n";
  msg += "<head>\n";
  msg += "<META HTTP-EQUIV=\"Content-Type\" CONTENT=\"text/html; charset=iso-8859-1\"/>\n";
  msg += "<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n";
  msg += "<title>Steuerung Garagentor</title>\n";
  msg += "<link rel=\"shortcut icon\" type=\"image/x-png\" href=\"";
  //Image copied from Wikipedia, see https://commons.wikimedia.org/wiki/File:Ic_settings_remote_48px.svg
  msg += "data:image/png;base64,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";
  msg += "\"/>\n";

  msg += "<style>\n";
  msg += "body { \
      font-family: \"Helvetica Neue\", Helvetica, Arial; \
      text-align: center; \
    }\n";
  msg += "a { \
      padding: 15px 21px; \
      font-size: 30px; \
      line-height: 1.4; \
      border-radius: 6px; \
      color: #fff; \
      background-color: #337ab7; \
      border-color: #2e6da4; \
      display: inline-block; \
      margin-bottom: 0; \
      font-weight: 400; \
      text-align: center; \
      white-space: nowrap; \
      vertical-align: middle; \
      touch-action: manipulation; \
      cursor: pointer; \
      background-image: none; \
      border: 1px solid transparent; \
      user-select: none; \
      text-transform: none; \
      overflow: visible; \
      margin: 0; \
      box-sizing: border-box; \
    }\n";
  msg += "</style>\n";

  msg += "<script>\n";
  msg += "function openGarage() { \
      var xhttp = new XMLHttpRequest(); \
      xhttp.open(\"GET\", \"?a=2\", true); \
      xhttp.send(); \
    }\n";
  msg += "</script>\n";

  msg += "</head>\n";

  msg += "<body>\n";
  msg += "<h1>Garagentor</h1>\n";
  //msg += "<h2><a href='?a=1'/>On</a></h2>\n";
  //msg += "<h2><a href='?a=0'/>Off</a></h2>\n";
  msg += "<a onClick='openGarage()'/>auf/zu</a>\n";
  msg += "</body>\n";
  msg += "</html>";

  server.send(200, "text/html", msg);
}
