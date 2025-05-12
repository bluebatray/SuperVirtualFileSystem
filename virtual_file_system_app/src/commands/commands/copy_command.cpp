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
    if (result.type == ErrorCodeType::AlreadyExists)
    {
        PrintBuffer printbuffer;
       
        printbuffer.add_error(result.extraData1 + " already exists in " + result.extraData2 + " directory.");
        return CommandResult(CommandResultType::Invalid, printbuffer);
    }

    return CommandResult(CommandResultType::Success);
}
}  // namespace virtualfilesystem