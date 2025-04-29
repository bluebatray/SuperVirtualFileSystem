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
       
    //it's valid
    m_fileSystem.MakeDir(args[1]);

    return CommandResult(CommandResultType::Success);
}

}
