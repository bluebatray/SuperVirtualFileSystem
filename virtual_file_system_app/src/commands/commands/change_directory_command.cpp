#include "change_directory_command.hpp"

namespace virtualfilesystem
{
CommandResult ChangeDirectoryCommand::handle_command(std::vector<std::string> args)
{
    ErrorCode returnCode = m_filesystem.change_directory(args[1]);

    if (returnCode == ErrorCode::NotFound) {
        PrintBuffer printbuffer;
        printbuffer.add_error("Directory not found.");
        return CommandResult(CommandResultType::Invalid, printbuffer);
    }

    return CommandResult(CommandResultType::Success);
}

}  // namespace virtualfilesystem