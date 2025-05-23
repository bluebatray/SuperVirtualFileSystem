#pragma once

#include <string>
#include <sstream>
#include "color.hpp"

namespace io
{

class IOutputHandler
{
   public:
    virtual ~IOutputHandler() = default;
    virtual void print(const std::string& message) const = 0;
    virtual void print_line() = 0;
    virtual void print_line(const std::string& message) = 0;
    virtual void redraw_input(const std::string& prompt, const std::string& input = std::string(),
                              const std::string& sugggested = std::string()) = 0;
    virtual void set_color(Color color) = 0;
    virtual void move_insertion_point(int amount) = 0;
    virtual void set_insertion_point(int index) = 0;
    virtual int get_insertion_point() = 0;
};


}  // namespace io
