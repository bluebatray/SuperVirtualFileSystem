#pragma once

#include "io/i_input_handler.hpp"
#include "io/i_output_handler.hpp"
#include "commands/command_manager.hpp"

class Gui
{
   public:
    Gui(io::IInputHandler& input_handler, io::IOutputHandler& output_handler)
        : input_handler(input_handler), 
        output_handler(output_handler), commandmanager(output_handler)
    {
    }
    void run();
    void print_result(const virtualfilesystem::CommandResult& commandResult);

   private:

    void execute_and_print(const std::string& line);
    std::string get_prompt();

    virtualfilesystem::CommandManager commandmanager;

    io::IInputHandler& input_handler;
    io::IOutputHandler& output_handler;
};
