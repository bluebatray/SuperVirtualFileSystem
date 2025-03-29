#include "copy_command.hpp"

#include <string>
#include <iostream>

void CopyCommand::HandleCommand(std::vector<std::string> args)
{
	std::cout << " handle copy command " << "\n";

  PrintFileSystemInfo();
}