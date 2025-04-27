#pragma once

#include <memory>

#include "filesystem/file_system.hpp"
#include "io/i_input_handler.hpp"
#include "io/i_output_handler.hpp"
#include "commands/command_manager.hpp"

class Gui
{
   public:
    Gui(io::IInputHandler& input_handler, io::IOutputHandler& output_handler)
        : input_handler(input_handler), output_handler(output_handler)
    {
    }
    void run();

   private:

    io::IInputHandler& input_handler;
    io::IOutputHandler& output_handler;
};
