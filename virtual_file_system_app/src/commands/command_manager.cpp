#include "command_manager.hpp"

#include <memory>
#include <sstream>
#include <cctype>
#include <stack>

#include "commands.hpp"
#include "../helper/container_helper.hpp"
#include "../helper/number.hpp"

namespace virtualfilesystem
{


CommandManager::CommandManager(io::IOutputHandler& output_handler)
{
    history_offset = 0;

    m_command_map["cp"] = std::make_unique<virtualfilesystem::CopyCommand>(file_system);
    m_command_map["mkdir"] = std::make_unique<virtualfilesystem::MakeDirectoryCommand>(file_system);
    m_command_map["create"] = std::make_unique<virtualfilesystem::MakeFileCommand>(file_system);
    m_command_map["ls"] = std::make_unique<virtualfilesystem::ListDirectoryCommand>(file_system);
    m_command_map["cd"] = std::make_unique<virtualfilesystem::ChangeDirectoryCommand>(file_system);

    for (auto const& pair : m_command_map)
        suggestion_list.push_back(pair.first);
}

CommandResult CommandManager::execute_line(const std::string& line)
{
    auto [command, commandArgs] = split_command(line);
    
    if (command == "exit")
        return CommandResult(CommandResultType::Exit);

    //add to history
    if (history_list.size() >= MAX_HISTORY_SIZE)
        history_list.pop_front();

    history_list.push_back(line);

    if (!m_command_map.contains(command))
    {
        //if it's empty don't error it
        if (command.empty())
        {
            return CommandResult(CommandResultType::Empty);
        }
        
        std::ostringstream oss;
        oss << "'" << command << "'" << " command not recognized.";
        PrintBuffer printbuffer;
        printbuffer.add_error(oss.str());
        return CommandResult(CommandResultType::Empty, printbuffer);
    }        

    return m_command_map[command]->handle_command(commandArgs);
}

std::string CommandManager::get_suggestion(const std::string& line)
{
    
    auto [command, commandArgs] = split_command(line);
    
    if (command.empty())
        return std::string();

    size_t found = std::string::npos;

    //if it's only command then check commands, otherwise directories and files
    if (commandArgs.size() <= 1)
    {
        // check commands
        for (std::string& possibleSuggestion : suggestion_list)
        {
            found = possibleSuggestion.find(line);

            if (found == 0)
            {
                return possibleSuggestion.substr(line.length(),
                                                 possibleSuggestion.length() - line.length());
            }
        }
    }
    else
    {
        //gets args only since we aren't dealing with command
        std::string argsOnly = line.substr(command.length()+1);


        for (std::shared_ptr<Node> nodePtr : file_system.GetNodeList())
        {
            found = nodePtr->name.find(argsOnly);

            if (found == 0)
            {
                //argsOnly
                return nodePtr->name.substr(argsOnly.length(),
                                            nodePtr->name.length() - argsOnly.length());
            }
        }
    }

    return "";
}

const std::string& CommandManager::get_current_full_directory_path() const
{
    return file_system.current_full_path;
}

void CommandManager::increment_history_offset(int amount)
{
    history_offset += amount;

    if (history_offset < 0)
        history_offset = 0;
    else if (history_offset > helper::safe_size_to_int(history_list.size()))
        history_offset = helper::safe_size_to_int(history_list.size());

}

const std::string CommandManager::get_history_suggestion()
{    
    //used to go back to cleared console after looking at history
    if (history_offset == 0)
        return std::string();

    return history_list[history_list.size() - history_offset];
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
