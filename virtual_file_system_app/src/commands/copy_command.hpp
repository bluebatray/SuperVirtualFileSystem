#pragma once

#include <string>
#include <vector>

#include "i_command.hpp"

class CopyCommand : public ICommand{

public:
	void HandleCommand(std::vector<std::string> args) override;
};