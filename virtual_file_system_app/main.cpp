#include <iostream>

#include "src/gui.hpp"
#include "src/io/console_input.hpp"
#include "src/io/console_output.hpp"

int main()
{
	ConsoleInput inputHandler;
	ConsoleOutput outputHandler;

	Gui theGui(inputHandler, outputHandler);
	theGui.run();

	return 0;
}
