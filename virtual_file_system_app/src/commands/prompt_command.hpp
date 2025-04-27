#pragma once

#include "../filesystem/file_system.hpp"
#include "../io/i_output_handler.hpp"
#include "i_command.hpp"

namespace virtualfilesystem
{
class PromptCommand : public ICommand
{
   public:
    PromptCommand(FileSystem& filesystem, io::IOutputHandler& outputhandler) : m_filesystem(filesystem), m_outputhandler(outputhandler) {}
    void handle_command(std::vector<std::string> args) override;

    private:
    FileSystem& m_filesystem;
    io::IOutputHandler& m_outputhandler;
};
}