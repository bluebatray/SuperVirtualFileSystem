#include "Gui.hpp"

#include <string>
#include <iostream>

#include "virtual_file_system_lib.hpp"
#include "commands/command_manager.hpp"

static constexpr auto IsEnter(const char ch) -> bool { return ch == 13 || ch == '\n'; }
static constexpr auto IsTab(const char ch) -> bool { return ch == 9 || ch == '\t'; }
static constexpr auto IsBackspace(const char ch) -> bool { return ch == 127 || ch == '\b'; }

const std::string PROMPT = " > ";


void Gui::run()
{
	CommandManager commandManager;

	PrintFileSystemInfo();

	std::string typedLine;
	std::string currentDirectory = "root";

	
	output_handler.Print(currentDirectory + PROMPT);

	while (true) {
	
		const char ch = input_handler.ReadChar();
					
		if (IsEnter(ch)) { //execute command

			output_handler.PrintLine("");

			if (typedLine == "exit") { //escape
				output_handler.PrintLine("Exiting...");
				break;
			}
						
			commandManager.ExecuteLine(typedLine);
			typedLine.clear();

		}else if (IsTab(ch)) { //add rest of suggestion
			
			typedLine += commandManager.GetSuggestion(typedLine);	

		}else if (IsBackspace(ch)) { //remove letter

			if (!typedLine.empty())
				typedLine.pop_back();

		}else { //add letter
			typedLine.push_back(ch);
		}

		std::string suggestion = commandManager.GetSuggestion(typedLine);
		output_handler.RedrawInput(currentDirectory + PROMPT, typedLine, suggestion);
			
	}

}


