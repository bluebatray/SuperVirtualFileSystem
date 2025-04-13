
#pragma once

#include <vector>
#include <string>

#include "virtual_file_system_lib.hpp"

namespace virtualfilesystem {

	class ICommand {
	public:

		virtual ~ICommand() = default;
		virtual void HandleCommand(std::vector<std::string> args) = 0;
	};
}