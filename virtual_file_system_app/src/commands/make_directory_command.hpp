#pragma once

#include <string>
#include "../filesystem/file_system.hpp"
#include "i_command.hpp"

namespace virtualfilesystem {
	class MakeDirectoryCommand : public ICommand {

	public:
		MakeDirectoryCommand(FileSystem& filesystem) : m_fileSystem(filesystem){}
		void HandleCommand(std::vector<std::string> args) override;

	private:
		FileSystem& m_fileSystem;
	};

}