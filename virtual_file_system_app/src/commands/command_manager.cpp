#include "command_manager.hpp"

#include "copy_command.hpp"
#include "i_command.hpp"
#include "list_directory_command.hpp"
#include "make_directory_command.hpp"

namespace virtualfilesystem
{

// CommandManager::CommandManager() : m_filesystem(), m_outputhandler() { //setup default commands
//	this->m_command_map = {
//		{"cp", new CopyCommand(m_filesystem)},
//		{"mkdir", new MakeDirectoryCommand(m_filesystem)},
//		{"ls", new ListDirectoryCommand(m_filesystem, m_outputhandler)}
//	};
// }

CommandManager::CommandManager(std::map<std::string, std::unique_ptr<ICommand>>&& command_map)
{
    this->m_command_map = std::move(command_map);
}

void CommandManager::execute_line(const std::string& line)
{
    std::vector parsedValues = parse_line_to_vector(line);

    if (!parsedValues.empty() && m_command_map.contains(parsedValues[0]))
    {
       
        if (parsedValues.size() > 1)
        {
            std::vector<std::string> args(&parsedValues[1], &parsedValues[parsedValues.size() - 1] + 1);
            m_command_map[parsedValues[0]]->handle_command(args);
        }
        else
        {
            std::vector<std::string> args;
            m_command_map[parsedValues[0]]->handle_command(args);
        }

         
        
    }
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

}  // namespace virtualfilesystem
