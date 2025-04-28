#pragma once

#include <string>

#include "i_output_handler.hpp"

namespace io
{

class ConsoleOutput : public IOutputHandler
{
   public:
    ConsoleOutput();
    void print(const std::string& message) const override;
    void print_line() override;
    void print_line(const std::string& message) override;
    void redraw_input(const std::string& prompt, const std::string& input,
                      const std::string& sugggested) override;

    void set_color(Color color) override;
    void print_prompt(const std::string& prompt);

    private:
#ifdef _WIN32
    int get_mapped_color(Color color);
#else
    const char* get_mapped_color(Color color);
#endif
};

}  // namespace io

