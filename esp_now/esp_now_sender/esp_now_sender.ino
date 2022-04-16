/*
  Name: ESP NOW sender
  Purpose: Sends data stream to receiver.
  Credits: Based off Rui Santos's ESP_NOW library: https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  @author Meng Lin
  @version 1.0 16/04/22
*/

#include <esp_now.h>
#include <WiFi.h>

// Change frequency of data transfer
const long frequency = 7200;
const unsigned char batch = 60;
const long ideal_period = round(batch*40*1000000.0/frequency);

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x9B, 0xF5, 0x44};
//uint8_t broadcastAddress[] = {0x58, 0xBF, 0x25, 0x32, 0xDB, 0x48};

typedef struct struct_message {
  float actual_frequency[batch] = {0};
} struct_message;
struct_message myData;

esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status){}





void IRAM_ATTR sendData(){
  myData.actual_frequency[0] = batch*1000000.0/timeStep();
  for(int i = 1; i < batch; i++){ myData.actual_frequency[i] = 0.123456789; }
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
  while (result != ESP_OK) { result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData)); }
  Serial.println(myData.actual_frequency[0],0);
}






void setup(){
  // Init Serial Monitor
  Serial.begin(500000);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);
  Serial.print("Wifi Mac address: ");
  Serial.println(WiFi.macAddress());

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  // Create timer interrupt
  hw_timer_t * ticker = NULL;
  ticker = timerBegin(0, 2, true);
  timerAttachInterrupt(ticker, &sendData, true);
  timerAlarmWrite(ticker, ideal_period, true);
  timerAlarmEnable(ticker);
}

void loop(){}
