#include "console_input.hpp"

#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h> 
#endif

namespace io
{

bool ConsoleInput::read_line(std::string& input)
{
    std::getline(std::cin, input);
    return !input.empty();
}
bool ConsoleInput::read(std::string& input)
{
    std::cin >> input;
    return !input.empty();
}

// todo make non windows version
char ConsoleInput::read_char()
{
#ifdef _WIN32
    char ch = 0;
    DWORD mode, count;
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    // Get current console mode
    GetConsoleMode(hInput, &mode);

    // Disable line buffering & echo
    SetConsoleMode(hInput, mode & ~(ENABLE_LINE_INPUT | ENABLE_ECHO_INPUT));

    ReadConsoleA(hInput, &ch, 1, &count, NULL);

    // Restore original mode
    SetConsoleMode(hInput, mode);

    return ch;
#endif

}
InputEvent ConsoleInput::read_event()
{
    const char ch = read_char();

    if (ch == 13 || ch == '\n')
        return InputEvent(InputEventType::Enter,  NULL);

     if (ch == 9 || ch == '\t')
        return InputEvent(InputEventType::Tab, NULL);
     if (ch == 127 || ch == '\b')
         return InputEvent(InputEventType::Backspace, NULL);
        
    return InputEvent(InputEventType::Character, ch);
}

}  // namespace io