#pragma once

#include <map>
#include <memory>
#include <set>

#include "node.hpp"

namespace virtualfilesystem
{

class File;

class Directory : public Node
{
   public:
    Directory(const std::string& _name, long long _size, std::time_t _creationTime,
              std::weak_ptr<Directory> _parentDirectory)
        : Node(_name, _size, _creationTime), parentDirectory(std::move(_parentDirectory))
    {
    }

    NodeType get_node_type() const override { return NodeType::Directory; }
    std::weak_ptr<Directory> parentDirectory;
    std::map<std::string, std::shared_ptr<Node>> nodeMap;
};
}  // namespace virtualfilesystem
