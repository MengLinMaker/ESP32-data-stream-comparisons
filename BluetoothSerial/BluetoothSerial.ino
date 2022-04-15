/*
  Name: Meng Lin
  Purpose: Streams serial data over bluetooth.
  For determining the max speed of streaming: 8 decimal float @ 7Hz

  @author Meng Lin
  @version 1.0 15/04/22
*/

#include "BluetoothSerial.h"

// Change frequency of data transfer
// Change frequency of data transfer
const long frequency = 7;
const long ideal_period = round(1000000.0/frequency);
BluetoothSerial SerialBT;





void IRAM_ATTR sendData(){
  float actual_period = 1000000.0/timeStep();
  SerialBT.println(actual_period,8);
}





void setup(){
  Serial.begin(1000000);
  SerialBT.begin("ESP32Stream"); //Bluetooth device name

  // Create timer interrupt
  hw_timer_t * ticker = NULL;
  ticker = timerBegin(0, 80, true);
  timerAttachInterrupt(ticker, &sendData, true);
  timerAlarmWrite(ticker, ideal_period, true);
  timerAlarmEnable(ticker);
}

void loop(){}
