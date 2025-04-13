#include "list_directory_command.hpp"

void virtualfilesystem::ListDirectoryCommand::HandleCommand(std::vector<std::string> args)
{
	for (Node node : m_filesystem.GetNodeList()) {
		m_outputhandler.print_line(node.name);
	}
}
