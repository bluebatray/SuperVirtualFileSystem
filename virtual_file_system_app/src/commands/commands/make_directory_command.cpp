#include "make_directory_command.hpp"

#include <iostream>
#include <string>

namespace virtualfilesystem
{
CommandResult MakeDirectoryCommand::handle_command(std::vector<std::string> args)
{
    //validate
    if (args.size() != 2) {
        PrintBuffer printbuffer;

        if (args.size() == 1)
        {
            printbuffer.add_error("Missing parameter.", args[0], "NewDirectory");
        }
        else if (args.size() > 2)
        {
            printbuffer.add_error("Incorrect parameter size.", args[0], "NewDirectory");
        }

        return CommandResult(CommandResultType::Invalid, printbuffer);
    } 
    
    ErrorCode returnCode = m_fileSystem.make_directory(args[1]);

    
     if (returnCode.type == ErrorCodeType::AlreadyExists)
    {
        PrintBuffer printbuffer;

        printbuffer.add_error("Directory " + returnCode.extraData1 + " already exists.");

        return CommandResult(CommandResultType::Invalid, printbuffer);
    }

    // it's valid
    if(returnCode.type == ErrorCodeType::Success)
        return CommandResult(CommandResultType::Success);

    //file system error
    return CommandResult(CommandResultType::Invalid);
   
}

}
