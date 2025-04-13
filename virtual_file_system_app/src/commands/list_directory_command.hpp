#pragma once

#include "i_command.hpp"

#include "../filesystem/file_system.hpp"
#include "../io/i_output_handler.hpp"

namespace virtualfilesystem {
	class ListDirectoryCommand : public ICommand {
	public:
		ListDirectoryCommand(FileSystem& filesystem, io::IOutputHandler& outputhandler) : m_filesystem(filesystem), m_outputhandler(outputhandler) {}

		void HandleCommand(std::vector<std::string> args) override;

	private:
		FileSystem& m_filesystem;
		io::IOutputHandler& m_outputhandler;
	};
		
}