/*
  Name: ESP NOW receiver with USB UART
  Purpose: Receives stream data from sender and sends it over USB UART to computer
  For catching
  Credits: Based off Rui Santos's ESP_NOW library: https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  @author Meng Lin
  @version 1.1 20/04/22
*/

#include "src/esp_now_wrapper.h"

// REPLACE WITH YOUR RECEIVER MAC Address
// uint8_t broadcastAddress[] = {0x78, 0x21, 0x84, 0x88, 0xBB, 0x94};

const unsigned char batch = 60;

typedef struct struct_message {
  float actual_frequency[batch];
} struct_message;
struct_message myData;





void OnDataRec(const uint8_t *mac, const uint8_t *incomingData, int len){
  memcpy(&myData, incomingData, sizeof(myData));
  float actual_frequency = batch*1000000.0/timeStep();
  Serial.println(actual_frequency,0);
  //*
  for (int i = 0; i < batch; i++){
    Serial.print(myData.actual_frequency[i],2);
    Serial.print(", ");
  }
  Serial.println();
  //*/
}





void setup(){
  Serial.begin(500000);
  setupEspNowReceiver(OnDataRec);
} 

void loop(){}
