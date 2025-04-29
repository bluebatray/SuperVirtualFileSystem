#pragma once

#include <vector>
#include <sstream>

#include "print_token.hpp"

namespace virtualfilesystem
{

class PrintBuffer
{
public:
    void set_color(Color color)
    {
        current_color = color;
    }

    const std::vector<PrintToken> get_tokens() const { return tokens;}
    void add_error(const std::string& desc, const std::string& command, const std::string& usage) 
    {
        set_color(Color::RED);
        //printbuffer.add_error("Missing parameter", args[0], " NewDirectory");

        *this << "[Error] ";

        set_color(Color::WHITE);
        *this << desc << "\n";

        *this << "Usage: ";
        set_color(Color::YELLOW);
        *this << command << " " <<  usage << "\n ";

        set_color(Color::RESET);      
    }
    PrintBuffer& operator<<(const std::string& str) 
    { 
        tokens.push_back(PrintToken{current_color, str});
        return *this;
    }
   
    PrintBuffer& operator<<(const char* str)
    {
        tokens.push_back(PrintToken{current_color, std::string(str)});
        return *this;
    }

    template <typename T>
    PrintBuffer& operator<<(const T& value)
    {
        std::ostringstream oss;
        oss << value;
        tokens.push_back(PrintToken{current_color, oss.str()});
        return *this;
    }

private:
 std::vector<PrintToken> tokens;
 Color current_color;

};

}  // namespace virtualfilesystem