#pragma once

#include "i_command.hpp"

#include "../filesystem/file_system.hpp"

namespace virtualfilesystem {

class ChangeDirectoryCommand : public ICommand {
	public:
    ChangeDirectoryCommand(FileSystem& filesystem) : m_filesystem(filesystem){}
    CommandResult handle_command(std::vector<std::string> args) override;

	private:
    FileSystem& m_filesystem;
};

}