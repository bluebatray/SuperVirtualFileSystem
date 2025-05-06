#include "copy_command.hpp"

#include <iostream>
#include <string>

namespace virtualfilesystem
{
CommandResult CopyCommand::handle_command(std::vector<std::string> args)
{
    PrintFileSystemInfo();

    ErrorCode result = m_filesystem.copy_node(args[1], args[2]);

    //todo handle different errorcodes
    return CommandResult(CommandResultType::Success);
}
}  // namespace virtualfilesystem