#include "command_manager.hpp"

#include <memory>
#include "commands.hpp"


namespace virtualfilesystem
{


CommandManager::CommandManager(io::IOutputHandler& output_handler)
{
    m_command_map["cp"] = std::make_unique<virtualfilesystem::CopyCommand>(file_system);
    m_command_map["mkdir"] = std::make_unique<virtualfilesystem::MakeDirectoryCommand>(file_system);
    m_command_map["create"] = std::make_unique<virtualfilesystem::MakeFileCommand>(file_system);
    m_command_map["ls"] = std::make_unique<virtualfilesystem::ListDirectoryCommand>(file_system);
}

CommandResult CommandManager::execute_line(const std::string& line)
{
    auto [command, commandArgs] = split_command(line);
    
    if (command == "exit")
        return CommandResult(CommandResultType::Exit, {});

    return m_command_map[command]->handle_command(commandArgs);
}

std::string CommandManager::get_suggestion(const std::string& prefix)
{
    std::string suggested = "cp dir1 dir2";

    size_t found = suggested.rfind(prefix);

    if (found == std::string::npos)
    {
        return "";
    }

    // return suggestion (only what's left from what's already typed)
    return suggested.substr(found + prefix.length(), suggested.length() - prefix.length());
}

void CommandManager::handle_suggestion(const std::string& typedline)
{

  /*  std::string suggestion = get_suggestion(typedline);
    output_handler.redraw_input(currentdirectory + PROMPT, typedline, suggestion);*/

}

const std::string& CommandManager::get_current_directory_name() const
{
    return file_system.currentDirectory->name;
}

std::vector<std::string> CommandManager::parse_line_to_vector(const std::string& line)
{
    std::vector<std::string> parsedValues;

    int beginIndex = 0;
    int endLength = 0;

    for (char ch : line)
    {
        if (ch == ' ')
        {
            parsedValues.push_back(line.substr(beginIndex, endLength));
            beginIndex += endLength+1; //add 1 to move past space
            endLength = 0;
        }

        endLength++;
    }

    parsedValues.push_back(line.substr(beginIndex, endLength));

    return parsedValues;
}

std::pair<std::string, std::vector<std::string>> CommandManager::split_command(const std::string& line)
{
    std::vector<std::string> parsedValues;

    int beginIndex = 0;
    int endLength = 0;

    for (char ch : line)
    {
        if (ch == ' ')
        {
            parsedValues.push_back(line.substr(beginIndex, endLength));
            beginIndex += endLength + 1;  // add 1 to move past space
            endLength = 0;
        }
        else
        {
            endLength++;
        }
        
    }

    parsedValues.push_back(line.substr(beginIndex, endLength));

    if (parsedValues.empty())
        return {"", {}};
    return {parsedValues[0], {parsedValues.begin() + 1, parsedValues.end()}};
}

}  // namespace virtualfilesystem
