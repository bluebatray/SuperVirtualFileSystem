#include "gui.hpp"

#include <iostream>
#include <string>

#include "commands/command_result.hpp"
#include "virtual_file_system_lib.hpp"

#include "helper/number.hpp"

void Gui::run()
{
    // printfilesysteminfo();

   

    //testing
    execute_and_print("mkdir \"folder 1\"");
    execute_and_print("mkdir folder2");
    execute_and_print("mkdir another1");
    execute_and_print("cd \"folder 1\"");
    execute_and_print("create file1 text in file");
    
    execute_and_print("cd ..");
    execute_and_print("cp \"folder 1\" folder2/");

    execute_and_print("ls");
    

    std::string typedline;

    output_handler.redraw_input(get_prompt(), typedline);

    while (true)
    {
        io::InputEvent inputEvent = input_handler.read_event();
      
        if (inputEvent.type == io::InputEventType::Enter)
        {  // execute command
            output_handler.redraw_input(get_prompt(), typedline);
            output_handler.print_line();

            //if true, exit out of loop
            virtualfilesystem::CommandResult commandResult = commandmanager.execute_line(typedline);

            if (commandResult.type == virtualfilesystem::CommandResultType::Exit)
                break;
            
            print_result(commandResult);   

            
            output_handler.move_insertion_point(-output_handler.get_insertion_point());

            typedline.clear();
            output_handler.redraw_input(get_prompt(), typedline);
            
            continue;
        }


        std::string suggestion;
        int insertionPoint;

        switch (inputEvent.type)
        {
            case io::InputEventType::Delete:
                if (output_handler.get_insertion_point() < typedline.length())
                {
                    typedline.erase(output_handler.get_insertion_point(), 1);
                }
                break;
            case io::InputEventType::Tab:
                suggestion = commandmanager.get_suggestion(typedline);
                insertionPoint = helper::safe_size_to_int(suggestion.length());
                output_handler.move_insertion_point(insertionPoint);
                typedline += suggestion;
                suggestion = "";

                break;
            case io::InputEventType::Backspace:
                if (!typedline.empty())
                    typedline.erase(output_handler.get_insertion_point()-1,1);

                suggestion = commandmanager.get_suggestion(typedline);
                if (output_handler.get_insertion_point() > 0)
                    output_handler.move_insertion_point(-1);
                break;
            case io::InputEventType::Character:
                //typedline.push_back(inputEvent.character);
                typedline.insert(typedline.begin() + output_handler.get_insertion_point(),
                                 inputEvent.character);
                suggestion = commandmanager.get_suggestion(typedline);
                output_handler.move_insertion_point(1);
                break;
            case io::InputEventType::DownArrow:
                commandmanager.increment_history_offset(-1);

                typedline = commandmanager.get_history_suggestion();
                output_handler.set_insertion_point(static_cast<int>(typedline.length()));
                break;
            case io::InputEventType::UpArrow:
                commandmanager.increment_history_offset(1);
                typedline = commandmanager.get_history_suggestion();
                
                insertionPoint = helper::safe_size_to_int(typedline.length());
                output_handler.set_insertion_point(insertionPoint);

                break;
            case io::InputEventType::LeftArrow:
                suggestion = commandmanager.get_suggestion(typedline);
                if (output_handler.get_insertion_point() > 0)
                    output_handler.move_insertion_point(-1);

                break;
            case io::InputEventType::RightArrow:
                suggestion = commandmanager.get_suggestion(typedline);

                //autocomplete the rest if we're at the end, otherwise just move right by 1
                if (output_handler.get_insertion_point() == typedline.length())
                {
                    suggestion = commandmanager.get_suggestion(typedline);
                    insertionPoint = helper::safe_size_to_int(typedline.length());
                    output_handler.move_insertion_point(insertionPoint);
                    typedline += suggestion;
                    suggestion = "";
                }
                else {
                    if (output_handler.get_insertion_point() < typedline.length())
                        output_handler.move_insertion_point(1);
                }
             
                break;
            default:
                continue;
        }

        
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
    return commandmanager.get_current_full_directory_path() + "/ > ";
}

