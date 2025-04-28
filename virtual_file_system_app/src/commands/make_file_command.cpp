#include "make_file_command.hpp"

#include <numeric>

namespace virtualfilesystem
{

CommandResult MakeFileCommand::handle_command(std::vector<std::string> args)
{

    std::string mergedArgs = std::accumulate(args.begin() + 1, args.end(), std::string(" "));
    m_filesystem.MakeFile(args[0], mergedArgs);

    return CommandResult(CommandResultType::Success);
}

}
