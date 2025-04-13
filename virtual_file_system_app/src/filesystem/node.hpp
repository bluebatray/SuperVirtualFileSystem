#pragma once

#include <ctime>
#include <memory>
#include <string>

namespace virtualfilesystem
{

struct Node
{
   public:
    Node(std::string _name, long long _size = 0, std::time_t _creationTime = std::time(nullptr))
        : name(std::move(_name)), size(_size), creationTime(_creationTime)
    {
    }
    std::string name;
    long long size;
    std::time_t creationTime;
};

}  // namespace virtualfilesystem