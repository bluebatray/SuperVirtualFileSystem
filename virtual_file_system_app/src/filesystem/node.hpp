#pragma once

#include <ctime>
#include <memory>
#include <string>

#include "node_type.hpp"

namespace virtualfilesystem
{

struct Node
{
   public:
    Node(std::string _name, long long _size = 0, std::time_t _creationTime = std::time(nullptr))
        : name(std::move(_name)),
          size(_size),
          creationTime(_creationTime),
          lastModifiedTime(_creationTime)
    {
    }

    virtual NodeType get_node_type() const = 0;

    std::string name;
    long long size;
    std::time_t creationTime;
    std::time_t lastModifiedTime;
};

}  // namespace virtualfilesystem