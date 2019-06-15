/*
 * Driver.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: daniel
 */

#include <string>
#include <jsoncpp/json/json.h>

class DataReader {


public:
	DataReader();
	virtual ~DataReader();
	void readData(const std::string& url);
	const std::vector<std::string> readDevicesInformation(const Json::Value& devices);
	const std::string  processDevice(const Json::Value& device);
	void sendData(const unsigned int baud_rate, const std::string& serial_port);


private:
	std::vector<std::string> m_devices_information;
	static const std::size_t callback(
			const char* in,
			const std::size_t size,
			const std::size_t num,
			std::string* out);

};
