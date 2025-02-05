#pragma once

#include <string>

#include "i_command.hpp"

class CopyCommand : public ICommand{

public:
	std::string GetCommandSyntax() override;
	void HandleCommand() override;
};