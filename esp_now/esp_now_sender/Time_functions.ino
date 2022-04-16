// When called, it calculates the last time the fuction is called in microseconds.
// ... excluding first call, which is used to start the timer.
unsigned long timeStep()
{
  // A copy of old time stamp tracks start of timer
  static unsigned long oldTimeStamp = 0;
  unsigned long timePassed;
  unsigned long newTimeStamp = micros();

  timePassed = newTimeStamp - oldTimeStamp;

  // update old timestamp
  oldTimeStamp = newTimeStamp;

  // time passed in seconds
  return timePassed;
}
