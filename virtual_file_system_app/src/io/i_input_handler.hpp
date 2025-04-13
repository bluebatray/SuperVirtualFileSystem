#pragma once

#include <string>

namespace io
{
class IInputHandler
{
   public:
    virtual ~IInputHandler() = default;
    virtual bool read(std::string&) = 0;
    virtual bool read_line(std::string&) = 0;
    virtual char read_char() = 0;
};

}  // namespace io