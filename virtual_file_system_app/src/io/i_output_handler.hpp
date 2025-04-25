#pragma once

#include <string>
#include <sstream>

namespace io
{

class IOutputHandler
{
   public:
    virtual ~IOutputHandler() = default;
    virtual void print(const std::string& message) const = 0;
    virtual void print_line() = 0;
    virtual void print_line(const std::string& message) = 0;
    virtual void redraw_input(const std::string& prompt, const std::string& input,
                              const std::string& sugggested) = 0;
    virtual void set_color(int color) = 0;
};

//template support for <<
template <typename T>
const IOutputHandler& operator<<(const IOutputHandler& out, const T& value)
{
    std::ostringstream oss;
    oss << value;
    out.print(oss.str());
    return out;
}

#ifdef _WIN32
namespace color
{
constexpr int RESET = 7;
constexpr int WHITE = 15;
constexpr int GRAY = 8;
constexpr int BLUE = 9;
constexpr int GREEN = 2;
constexpr int TEAL = 11;
constexpr int PURPLE = 5;
constexpr int YELLOW = 6;
}

#else
namespace color
{
constexpr const char* RESET = "\033[0m";
constexpr const char* WHITE = "\033[97m";
constexpr const char* GRAY = "\033[90m";
constexpr const char* BLUE = "\033[94m";
constexpr const char* GREEN = "\033[32m";
constexpr const char* TEAL = "\033[96m";  
constexpr const char* PURPLE = "\033[35m";
constexpr const char* YELLOW = "\033[33m";

}  // namespace color
#endif  // _WIN32

}  // namespace io
