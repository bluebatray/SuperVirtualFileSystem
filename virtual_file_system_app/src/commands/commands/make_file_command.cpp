#include "make_file_command.hpp"

#include <numeric>
#include <sstream>

#include "../../helper/container_helper.hpp"

namespace virtualfilesystem
{

CommandResult MakeFileCommand::handle_command(std::vector<std::string> args)
{
    std::string mergedArgs = helper::join(args.begin() + 2, args.end(), " ");

    m_filesystem.make_file(args[1], mergedArgs);

    return CommandResult(CommandResultType::Success);
}

}
