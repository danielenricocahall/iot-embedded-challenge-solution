/*
 * Driver.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: daniel
 */




// main.cpp
#include <cstdint>
#include <iostream>
#include <memory>
#include <string>
#include "DataReader.h"



int main()
{

	DataReader * dataReader = new DataReader();
	const std::string url = "http://localhost:8080/devices/";
	const int baud_rate = 9600;
	const std::string serial_port = "/dev/tty0";
	dataReader->readData(url);
	dataReader->sendData(baud_rate, serial_port);
	return 0;
}
