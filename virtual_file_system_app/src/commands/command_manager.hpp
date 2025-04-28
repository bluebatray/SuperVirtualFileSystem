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
    CommandManager(io::IOutputHandler& output_handler);
   
    CommandResult execute_line(const std::string& line);
    std::string get_suggestion(const std::string& input);
    void handle_suggestion(const std::string& input);
    const std::string& get_current_directory_name() const;

   private:
    std::vector<std::string> parse_line_to_vector(const std::string& line);
    std::map<std::string, std::unique_ptr<ICommand>> m_command_map;

    std::pair<std::string, std::vector<std::string>> split_command(const std::string& line);

    FileSystem file_system;
    std::vector <std::string> suggestion_list;
    std::vector <std::string> history_list;
};

}  // namespace virtualfilesystem