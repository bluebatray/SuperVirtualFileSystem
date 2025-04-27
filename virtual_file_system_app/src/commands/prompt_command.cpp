#include "prompt_command.hpp"

void virtualfilesystem::PromptCommand::handle_command(std::vector<std::string> args)
{
    m_outputhandler.set_color(io::color::YELLOW);
    m_outputhandler << m_filesystem.currentDirectory->name << m_filesystem.seperator_symbol << " > ";
    m_outputhandler.set_color(io::color::RESET);
}
