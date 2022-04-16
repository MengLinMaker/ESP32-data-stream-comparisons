/*
  Name: USB UART
  Purpose: Streams serial data over USB UART
  For determining the max speed of streaming: 8 decimal float @ 9000Hz
  Baud rate needs to be set to 2000000. Otherwise, baud rate of 1000000 gives 6666Hz

  @author Meng Lin
  @version 1.0 15/04/22
*/

// Change frequency of data transfer
const long frequency = 9000;
const long ideal_period = round(40*1000000.0/frequency);





void IRAM_ATTR sendData(){
  float actual_period = 1000000.0/timeStep();
  Serial.println(actual_period,8);
}





void setup(){
  Serial.begin(2000000);

  // Create timer interrupt
  hw_timer_t * ticker = NULL;
  ticker = timerBegin(0, 2, true);
  timerAttachInterrupt(ticker, &sendData, true);
  timerAlarmWrite(ticker, ideal_period, true);
  timerAlarmEnable(ticker);
}

void loop(){}
