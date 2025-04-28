#pragma once

#include "print_buffer.hpp"

namespace virtualfilesystem
{
	enum class CommandResultType {
		Success,
		Invalid,
		Empty,
		Exit
	};

	struct CommandResult {
        CommandResultType type;
        PrintBuffer token;
	};

}