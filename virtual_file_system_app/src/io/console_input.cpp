#include "console_input.hpp"

#include <iostream>
#include <string>

#include <windows.h>

bool ConsoleInput::ReadLine(std::string& input)
{
	std::getline(std::cin, input);
	return !input.empty();
}
bool ConsoleInput::Read(std::string& input) 
{
	std::cin >> input;
	return !input.empty();
}

char ConsoleInput::ReadChar() {
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
}
