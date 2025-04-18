#pragma once

#include <string>

#include "i_output_handler.hpp"

namespace io
{

class ConsoleOutput : public IOutputHandler
{
   public:
    void print(const std::string& message) override;
    void print_line(const std::string& message) override;
    void redraw_input(const std::string& prompt, const std::string& input,
                      const std::string& sugggested) override;

   private:
    void SetColor(int color);
};
}  // namespace io