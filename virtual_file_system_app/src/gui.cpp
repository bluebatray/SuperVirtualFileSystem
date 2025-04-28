#include "Gui.hpp"

#include <iostream>
#include <string>

#include "commands/command_result.hpp"
#include "virtual_file_system_lib.hpp"


void Gui::run()
{
    // printfilesysteminfo();

    std::string typedline;
    std::string currentdirectory = "root";


    //testing
    execute_and_print("mkdir folder1");
    execute_and_print("mkdir folder2");
    execute_and_print("create file1 text in file");
    execute_and_print("ls");
    
    output_handler.redraw_input(get_prompt(), typedline, "");

    while (true)
    {
        io::InputEvent inputEvent = input_handler.read_event();
      
        if (inputEvent.type == io::InputEventType::Enter)
        {  // execute command

            output_handler.print_line();

            //if true, exit out of loop
            virtualfilesystem::CommandResult commandResult = commandmanager.execute_line(typedline);

            if (commandResult.type == virtualfilesystem::CommandResultType::Exit)
                break;
            
            if (commandResult.type == virtualfilesystem::CommandResultType::Success) {
                print_result(commandResult);                
            }

            typedline.clear();
            output_handler.redraw_input(get_prompt(), typedline, "");

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
        output_handler.redraw_input(get_prompt(), typedline, suggestion);
    }
}

void Gui::print_result(const virtualfilesystem::CommandResult& commandResult)
{
    for (const auto& token : commandResult.token.get_tokens())
    {
        output_handler.set_color(token.color);
        output_handler.print(token.text);
    }
}

void Gui::execute_and_print(const std::string& line)
{
   auto result = commandmanager.execute_line(line);
   print_result(result);
}

std::string Gui::get_prompt()
{
    return commandmanager.get_current_directory_name() + "/ > ";
}

