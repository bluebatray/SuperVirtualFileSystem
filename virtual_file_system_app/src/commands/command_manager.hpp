#pragma once

#include "i_command.hpp"

#include "../filesystem/file_system.hpp"
#include "../io/i_output_handler.hpp"
#include <map>
#include <vector>

namespace virtualfilesystem
{

class CommandManager
{
   public:
    CommandManager(std::map<std::string, std::unique_ptr<ICommand>>&& command_map);

    void execute_line(const std::string& line);
    std::string get_suggestion(const std::string& input);

   private:
    std::vector<std::string> parse_line_to_vector(const std::string& line);
    std::map<std::string, std::unique_ptr<ICommand>> m_command_map;
};

}  // namespace virtualfilesystem