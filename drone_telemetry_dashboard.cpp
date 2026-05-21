#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Wokwi-GUEST";
const char* password = "";

WebServer server(80);

int altitude = 120;
int speed = 40;
float battery = 100;

void homePage() {

  String page = "";

  page += "<h1>Drone Dashboard</h1>";

  page += "<p>Altitude: ";
  page += altitude;
  page += " m</p>";

  page += "<p>Speed: ";
  page += speed;
  page += " km/h</p>";

  page += "<p>Battery: ";
  page += battery;
  page += " %</p>";

  server.send(200, "text/html", page);
}

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  Serial.print("Connecting");

  while (WiFi.status() != WL_CONNECTED) {

    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", homePage);

  server.begin();

  Serial.println("Server started");
}

void loop() {

  altitude = altitude + random(-2, 5);

  speed = random(20, 80);

  battery = battery - 0.1;

  if (battery <= 0) {

    battery = 100;
  }

  server.handleClient();

  delay(1000);
}