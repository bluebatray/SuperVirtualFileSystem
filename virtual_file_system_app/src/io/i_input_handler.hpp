#pragma once

#include <string>

class IInputHandler {
public:
	virtual ~IInputHandler() = default;	
	virtual bool Read(std::string&) = 0;
	virtual bool ReadLine(std::string&) = 0;
	virtual char ReadChar() = 0;
};