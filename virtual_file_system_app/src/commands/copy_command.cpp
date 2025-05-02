#include "copy_command.hpp"

#include <iostream>
#include <string>

namespace virtualfilesystem
{
CommandResult CopyCommand::handle_command(std::vector<std::string> args)
{
    PrintFileSystemInfo();

    m_filesystem.copy_file(args[1], args[2]);

    return CommandResult(CommandResultType::Success);
}
}  // namespace virtualfilesystem