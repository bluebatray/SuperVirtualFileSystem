#include "console_output.hpp"

#include <iostream>
#include <locale>

namespace io
{

ConsoleOutput::ConsoleOutput()
{
    std::cout.imbue(std::locale());
    m_cursorPosition = 0;
}

void ConsoleOutput::set_color(Color color)
{  
     std::cout << "\033[" << static_cast<int>(color) << "m";
 }

void ConsoleOutput::print_prompt(const std::string& prompt)
{
    std::cout << "\r"; // Reset cursor position
    set_color(Color::YELLOW);
    std::cout << prompt;  
}

void ConsoleOutput::move_insertion_point(int amount)
{
    m_cursorPosition += amount;
}

void ConsoleOutput::set_insertion_point(int index)
{
    m_cursorPosition = index;
}

int ConsoleOutput::get_insertion_point()
{
    return m_cursorPosition;
}

void ConsoleOutput::print(const std::string& message) const
{
    std::cout << message;
}

void ConsoleOutput::print_line()
{
    std::cout << std::endl;
}

void ConsoleOutput::print_line(const std::string& message)
{
    std::cout << message << '\n';
}

void ConsoleOutput::redraw_input(const std::string& prompt, const std::string& input,
                                 const std::string& suggested)
{
    print_prompt(prompt);

    // Print typed input in white
    set_color(Color::WHITE);

    std::cout << input;

    // Print suggested remaining part in gray
    if (!suggested.empty())
    {
        set_color(Color::GRAY);

        std::cout << suggested;
    }

    // Reset color back to normal
    set_color(Color::RESET);

    // Clear remaining characters if previous input was longer
    size_t total_length = input.length() + suggested.length();

    static size_t last_length = 0;  // Track previous input length

    //if we have less characters now, we need to redraw and clear out the old area
    if (total_length < last_length)
    {
        std::cout << std::string(last_length - total_length, ' ');  // Overwrite extra chars
        print_prompt(prompt);

        set_color(Color::WHITE);
        std::cout << input;
    }

    //std::cout << "\033[" << (prompt.length() + input.length() + 1) << "G";  // Move cursor back to end of typed part
    std::cout << "\033[" << (prompt.length() + m_cursorPosition + 1) << "G";  // Move cursor back to end of typed part

    std::cout.flush();
    last_length = total_length;  // Update last known length

}

}