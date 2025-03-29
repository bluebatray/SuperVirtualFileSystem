#pragma once

#include <string>

class IOutputHandler {
public:
	virtual ~IOutputHandler() = default;
	virtual void Print(const std::string& message) = 0;
	virtual void PrintLine(const std::string& message) = 0;
	virtual void RedrawInput(const std::string& prompt, const std::string& input, const std::string& sugggested) = 0;
};

