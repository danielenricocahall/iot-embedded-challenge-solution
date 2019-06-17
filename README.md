# IOT Embedded Challenge Solution #
This is my solution to the Jefferson Health IOT Embedded Challenge. There are a few things that still need work, but I belive it has most of the requested functionality. If you have any questions, please don't hesitate to email me at danielenricocahall@gmail.com.

## Libraries/Dependencies ##
* libcurl (https://curl.haxx.se/libcurl/)
* jsoncpp (https://github.com/open-source-parsers/jsoncpp) for handling the packet
* boost (https://www.boost.org/) for accessing/interacting with serial ports


## Running ##

After starting the server, run "Driver.cpp", which should read the json from "localhost:8080/devices/",parse it and place the type/value information in the correct format, and send it to a serial port (I think I have it set to /dev/ttyS0 right now) with a specified baud rate. All the logic can be found in the DataReader class.

## TODO ##

* Checksum - not sure I understand it entirely, so I didn't add that to the serial message
* Maybe add some safety checks/precautions
* Put some logic in a util (i.e; converting F to C)
 
## Notes ##

This was a pretty cool challenge, and not overly difficult - most of the work was just finding the correct libraries to use, which I was already fairly familiar with JsonCpp and Boost.



