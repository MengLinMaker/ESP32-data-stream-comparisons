/*
  Name: Receiver for serial printing BNO080 data
  Purpose: Wirelessly receiving BNO080 IMU data from sender esp32. Then data is serial printed.
  Data includes quaterions,acceleration and angular velocity on Esp32 at high frequencies.
  Credits: Based off Rui Santos's ESP_NOW library: https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/
  @author Meng Lin
  @version 1.1 20/04/22
*/

#include "src/IMUData.h"
#include "src/esp_now_wrapper.h"

IMUdata IMU;





void OnDataRec(const uint8_t *mac, const uint8_t *incomingData, int len){
  memcpy(&IMU, incomingData, sizeof(IMU));
  //Serial.println(timeStep());
  
  //*
  char string_buff[128];
  sprintf(string_buff,"%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", IMU.quat[0], IMU.quat[1], IMU.quat[2], IMU.quat[3],
  IMU.acc[0], IMU.acc[1], IMU.acc[2], IMU.gyro[0], IMU.gyro[1], IMU.gyro[2]);
  Serial.println(string_buff);
  //*/
}





void setup(){
  Serial.begin(500000);
  setupEspNowReceiver(OnDataRec);
} 

void loop(){}
