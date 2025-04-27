#include "Gui.hpp"

#include <iostream>
#include <string>


#include "virtual_file_system_lib.hpp"

// commands
#include "commands/copy_command.hpp"
#include "commands/list_directory_command.hpp"
#include "commands/make_directory_command.hpp"
#include "commands/prompt_command.hpp"
#include "commands/make_file_command.hpp"


const std::string PROMPT = " > ";

void Gui::run()
{
    virtualfilesystem::FileSystem file_system;

    std::map<std::string, std::unique_ptr<virtualfilesystem::ICommand>> commandMap;
    commandMap["cp"] = std::make_unique<virtualfilesystem::CopyCommand>(file_system);
    commandMap["mkdir"] = std::make_unique<virtualfilesystem::MakeDirectoryCommand>(file_system);
    commandMap["create"] = std::make_unique<virtualfilesystem::MakeFileCommand>(file_system);
    commandMap["ls"] = std::make_unique<virtualfilesystem::ListDirectoryCommand>(file_system, output_handler);
    commandMap[""] = std::make_unique<virtualfilesystem::PromptCommand>(file_system, output_handler);

    virtualfilesystem::CommandManager commandmanager(std::move(commandMap));

    // printfilesysteminfo();

    std::string typedline;
    std::string currentdirectory = "root";


    //testing
    commandmanager.execute_line("mkdir folder1");
    commandmanager.execute_line("mkdir folder2");
    commandmanager.execute_line("create file1 your mother");
    commandmanager.execute_line("ls");
    commandmanager.execute_line("");
    
    //maybe have enter/tab as commands?

    while (true)
    {
        io::InputEvent inputEvent = input_handler.read_event();

      
        if (inputEvent.type == io::InputEventType::Enter)
        {  // execute command

            output_handler.print_line();

            //if true, exit out of loop
            if (commandmanager.execute_line(typedline))
                break;
            
            typedline.clear();

            continue;
        }
        
        //not command, so let's handle suggestions
        switch (inputEvent.type)
        {
            case io::InputEventType::Tab:
                typedline += commandmanager.get_suggestion(typedline);
                break;
            case io::InputEventType::Backspace:
                if (!typedline.empty())
                    typedline.pop_back();
                break;
            case io::InputEventType::Character:
                typedline.push_back(inputEvent.character);
                break;
        }

        std::string suggestion = commandmanager.get_suggestion(typedline);
        output_handler.redraw_input(currentdirectory + PROMPT, typedline, suggestion);
    }
}

