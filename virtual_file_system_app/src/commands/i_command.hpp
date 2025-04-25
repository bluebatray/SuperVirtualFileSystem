
#pragma once

#include <string>
#include <vector>

#include "virtual_file_system_lib.hpp"

namespace virtualfilesystem
{

class ICommand
{
   public:
    virtual ~ICommand() = default;
    virtual void handle_command(std::vector<std::string> args) = 0;
};
}  // namespace virtualfilesystem