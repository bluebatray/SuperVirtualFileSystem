#pragma once

#include "../../filesystem/file_system.hpp"
#include "../i_command.hpp"
#include <string>

namespace virtualfilesystem
{
class MakeDirectoryCommand : public ICommand
{
   public:
    MakeDirectoryCommand(FileSystem& filesystem) : m_fileSystem(filesystem) {}
    CommandResult handle_command(std::vector<std::string> args) override;

   private:
    FileSystem& m_fileSystem;
};

}  // namespace virtualfilesystem