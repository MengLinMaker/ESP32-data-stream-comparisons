/*
  Name: ESP NOW sender
  Purpose: Sends data stream to receiver.
  Credits: Based off Rui Santos's ESP_NOW library: https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  @author Meng Lin
  @version 1.1 20/04/22
*/

#include "src/esp_now_wrapper.h"

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x9B, 0xF5, 0x44};

const unsigned char batch = 60;

typedef struct struct_message {
  float actual_frequency[batch] = {0};
} struct_message;
struct_message myData;

// Change frequency of data transfer
const long frequency = 7200;
const long ideal_period = round(batch*1000000.0/frequency);





void IRAM_ATTR sendData(){
  myData.actual_frequency[0] = batch*1000000.0/timeStep();
  for(int i = 1; i < batch; i++){ myData.actual_frequency[i] = 0.123456789; }
  guaranteeSend(broadcastAddress, (uint8_t*) &myData, sizeof(myData));
  Serial.println(myData.actual_frequency[0],0);
}





void setup(){
  Serial.begin(2000000);
  setupEspNowReceiver(broadcastAddress);

  // Create timer interrupt
  hw_timer_t * ticker = NULL;
  ticker = timerBegin(0, 2, true);
  timerAttachInterrupt(ticker, &sendData, true);
  timerAlarmWrite(ticker, round(40*ideal_period), true);
  timerAlarmEnable(ticker);
}

void loop(){}
