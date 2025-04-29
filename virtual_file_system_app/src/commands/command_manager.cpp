#include "command_manager.hpp"

#include <memory>
#include <sstream>
#include <cctype>

#include "commands.hpp"


namespace virtualfilesystem
{


CommandManager::CommandManager(io::IOutputHandler& output_handler)
{
    m_command_map["cp"] = std::make_unique<virtualfilesystem::CopyCommand>(file_system);
    m_command_map["mkdir"] = std::make_unique<virtualfilesystem::MakeDirectoryCommand>(file_system);
    m_command_map["create"] = std::make_unique<virtualfilesystem::MakeFileCommand>(file_system);
    m_command_map["ls"] = std::make_unique<virtualfilesystem::ListDirectoryCommand>(file_system);

    for (auto const& pair : m_command_map)
        suggestion_list.push_back(pair.first);
}

CommandResult CommandManager::execute_line(const std::string& line)
{
    auto [command, commandArgs] = split_command(line);
    
    if (command == "exit")
        return CommandResult(CommandResultType::Exit, {});

    //add to history
    history_list.push_back(line);

    if (!m_command_map.contains(command))
        return CommandResult(CommandResultType::Empty, {});

    return m_command_map[command]->handle_command(commandArgs);
}

std::string CommandManager::get_suggestion(const std::string& prefix)
{
    
    size_t found = std::string::npos;

    

    //for (auto directory : file_system.currentDirectory->directoryList)
    //{
    //    
    //    found = directory->name.rfind(prefix);

    //    if (found != std::string::npos)
    //    {
    //        return directory->name.substr(found + prefix.length(),
    //                                      directory->name.length() - prefix.length());
    //    }
    //}

    // check commands
    for (std::string& possibleSuggestion : suggestion_list)
    {
        found = possibleSuggestion.rfind(prefix);

        if (found != std::string::npos)
        {
            return possibleSuggestion.substr(found + prefix.length(),
                                            possibleSuggestion.length() - prefix.length());
        }        
    }
    


   return "";
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

    std::string current;
    bool in_quotes = false;

    for (size_t i = 0; i < line.size(); ++i)
    {
        char ch = line[i];

        if (ch == '"')
        {
            in_quotes = !in_quotes;  // Toggle inside quotes
        }
        else if ((ch == ' ' || ch == '\t') && !in_quotes)
        {
            if (!current.empty())
            {
                parsedValues.push_back(current);
                current.clear();
            }
        }
        else
        {
            current += ch;
        }
    }

    if (!current.empty())
    {
        parsedValues.push_back(current);
    }

    if (parsedValues.empty())
        return {"", {}};

    return {parsedValues[0], {parsedValues.begin(), parsedValues.end()}};
}

}  // namespace virtualfilesystem
