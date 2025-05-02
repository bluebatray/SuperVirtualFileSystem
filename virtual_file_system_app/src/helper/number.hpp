#pragma once

namespace helper {

inline int safe_size_to_int(size_t size)
{
    return static_cast<int>(std::min(size, static_cast<size_t>(std::numeric_limits<int>::max())));
}

}