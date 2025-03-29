#include "command_manager.hpp"

#include "i_command.hpp"
#include "copy_command.hpp"

CommandManager::CommandManager() { //setup default commands
	this->command_map_ = { {"cp", new CopyCommand()} };
}

void CommandManager::ExecuteLine(const std::string& line)
{
	std::vector parsedValues = ParseLineToVector(line);

	if(!parsedValues.empty() && command_map_.contains(parsedValues[0]))
	{
		std::vector<std::string> args(&parsedValues[1], &parsedValues[parsedValues.size() - 1] + 1);
		command_map_[parsedValues[0]]->HandleCommand(args);
	}
}

std::string CommandManager::GetSuggestion(const std::string& prefix)
{

	std::string suggested = "cp dir1 dir2";

	size_t found = suggested.rfind(prefix);

	if (found == std::string::npos) {
		return "";
	}

	//return suggestion (only what's left from what's already typed)
	return suggested.substr(found + prefix.length(), suggested.length() - prefix.length());

}

std::vector<std::string> CommandManager::ParseLineToVector(const std::string& line)
{
	std::vector<std::string> parsedValues;

	int beginIndex = 0;
	int endLength = 0;

	for (char ch : line) {

		if (ch == ' ') {
			parsedValues.push_back(line.substr(beginIndex, endLength));
			beginIndex += endLength;
			endLength = 0;
		}

		endLength++;
	}

	parsedValues.push_back(line.substr(beginIndex, endLength));

	return parsedValues;
}
