#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "UNKNOWN";
const char* password = "ORYXHCKCS2011";

const int switchPin = 12;
const int ledGreen = 13;
const int ledRed = 14;

bool lastState = false;

// URL que actualizará el estado (puede ser la Space API tuya si tienes endpoint)
const char* serverUrl = "https://webhook.site/d53a47eb-031b-4891-95ee-f93a98288ee4";

void setup() {
  Serial.begin(115200);
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledRed, OUTPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");
}

void loop() {
  bool isOpen = digitalRead(switchPin) == LOW;
  if (isOpen != lastState) {
    lastState = isOpen;
    updateLeds(isOpen);
    postState(isOpen);
  }
  delay(2000);
}

void updateLeds(bool open) {
  digitalWrite(ledGreen, open ? HIGH : LOW);
  digitalWrite(ledRed, open ? LOW : HIGH);
}

void postState(bool open) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");
    String json = "{\"open\": " + String(open ? "true" : "false") + "}";
    int httpResponseCode = http.POST(json);
    Serial.print("HTTP Response: ");
    Serial.println(httpResponseCode);
    http.end();
  } else {
    Serial.println("Error WiFi");
  }
}
