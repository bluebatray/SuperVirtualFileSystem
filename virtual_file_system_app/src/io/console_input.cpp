#include "console_input.hpp"

#include <iostream>
#include <string>

#include <conio.h>

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
    char c =  getch();

     if (c && c != 224)
        return c;

     return getch();

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
    char ch = getch();

    if (ch == 13 || ch == '\n')
        return InputEvent(InputEventType::Enter,  NULL);

     if (ch == 9 || ch == '\t')
        return InputEvent(InputEventType::Tab, NULL);

     if (ch == 127 || ch == '\b')
         return InputEvent(InputEventType::Backspace, NULL);


     //special key
     if (ch < 0) {
         ch = getch(); //special keys have 2 parts, let's get the 2nd part and see what it is

         switch (ch)
         {
             case 72:   //arrow up
                 return InputEvent(InputEventType::UpArrow, NULL);
             case 80:   //arrow down
                 return InputEvent(InputEventType::DownArrow, NULL);
             case 75:   //arrow left
                 return InputEvent(InputEventType::LeftArrow, NULL);
             case 77:   //arrow right
                 return InputEvent(InputEventType::RightArrow, NULL);
             case 83:   //delete
                 return InputEvent(InputEventType::Delete, NULL);
         }

          return InputEvent(InputEventType::Unused, NULL);
      }

    return InputEvent(InputEventType::Character, ch);
}

}  // namespace io