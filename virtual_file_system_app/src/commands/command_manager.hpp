#pragma once

#include "i_command.hpp"

#include <vector>
#include <map>

class CommandManager {

public:
	explicit CommandManager(std::map<std::string, ICommand*> command_map)
		: command_map_(std::move(command_map)){}

	void ExecuteCommand(const std::string& command);

private:
	std::map<std::string, ICommand*> command_map_;
};

