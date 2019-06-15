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

private:
	std::vector<std::string> m_devices_information;

};
