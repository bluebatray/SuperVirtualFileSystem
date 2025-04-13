#pragma once

#include <string>

#include "i_input_handler.hpp"

namespace io {

	class ConsoleInput : public IInputHandler {
		bool read_line(std::string&) override;
		bool read(std::string&) override;
		char read_char() override;
	};
}