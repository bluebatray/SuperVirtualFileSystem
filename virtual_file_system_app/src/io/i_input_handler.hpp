#pragma once

#include <string>

namespace io
{

enum InputEventType
{
    Character,
    Enter,
    Tab,
    Backspace
};

struct InputEvent
{
    InputEventType type;
    char character = '\0';
};

class IInputHandler
{
   public:
    virtual ~IInputHandler() = default;
    virtual bool read(std::string&) = 0;
    virtual bool read_line(std::string&) = 0;
    virtual char read_char() = 0;
    virtual InputEvent read_event() = 0;
};

}  // namespace io