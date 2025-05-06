#pragma once

#include "node.hpp"
#include <memory>

namespace virtualfilesystem
{

class Directory;

class File : public Node
{
   public:
    File(const std::string& _name, const std::string& _contents, long long _size, std::time_t _creationTime,
         std::weak_ptr<Directory> _parentDirectory)
        : Node(_name, _size, _creationTime), 
        parentDirectory(std::move(_parentDirectory)),
          contents(_contents)
    {
    }
    File(const File& _other, std::time_t _creationTime, std::weak_ptr<Directory> _parentDirectory)
        : Node(_other.name, _other.size, _creationTime),
          contents(_other.contents),
          parentDirectory(_other.parentDirectory){}

    NodeType get_node_type() const override { return NodeType::File; } 

    std::weak_ptr<Directory> parentDirectory;
    std::string contents;
};
}  // namespace virtualfilesystem