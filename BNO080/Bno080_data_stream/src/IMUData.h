/*
    IMUdata management for storage, recieving and printing data
    @author Meng Lin
    @version 1.0 17/04/22
*/

#include "Arduino.h"
#include "TinyBNO080.h"

class IMUdata
{
public:
    float acc[3] = {0};
    float gyro[3] = {0};
    float quat[4] = {0};
    void update_BNO080(BNO080 *IMU_BNO080, unsigned long timeOut = 5000);
    void printAll();
    void printQuat();
    void printAcc();
    void printGyro();
};