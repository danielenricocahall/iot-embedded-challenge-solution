/*
 * DataReader.cpp
 *
 *  Created on: Jun 14, 2019
 *      Author: daniel
 */



#include "DataReader.h"
#include <curl/curl.h>
#include <cstdint>
#include <iostream>
#include <memory>
#include <boost/asio.hpp>
#include <stdlib.h>


DataReader::DataReader() {

}

DataReader::~DataReader() {

}

const std::size_t DataReader::callback(
		const char* in,
		const std::size_t size,
		const std::size_t num,
		std::string* out) {
	const std::size_t totalBytes(size * num);
	out->append(in, totalBytes);
	return totalBytes;
}


void DataReader::readData(
		const std::string& url) {

		CURL* curl = curl_easy_init();

	    // Set remote URL.
	    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

	    // Response information.
	    int httpCode(0);
	    std::shared_ptr<std::string> httpData(new std::string());

	    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, callback);
	    curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData.get());

	    // Run our HTTP GET command, capture the HTTP response code, and clean up.
	    curl_easy_perform(curl);
	    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
	    curl_easy_cleanup(curl);
	    if (httpCode == 200)
	    {
	        Json::Value jsonData;
	        Json::Reader jsonReader;

	        if (jsonReader.parse(*httpData, jsonData))
	        {
	            const Json::Value devices =  jsonData["devices"];
	            m_devices_information = readDevicesInformation(devices);

	        }
	        else
	        {
	            std::cout << "Could not parse HTTP data as JSON" << std::endl;
	            std::cout << "HTTP data was:\n" << *httpData.get() << std::endl;
	        }
	    }
	    else
	    {
	        std::cout << "Couldn't GET from " << url << " - exiting" << std::endl;
	    }

}

const std::vector<std::string> DataReader::readDevicesInformation(const Json::Value& devices) {
	std::vector<std::string> devices_information;
    for (unsigned int i = 0; i < devices.size(); ++i) {
    	const std::string payload= processDevice(devices[i]);
    	devices_information.push_back(payload);
    	}
    return devices_information;
    }


const std::string DataReader::processDevice(const Json::Value& device) {
	std::stringstream ss;
	ss << "J";
	const std::string type = device["type"].asString();
	const std::string state = device["state"].asString();
	ss << type.at(0);

	uint8_t stateValue;

	if(type.compare("light") == 0) {
		if(state.compare("on") == 0) {
			stateValue = 1;
		}
		else {
			stateValue = 0;
		}
	}
	else {
		stateValue = atoi(state.c_str());
	}
	if(type.compare("heat") == 0) {
		const std::string unit = device["unit"].asString();
		if(unit.compare("F") == 0) {
			// convert to C
			// Note: maybe put this in util?
			stateValue = (9/5) * stateValue + 32;
		}
	}
	ss << std::to_string(stateValue);
	// this is where checksum logic would go, but I'm a litte uncertain how to implement it:
	// const unsigned int checksum = ...;
	// ss << checksum;

	// CR
	ss << "\r";
	//NL
	ss << "\n";
	std::cout << ss.str();
	std::string payload = ss.str();
	return payload;
}

void DataReader::sendData(
		const unsigned int baud_rate,
		const std::string& serial_port) {
	static boost::asio::io_service ios;
	boost::asio::serial_port sp(ios, serial_port);
	sp.set_option(boost::asio::serial_port::baud_rate(baud_rate));
	for(const std::string& payload: m_devices_information) {
		sp.write_some(boost::asio::buffer(payload));
	}
	sp.close();
}
