#include "copy_command.hpp"

#include <iostream>
#include <string>

namespace virtualfilesystem
{
void CopyCommand::handle_command(std::vector<std::string> args)
{
    std::cout << " handle copy command " << "\n";

    PrintFileSystemInfo();

    m_filesystem.CopyFile(args[0], args[1]);
}
}  // namespace virtualfilesystem