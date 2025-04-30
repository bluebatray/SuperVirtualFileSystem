#include "copy_command.hpp"

#include <iostream>
#include <string>

namespace virtualfilesystem
{
CommandResult CopyCommand::handle_command(std::vector<std::string> args)
{
    PrintFileSystemInfo();

    m_filesystem.copy_file(args[0], args[1]);

    return CommandResult(CommandResultType::Success);
}
}  // namespace virtualfilesystem