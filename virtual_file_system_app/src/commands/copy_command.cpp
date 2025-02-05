#include "copy_command.hpp"

#include <string>
#include <iostream>


std::string CopyCommand::GetCommandSyntax()
{
	return "cp";
}

void CopyCommand::HandleCommand()
{
	std::cout << " handle copy command " << std::endl;
}