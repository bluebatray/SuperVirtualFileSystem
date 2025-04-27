#include "make_file_command.hpp"

void virtualfilesystem::MakeFileCommand::handle_command(std::vector<std::string> args)
{
    m_filesystem.MakeFile(args[0], args[1]);
}