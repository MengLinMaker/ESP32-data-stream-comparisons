/*
  Name: ESP NOW receiver with USB UART
  Purpose: Receives stream data from sender and sends it over USB UART to computer
  For catching
  Credits: Based off Rui Santos's ESP_NOW library: https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  @author Meng Lin
  @version 1.0 16/04/22
*/

#include <esp_now.h>
#include <WiFi.h>

const unsigned char batch = 60;

// REPLACE WITH YOUR RECEIVER MAC Address
// uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0x88, 0xBB, 0x94};

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  float actual_frequency[batch];
} struct_message;
struct_message myData;






void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len){
  memcpy(&myData, incomingData, sizeof(myData));
  float actual_frequency = batch*1000000.0/timeStep();
  Serial.println(actual_frequency,0);
  /*
  for (int i = 0; i < batch; i++){
    Serial.print(myData.actual_frequency[i],2);
    Serial.print(", ");
  }
  Serial.println();
  //*/
}






void setup(){
  // Initialize Serial Monitor
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
  
  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}

void loop(){}
