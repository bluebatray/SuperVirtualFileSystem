#include "console_output.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>

void ConsoleOutput::SetColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

#define RESET_COLOR 7
#define WHITE_COLOR 15
#define GRAY_COLOR 8

#else

#define RESET   "\033[0m"
#define WHITE   "\033[37m"
#define GRAY    "\033[90m"

#endif

void ConsoleOutput::Print(const std::string& message)
{
	std::cout << message;
}

void ConsoleOutput::PrintLine(const std::string& message) {
	std::cout << message << std::endl;
}


void ConsoleOutput::RedrawInput(const std::string& prompt, const std::string& input, const std::string& suggested) {
    std::cout << "\r" << prompt; // Reset cursor position

    // Print typed input in white
#ifdef _WIN32
    SetColor(WHITE_COLOR);
#else
    std::cout << WHITE;
#endif
    std::cout << input;

    // Print suggested remaining part in gray
    if (!suggested.empty()) {
#ifdef _WIN32
        SetColor(GRAY_COLOR);
#else
        std::cout << GRAY;
#endif
        std::cout << suggested;
    }

    // Reset color back to normal
#ifdef _WIN32
    SetColor(RESET_COLOR);
#else
    std::cout << RESET;
#endif

    // Clear remaining characters if previous input was longer
    size_t total_length = input.length() + suggested.length();

    static size_t last_length = 0; // Track previous input length

    if (total_length < last_length) {
        std::cout << std::string(last_length - total_length, ' ');  // Overwrite extra chars
        std::cout << "\r" << prompt << input; // Reset cursor position
    }

    std::cout << "\033[" << (input.length() + prompt.length() + 1) << "G"; // Move cursor back to after "VirtualSystem> "


    std::cout.flush();
    last_length = total_length; // Update last known length
}