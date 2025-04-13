#pragma once

#include <string>
#include <vector>

#include "i_command.hpp"
#include "../filesystem/file_system.hpp"

namespace virtualfilesystem {

	class CopyCommand : public ICommand {

	public:
		CopyCommand(FileSystem& filesystem) : m_filesystem(filesystem) {}

		void HandleCommand(std::vector<std::string> args) override;

	private:
		FileSystem& m_filesystem;
	};
}