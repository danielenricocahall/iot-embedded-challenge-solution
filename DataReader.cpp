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

std::size_t callback(
		const char* in,
		const std::size_t size,
		const std::size_t num,
		std::string* out)
{
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
	            std::cout << jsonData.toStyledString() << std::endl;
	            const Json::Value devices =  jsonData["devices"];

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




