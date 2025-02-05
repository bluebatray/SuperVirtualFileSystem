#include "Gui.hpp"

#include <string>
#include <iostream>

#include "virtual_file_system_lib.hpp"
#include "commands/i_command.hpp"
#include "commands/copy_command.hpp"
#include "commands/command_manager.hpp"

const std::string PROMPT = " > ";
//#include "i_command.hpp"

void Gui::run()
{
	
	std::map<std::string, ICommand*> commandMap = {{"cp", new CopyCommand()}};

	CommandManager commandManager(std::move(commandMap));

	PrintFileSystemInfo();

	std::string line;
	std::string suggested = "cp dir1 dir2";
	std::string currentDirectory = "root";

	
	output_handler.print(currentDirectory + PROMPT);

	while (true) {
	
		const char ch = input_handler.read_char();

		int charValue = static_cast<unsigned char>(ch);
		//std::cout << charValue << std::endl;
		
		
		if (ch == 13 || ch == '\n') { //enter

			output_handler.print_line("");

			if (line == "exit") { //escape
				output_handler.print_line("Exiting...");
				break;
			}
			

			//execute command
			commandManager.ExecuteCommand(line);
			suggested.clear();
			line.clear();

		}
		else if (ch == 9 || ch == '\t') { //tab
			//complete suggested
			line += suggested;
			suggested.clear();
			
		}
		else if (ch == 127 || ch == '\b') { //backspace

			if (!line.empty())
				line.pop_back();

			suggested = find_suggestion(line);
		}
		else { //add letter
			line.push_back(ch);
			suggested = find_suggestion(line);
		}

		output_handler.redraw_input(currentDirectory + PROMPT, line, suggested);
			

	}

		
}

const std::string Gui::find_suggestion(std::string prefix)
{
	std::string suggested = "cp dir1 dir2";

	size_t found = suggested.rfind(prefix);

	if (found == std::string::npos) {
		return "";
	}
	
	//return suggestion (only what's left from what's already typed)
	return suggested.substr(found+prefix.length(), suggested.length() - prefix.length());
}


