#include <iostream>

#include "gui.hpp"
#include "io/console_input.hpp"
#include "io/console_output.hpp"

#include "virtual_file_system.hpp"
int main()
{
	//VirtualFileSystem vfs;
 // vfs.PrintFileSystemInfo();
 //       return 0;

	io::ConsoleInput inputHandler;
	io::ConsoleOutput outputHandler;

	Gui theGui(inputHandler, outputHandler);
	theGui.run();

	return 0;
}
