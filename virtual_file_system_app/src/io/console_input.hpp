#pragma once

#include <string>

#include "i_input_handler.hpp"

class ConsoleInput : public IInputHandler {
	bool ReadLine(std::string&) override;
	bool Read(std::string&) override;
	char ReadChar() override;
};