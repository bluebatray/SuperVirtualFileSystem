#include "list_directory_command.hpp"

#include <time.h>
#include <concepts>
#include <iomanip>

#include "../../io/color.hpp"

namespace virtualfilesystem
{

CommandResult virtualfilesystem::ListDirectoryCommand::handle_command(std::vector<std::string> args)
{
    std::vector<std::shared_ptr<Node>> nodeList = m_filesystem.GetNodeList();
    PrintBuffer printbuffer;

    // if it's empty directory, exit out
    if (nodeList.empty())
    {
        printbuffer.set_color(Color::WHITE);
        printbuffer << "Directory is empty.\n\n";
        printbuffer.set_color(Color::RESET);

        return CommandResult(CommandResultType::Success, std::move(printbuffer));
    }

    // first go through list and find the biggest file, we will format text based on this
    long long biggestFile = 0;
    for (std::shared_ptr<Node> node : nodeList)
    {
        if (node->size > biggestFile)
            biggestFile = node->size;
    }

    int numDigitsOfBiggestFile = get_digits(biggestFile);
    int dateSize = format_time(nodeList[0]->lastModifiedTime).length();

    // headers
    int spaceBetween = 4;

    // print header
    printbuffer << "\n";
    printbuffer.set_color(Color::GREEN);
    printbuffer << size_string
                << std::string(numDigitsOfBiggestFile - size_string.length() + spaceBetween, ' ')
                << modified_string
                << std::string(dateSize - modified_string.length() + spaceBetween, ' ') << name_string
                << "\n";

    // lines under header
    printbuffer << std::string(size_string.length(), '-')
                << std::string(numDigitsOfBiggestFile - size_string.length() + spaceBetween, ' ')
                << std::string(modified_string.length(), '-')
                << std::string(dateSize - 8 + spaceBetween, ' ')
                << std::string(name_string.length(), '-') << "\n";

    // data
    printbuffer.set_color(Color::WHITE);
    int compensatingTabs = 0;

    for (std::shared_ptr<Node> node : nodeList)
    {
        compensatingTabs = get_digits(node->size);

        printbuffer << node->size
                    << std::string(numDigitsOfBiggestFile - compensatingTabs + spaceBetween, ' ')
                    << format_time(node->lastModifiedTime) << std::string(spaceBetween, ' ');

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

std::string ListDirectoryCommand::format_time(time_t time)
{
    std::tm localTime;

#ifdef _WIN32
    localtime_s(&localTime, &time);
#else
    localtime_r(&time, &localTime);
#endif

    std::ostringstream oss;
    oss << std::put_time(&localTime, "%x %X");
    return oss.str();
}

long long ListDirectoryCommand::get_digits(long long size)
{
    if (size == 0)
        return 1;

    int digits = 0;
    while (size > 0)
    {
        size /= 10;
        digits++;
    }

    return digits;
}

}  // namespace virtualfilesystem
