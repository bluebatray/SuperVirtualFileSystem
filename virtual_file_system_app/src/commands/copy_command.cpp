#include "copy_command.hpp"

#include <string>
#include <iostream>

namespace virtualfilesystem {
	void CopyCommand::HandleCommand(std::vector<std::string> args)
	{
		std::cout << " handle copy command " << "\n";

		PrintFileSystemInfo();

		m_filesystem.CopyFile(args[0], args[1]);

	}
}