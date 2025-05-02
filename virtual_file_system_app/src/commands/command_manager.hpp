#pragma once

#include "i_command.hpp"

#include "../filesystem/file_system.hpp"
#include "../io/i_output_handler.hpp"
#include <map>
#include <vector>
#include <deque>

namespace virtualfilesystem
{

class CommandManager
{
   public:
    CommandManager(io::IOutputHandler& output_handler);
   
    CommandResult execute_line(const std::string& line);
    std::string get_suggestion(const std::string& line);
    const std::string& get_current_full_directory_path() const;
    void increment_history_offset(int amount);
    const std::string get_history_suggestion();

   private:
    std::vector<std::string> parse_line_to_vector(const std::string& line);
    std::map<std::string, std::unique_ptr<ICommand>> m_command_map;

    std::pair<std::string, std::vector<std::string>> split_command(const std::string& line);
    
    std::vector <std::string> suggestion_list;
    std::deque<std::string> history_list;

    int history_offset = 0;
    const size_t MAX_HISTORY_SIZE = 50;
    
    FileSystem file_system;
};

}  // namespace virtualfilesystem