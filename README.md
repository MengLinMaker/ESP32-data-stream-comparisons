# ESP32 data stream comparisons
## Description
Comparing data streaming methods for ESP32:
* Reliable data rate - no signs of crashes (max speed may be higher but less reliable).
* Frequency is calculated as number of 4 byte floats received in a second - sending in batches is valid.
* The data is sent repeatedly using a timer interrupt for consistency.
* Note: Bytes/s = freq*4
#
#
## Comparisons - Fastest to slowest
### USB UART - 9000Hz (wired esp32 to PC)
Using the built in "serial_library" from arduino IDE. The receiver is the Arduino IDE Serial Monitor. The baud rate was set to 2000000. Note: this is wired and requires good quality usb cable and board. The cheap esp32 boards only acheived a max reliable baud rate of 500000. The rate of printing depends on the number of symbols printed

### esp_now.h - 7200Hz 60batch (wireless esp32 to esp32)
Using the "esp_now" library and modified code by Rui Santos: https://RandomNerdTutorials.com/esp-now-esp32-arduino-ide/. This protocol is capable of sending out 12000Hz x 4bytes = 48000bytes/s for short durations in close proximity. Although theoretical maximum is 125000bytes/s, this is unlikely to be achieved; even half this speed is difficult. The data can be streamed to arduino IDE for fast wireless communication to computer.

### WebSerial.h - 10Hz (wireless esp32 to website)
Using Ayush Sharma's WebSerial library: https://github.com/ayushsharma82. Higher frequencies lead to buffer overflows.

### BluetoothSerial.h - 7Hz (wireless esp32 to android mobile)
Using the "BluetoothSerial" library from arduino IDE. The receiver is an android app: https://play.google.com/store/apps/details?id=com.giumig.apps.bluetoothserialmonitor. There are some fluctuations in the period. Any higher frequencies will only work for a short while.
##
#
## Sensor streaming
### BNO080 I2C - 200Hz (include wireless communication through 2 esp32 to PC)
Streaming orientation quaternion, acceleration and angular velocity. The I2C rate is 400000kbit/s. The original library and example by Nathan has some inefficiencies: https://github.com/sparkfun/SparkFun_BNO080_Arduino_Library. Data rate is currently capped by the I2C speed. Note:some values are repeated due to the constant need for checking if data is availiable inorder to reveive data updates. This is caused by the Hillcrest's SHTP protocol. Inefficiencies can be recuced with interrupts.
