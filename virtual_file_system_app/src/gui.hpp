#pragma once

#include <memory>

#include "io/i_input_handler.hpp"
#include "io/i_output_handler.hpp"

class Gui {

public:
	Gui(IInputHandler& input_handler, IOutputHandler& output_handler) : input_handler(input_handler), output_handler(output_handler) {}
	void run();

private:
	IInputHandler& input_handler;
	IOutputHandler& output_handler;
};
