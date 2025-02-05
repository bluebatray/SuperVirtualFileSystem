#pragma once

#include <string>

#include "i_command.hpp"

class CopyCommand : public ICommand{

public:
	void HandleCommand() override;
};