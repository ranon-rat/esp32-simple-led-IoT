#include <Arduino.h>
#include <WiFi.h>

#include <WiFiConfig.hpp>
#include "server.hpp"
#include <pins.hpp>

void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(false);
  // Set pin mode
 
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  WiFi.begin((char *)SSID, (char *)PASS); // connect to our own network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.printf("\nWiFi connected\n\nCamera Stream Ready! Go to: http://%s/\n", WiFi.localIP().toString().c_str());
  initServer();
}
void loop()
{

}