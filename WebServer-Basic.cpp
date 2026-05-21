#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);

void homePage() {

  String page = "<h1>Drone Dashboard</h1>";

  server.send(200, "text/html", page);
}

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("Connected!");

  Serial.println(WiFi.localIP());

  server.on("/", homePage);

  server.begin();
}

void loop() {

  server.handleClient();
}