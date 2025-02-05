
#pragma once

#include <string>

class ICommand {
public:
	virtual ~ICommand() = default;
	virtual std::string GetCommandSyntax() = 0;
	virtual void HandleCommand() = 0;
};
