#include "make_directory_command.hpp"

#include <iostream>
#include <string>

void virtualfilesystem::MakeDirectoryCommand::HandleCommand(std::vector<std::string> args)
{
    std::cout << " handle make directory command " << "\n";

    m_fileSystem.MakeDir(args[0]);
}
