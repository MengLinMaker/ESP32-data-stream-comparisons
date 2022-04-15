# ESP32 data stream comparisons
## Description
Comparing data streaming methods for ESP32. The main comparison is data rate, specifically the number of 4 byte floats that can be sent though in a second. Although reliability is also an important factor. The data is streamed from 1 core only using a timer interrupt for consistency.

## Comparisons
### USB UART - 9900Hz
Using the built in serial library from arduino IDE. The receiver is the Arduino IDE Serial Monitor.

### BluetoothSerial.h - 5Hz
Using the "BluetoothSerial" library from arduino IDE. The receiver is an android app: https://play.google.com/store/apps/details?id=com.giumig.apps.bluetoothserialmonitor.

## Analysis
