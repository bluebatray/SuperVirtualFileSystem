#pragma once

#include "i_command.hpp"

#include <vector>
#include <map>

class CommandManager {

public:
	CommandManager();

	void ExecuteLine(const std::string& line);
	std::string GetSuggestion(const std::string& input);

private:
	std::vector<std::string> ParseLineToVector(const std::string& line);
	std::map<std::string, ICommand*> command_map_;
};

