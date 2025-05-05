#pragma once

#include "../i_command.hpp"

#include "../../filesystem/file_system.hpp"

namespace virtualfilesystem
{
class ListDirectoryCommand : public ICommand
{
   public:
    ListDirectoryCommand(FileSystem& filesystem)
        : m_filesystem(filesystem)
    {
    }

    CommandResult handle_command(std::vector<std::string> args) override;

   std::string format_time(time_t time);

   private:
    long long get_digits(long long size);
    FileSystem& m_filesystem;
};

}  // namespace virtualfilesystem