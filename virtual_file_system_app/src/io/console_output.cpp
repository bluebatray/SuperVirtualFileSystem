#include "console_output.hpp"

#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

namespace io
{

void ConsoleOutput::set_color(Color color)
{

   
int translatedColor = get_mapped_color(color);

#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, translatedColor);
#else
    std::cout << translatedColor;
#endif
}

void ConsoleOutput::print_prompt(const std::string& prompt)
{
    std::cout << "\r"; // Reset cursor position
    set_color(Color::YELLOW);
    std::cout << prompt;  
}


#ifdef _WIN32
int ConsoleOutput::get_mapped_color(Color color)
{
    switch (color)
    {
        case Color::RESET:
            return 7;
        case Color::WHITE:
            return 15;
        case Color::GRAY:
            return 8;
        case Color::BLUE:
            return 9;
        case Color::GREEN:
            return 2;
        case Color::TEAL:
            return 11;
        case Color::PURPLE:
            return 5;
        case Color::YELLOW:
            return 6;
    }
    return 7;
}

#else

const char* ConsoleOutput::get_mapped_color(Color color)
{
    switch (color)
    {
        case Color::RESET:
            return "\033[0m";
        case Color::WHITE:
            return "\033[97m";
        case Color::GRAY:
            return "\033[90m";
        case Color::BLUE:
            return "\033[94m";
        case Color::GREEN:
            return "\033[32m";
        case Color::TEAL:
            return "\033[96m";
        case Color::PURPLE:
            return "\033[35m";
        case Color::YELLOW:
            return "\033[33m";
    }
    return "\033[0m";
}

#endif


ConsoleOutput::ConsoleOutput()
{
    std::cout.imbue(std::locale());
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

  /*printbuffer.set_color(Color::YELLOW);
printbuffer << m_filesystem.currentDirectory->name << m_filesystem.seperator_symbol << " > ";
printbuffer.set_color(Color::RESET);*/

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

    std::cout << "\033[" << (input.length() + prompt.length() + 1)
              << "G";  // Move cursor back "

    std::cout.flush();
    last_length = total_length;  // Update last known length

}

}