#include "list_directory_command.hpp"

#include <concepts>
#include <iomanip>

#include "../io/color.hpp"

namespace virtualfilesystem
{

CommandResult virtualfilesystem::ListDirectoryCommand::handle_command(std::vector<std::string> args)
{
    std::vector<std::shared_ptr<Node>> nodeList = m_filesystem.GetNodeList();

    PrintBuffer printbuffer;

    if (nodeList.empty()) {

        printbuffer.set_color(Color::WHITE);
        printbuffer << "Directory is empty.\n\n";
        printbuffer.set_color(Color::RESET);

        return CommandResult(CommandResultType::Success, std::move(printbuffer));
    }


    

    printbuffer << "\n";
    printbuffer.set_color(Color::GREEN);
    printbuffer << "Size\tModified\t\tName\n";
    printbuffer << "----\t--------\t\t----\n";

    for (auto node : nodeList)
    {
        std::tm localTime = *std::localtime(&node->lastModifiedTime);

         printbuffer.set_color(Color::WHITE);
        printbuffer << node->size << "\t" << std::put_time(&localTime, "%x %X") << "\t";

        if (node->get_node_type() == NodeType::Directory)
        {           
            printbuffer.set_color(Color::BLUE);
            printbuffer << node->name;
            printbuffer.set_color(Color::WHITE);
            printbuffer << "/";
        }
        else if (node->get_node_type() == NodeType::File)
        {
            printbuffer.set_color(Color::WHITE);
            printbuffer << node->name;           
        }

         printbuffer << "\n";
         
    }

    printbuffer.set_color(Color::RESET);
    printbuffer << "\n";

    return CommandResult(CommandResultType::Success, std::move(printbuffer));

}

}  // namespace virtualfilesystem