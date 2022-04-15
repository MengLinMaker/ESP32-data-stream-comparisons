/*
  Name: WebSerial Stream Test
  Purpose: Streams serial data over WIFI using server on esp32
  For determining the max speed of streaming: 8 decimal float @ 10Hz
  Based off Ayush's WebSerial Demo: https://github.com/ayushsharma82

  @author Meng Lin
  @version 1.0 15/04/22
*/

#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <WebSerial.h>

AsyncWebServer server(80);

const char* ssid = "Aussie Broadband 6713"; // Your WiFi SSID
const char* password = "hicahivuca"; // Your WiFi Password

// Change frequency of data transfer
const long frequency = 10;
const long ideal_period = round(1000000.0/frequency);





void IRAM_ATTR sendData(){
  float actual_period = 1000000.0/timeStep();
  char msg[16];
  dtostrf(actual_period,3,8,msg);
  WebSerial.println(msg);
}





void setup() {
  Serial.begin(1000000);
  vTaskDelay(500);
  // Connect to wifi
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.printf("WiFi Failed!\n");
    return;
  }

  // Start WebSerial
  WebSerial.begin(&server);
  server.begin();

  // Print url to access WebSerial
  Serial.println("Access webserial url:");
  Serial.print(WiFi.localIP());
  Serial.println("/webserial");
}





void loop(){
  sendData();
  delayPeriod_us(ideal_period);  
}
