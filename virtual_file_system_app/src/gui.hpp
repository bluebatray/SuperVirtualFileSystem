#pragma once

#include <memory>

#include "io/i_input_handler.hpp"
#include "io/i_output_handler.hpp"

class Gui {

public:
	Gui(IInputHandler& inputHandler, IOutputHandler& outputHandler) : inputHandler(inputHandler), outputHandler(outputHandler) {}
	void run();

private:

	const std::string find_suggestion(std::string prefix);

	IInputHandler& inputHandler;
	IOutputHandler& outputHandler;
};
