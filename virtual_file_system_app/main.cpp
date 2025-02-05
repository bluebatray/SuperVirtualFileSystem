#include <iostream>


#include "src/gui.hpp"
#include "src/io/console_input.hpp"
#include "src/io/console_output.hpp"


#include "virtual_file_system.hpp"
int main()
{
	VirtualFileSystem vfs;
  vfs.PrintFileSystemInfo();
        return 0;
	ConsoleInput inputHandler;
	ConsoleOutput outputHandler;

	Gui theGui(inputHandler, outputHandler);
	theGui.run();

	return 0;
}
