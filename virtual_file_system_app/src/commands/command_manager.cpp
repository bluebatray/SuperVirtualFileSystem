#include "command_manager.hpp"


void CommandManager::ExecuteCommand(const std::string& command)
{
  if(command_map_.contains(command))
  {
    command_map_[command]->HandleCommand();		
  }


}