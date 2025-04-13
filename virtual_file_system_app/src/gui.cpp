#include "Gui.hpp"

#include <string>
#include <iostream>

#include "virtual_file_system_lib.hpp"
#include "commands/command_manager.hpp"

//commands
#include "commands/copy_command.hpp"
#include "commands/make_directory_command.hpp"
#include "commands/list_directory_command.hpp"

#include "filesystem/file_system.hpp"

static constexpr auto is_enter(const char ch) -> bool { return ch == 13 || ch == '\n'; }
static constexpr auto is_tab(const char ch) -> bool { return ch == 9 || ch == '\t'; }
static constexpr auto is_backspace(const char ch) -> bool { return ch == 127 || ch == '\b'; }

const std::string PROMPT = " > ";

void Gui::run()
{
	virtualfilesystem::FileSystem file_system;

	// todo fix listdirectorycommand consutrctor

	std::map<std::string, std::unique_ptr<virtualfilesystem::ICommand>> commandMap;
	commandMap["cp"] = std::make_unique<virtualfilesystem::CopyCommand>(file_system);
	commandMap["mkdir"] = std::make_unique<virtualfilesystem::MakeDirectoryCommand>(file_system);
	//commandMap["ls"] = std::make_unique<virtualfilesystem::ListDirectoryCommand>(file_system);

	virtualfilesystem::CommandManager commandmanager(std::move(commandMap));

	//printfilesysteminfo();

	std::string typedline;
	std::string currentdirectory = "root";

	
	output_handler.print(currentdirectory + PROMPT);

	while (true) {
	
		const char ch = input_handler.read_char();
					
		if (is_enter(ch)) { //execute command

			output_handler.print_line("");

			if (typedline == "exit") { //escape
				output_handler.print_line("exiting...");
				break;
			}
						
			commandmanager.execute_line(typedline);
			typedline.clear();

		}else if (is_tab(ch)) { //add rest of suggestion
			
			typedline += commandmanager.get_suggestion(typedline);	

		}else if (is_backspace(ch)) { //remove letter

			if (!typedline.empty())
				typedline.pop_back();

		}else { //add letter
			typedline.push_back(ch);
		}

		std::string suggestion = commandmanager.get_suggestion(typedline);
		output_handler.redraw_input(currentdirectory + PROMPT, typedline, suggestion);
			
	}

}




