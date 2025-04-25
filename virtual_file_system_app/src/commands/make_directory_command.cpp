#include "make_directory_command.hpp"

#include <iostream>
#include <string>

void virtualfilesystem::MakeDirectoryCommand::handle_command(std::vector<std::string> args)
{
    m_fileSystem.MakeDir(args[0]);
}
