#pragma once

#include <ostream>

namespace helper {

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

}