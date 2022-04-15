# ESP32 data stream comparisons
## Description
Comparing data streaming methods for ESP32. The main comparison is data rate, specifically the number of 4 byte floats that can be sent though in a second. The frequency is calculated and sent as a float. Although reliability is also an important factor. The data is streamed from 1 core only using a timer interrupt for consistency.

## Comparisons
### USB UART - 6666Hz
Using the built in serial library from arduino IDE. The receiver is the Arduino IDE Serial Monitor.

### WebSerial.h - 10Hz
Using Ayush Sharma's WebSerial library: https://github.com/ayushsharma82. Higher frequencies lead to buffer overflows

### BluetoothSerial.h - 7Hz
Using the "BluetoothSerial" library from arduino IDE. The receiver is an android app: https://play.google.com/store/apps/details?id=com.giumig.apps.bluetoothserialmonitor. There are some fluctuations in the period. Any higher frequencies will only work for a short while

## Analysis
