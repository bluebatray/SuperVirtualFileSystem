
#pragma once

#include <string>
#include "virtual_file_system_lib.hpp"

class ICommand {
public:
 
	virtual ~ICommand() = default;
	virtual void HandleCommand() = 0;
};
