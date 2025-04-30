#pragma once

#include <ostream>
#include <iostream>
#include <vector>

namespace helper
{

template <typename Iter>
std::string join(Iter begin, Iter end, const char* const delimiter)
{
    using Value = typename std::iterator_traits<Iter>::value_type;
    std::ostringstream os;

    if (begin != end)
    {
        std::copy(begin, prev(end), std::ostream_iterator<Value>(os, delimiter));
        begin = prev(end);
    }
    if (begin != end)
    {
        os << *begin;
    }

    return os.str();
}


inline std::vector<std::string> split_string(const std::string& s, std::string delimiter)
{
    std::vector<std::string> vec;
    size_t pos = 0, prevPos = 0;
    while (1)
    {
        pos = s.find(delimiter, prevPos);
        if (pos == std::string::npos)
        {
            vec.push_back(s.substr(prevPos));
            return vec;
        }

        vec.push_back(s.substr(prevPos, pos - prevPos));
        prevPos = pos + delimiter.length();
    }

    return vec;
}

}  // namespace helper