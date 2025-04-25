#include "list_directory_command.hpp"

#include <concepts>

void virtualfilesystem::ListDirectoryCommand::handle_command(std::vector<std::string> args)
{
    for (auto node : m_filesystem.GetNodeList())
    {
        if (node->GetNodeType() == NodeType::Directory)
        {
            m_outputhandler.set_color(io::color::BLUE);
            m_outputhandler << node->name;
            m_outputhandler.set_color(io::color::WHITE);
            m_outputhandler << "/ ";
            m_outputhandler.set_color(io::color::BLUE);
            m_outputhandler << std::to_string(node->size) << "\n";
        }
        else if (node->GetNodeType() == NodeType::File)
        {
            m_outputhandler.set_color(io::color::WHITE);
        }
       
        
        m_outputhandler.set_color(io::color::RESET);
    }
}
