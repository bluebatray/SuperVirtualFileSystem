
#pragma once

#include <string>
#include <vector>

#include "virtual_file_system_lib.hpp"
#include "command_result.hpp"

namespace virtualfilesystem
{

class ICommand
{
   public:
    virtual ~ICommand() = default;
    virtual CommandResult handle_command(std::vector<std::string> args = {}) = 0;
};
}  // namespace virtualfilesystem