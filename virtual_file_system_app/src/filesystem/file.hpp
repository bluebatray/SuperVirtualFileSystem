#pragma once

#include "node.hpp"
#include <memory>

namespace virtualfilesystem
{

class Directory;

class File : public Node
{
   public:
    File(std::string _name, long long _size, std::time_t _creationTime,
         std::weak_ptr<Directory> _parentDirectory)
        : Node(std::move(_name), _size, _creationTime), parentDirectory(std::move(_parentDirectory))
    {
    }

    NodeType GetNodeType() const override { return NodeType::File; } 

    std::weak_ptr<Directory> parentDirectory;
};
}  // namespace virtualfilesystem