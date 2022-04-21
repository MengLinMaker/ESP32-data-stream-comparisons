/*
  Name: Sender for sending BNO080 data
  Purpose: Wirelessly sending data from BNO080 IMU to receiver esp32. 
  Data includes quaterions,acceleration and angular velocity on Esp32 at high frequencies.
  Credits: Modified BNO080 library based on Nathan Seidle: https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library
  @author Meng Lin
  @version 1.0 20/04/22
*/

#include "src/TinyBNO080.h"
#include "src/IMUData.h"
#include "src/esp_now_wrapper.h"

BNO080 IMU_BNO080;
IMUdata IMU;

// Change data rate
const long frequency = 100;
const long ideal_period = round(40*1000000.0/frequency);
static SemaphoreHandle_t timer_sem;
unsigned char counter = 0;

uint8_t broadcastAddress[] = {0x30, 0xAE, 0xA4, 0x9B, 0xF5, 0x44};





void sample_timer_task(void *param)
{
  timer_sem = xSemaphoreCreateBinary();
  while (1) {
    xSemaphoreTake(timer_sem, portMAX_DELAY);

    Serial.println(timeStep());
    IMU.update_BNO080(&IMU_BNO080, ideal_period/40 - 1000);
    guaranteeSend(broadcastAddress, (uint8_t*) &IMU, sizeof(IMU));
    if (counter == 9){ counter = 0; } else { counter++; }
    
    /*
    char string_buff[128];
    sprintf(string_buff, "%d,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f", counter, IMU.quat[0], IMU.quat[1], IMU.quat[2], IMU.quat[3],
    IMU.acc[0], IMU.acc[1], IMU.acc[2], IMU.gyro[0], IMU.gyro[1], IMU.gyro[2]);
    Serial.println(string_buff);
    //*/
  }
}

void IRAM_ATTR onTimer(){
  static BaseType_t xHigherPriorityTaskWoken = pdFALSE;
  xSemaphoreGiveFromISR(timer_sem, &xHigherPriorityTaskWoken);
  if( xHigherPriorityTaskWoken) {
    portYIELD_FROM_ISR(); // this wakes up sample_timer_task immediately
  }
}





void setup(){
  Serial.begin(2000000);
  setupEspNowReceiver(broadcastAddress);
  
  // Define I2C_SDA and SCL pins
  Wire.begin(21, 22);
  Wire.setClock(400000);

  const unsigned char updateTime = 5;
  IMU_BNO080.begin();
  IMU_BNO080.enableRotationVector(updateTime);
  IMU_BNO080.enableAccelerometer(updateTime);
  IMU_BNO080.enableGyro(updateTime);

  // Create timer interrupt
  hw_timer_t *ticker = NULL;
  ticker = timerBegin(0, 2, true);
  timerAttachInterrupt(ticker, onTimer, true);
  timerAlarmWrite(ticker, ideal_period, true);
  timerAlarmEnable(ticker);

  xTaskCreatePinnedToCore(sample_timer_task, "sample_timer", 4096, NULL, configMAX_PRIORITIES - 1, NULL, 1);
}

void loop(){}
