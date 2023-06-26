#include "DHT.h"
#include <WiFi.h>
#include <HTTPClient.h>

#define DHTPIN 15
#define DHTTYPE DHT11

DHT dht (DHTPIN, DHTTYPE);

const char* ssid = "UNTIRTAKU";
const char* password = "untirtajawara";

const char* server = "10.10.153.153";

void setup() {
  Serial.begin(9600);
  dht.begin();

  WiFi.mode(WIFI_OFF);
  delay(1000);
  WiFi.mode(WIFI_STA);

  WiFi.hostname("UNTIRTAKU");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("...");
    delay(500);
  }

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);

}

void loop() {
  float temp = dht.readTemperature();
  int hum = dht.readHumidity();

  Serial.println("Suhu :" + String(temp));
  Serial.println("Kelembaban :" + String(hum));
  
  WiFiClient wClient;
  const int httpPort = 80;
  if(!wClient.connect(server, httpPort))
  {
    Serial.println("Tidak terkoneksi ke server");
    return;
  }

  String url;
  HTTPClient http;
  url = "http://" + String(server) + "/projekiot/public/inputdata/" + String(temp) + "/" + String(hum);

  http.begin(wClient, url);
  http.GET();
  http.end();

  delay(5000);

}
