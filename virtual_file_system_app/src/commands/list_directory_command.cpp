#include "list_directory_command.hpp"

#include <concepts>
#include <iomanip>

void virtualfilesystem::ListDirectoryCommand::handle_command(std::vector<std::string> args)
{
    m_outputhandler.set_color(io::color::GREEN);
    m_outputhandler << "Size\tCreated\t\t\tName\n";
    m_outputhandler << "----\t-------\t\t\t----\n";

    for (auto node : m_filesystem.GetNodeList())
    {
        std::tm localTime = *std::localtime(&node->creationTime);

        if (node->GetNodeType() == NodeType::Directory)
        {
            m_outputhandler.set_color(io::color::WHITE);
            m_outputhandler << node->size << "\t" << std::put_time(&localTime, "%x %X") << "\t";
            m_outputhandler.set_color(io::color::BLUE);
            m_outputhandler << node->name;
            m_outputhandler.set_color(io::color::WHITE);
            m_outputhandler << "/\n";
        }
        else if (node->GetNodeType() == NodeType::File)
        {
            m_outputhandler.set_color(io::color::WHITE);
        }
       
        
    }


    m_outputhandler.set_color(io::color::RESET);
    m_outputhandler << "\n";

}
