/*
	IMUdata management for storage, recieving and printing data
  	@author Meng Lin
  	@version 1.0 17/04/22
*/

#include "IMUData.h"

void IMUdata::update_BNO080(BNO080 *IMU_BNO080, unsigned long timeOut)
{
	unsigned long newTimeStamp = micros();
	while (micros() - newTimeStamp < timeOut)
	{
		IMU_BNO080->receivePacket();
		IMU_BNO080->parseInputReport();
	}

	this->quat[0] = IMU_BNO080->getQuatReal();
	this->quat[1] = IMU_BNO080->getQuatI();
	this->quat[2] = IMU_BNO080->getQuatJ();
	this->quat[3] = IMU_BNO080->getQuatK();
	this->acc[0] = IMU_BNO080->getAccelX();
	this->acc[1] = IMU_BNO080->getAccelY();
	this->acc[2] = IMU_BNO080->getAccelZ();
	this->gyro[0] = IMU_BNO080->getGyroX();
	this->gyro[1] = IMU_BNO080->getGyroY();
	this->gyro[2] = IMU_BNO080->getGyroZ();
}

void IMUdata::printAll()
{
	this->printQuat();
	this->printAcc();
	this->printGyro();
}

void IMUdata::printQuat()
{
	char string_buff[64];
	sprintf(string_buff, "Quat:[%f,%f,%f,%f]", this->quat[0], this->quat[1], this->quat[2], this->quat[3]);
	Serial.println(string_buff);
}

void IMUdata::printAcc()
{
	char string_buff[64];
	sprintf(string_buff, "Acc:[%f,%f,%f]", this->acc[0], this->acc[1], this->acc[2]);
	Serial.println(string_buff);
}

void IMUdata::printGyro()
{
	char string_buff[64];
	sprintf(string_buff, "Gyro:[%f,%f,%f]", this->gyro[0], this->gyro[1], this->gyro[2]);
	Serial.println(string_buff);
}