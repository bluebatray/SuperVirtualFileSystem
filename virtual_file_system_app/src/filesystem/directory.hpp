#pragma once

#include <map>
#include <memory>
#include <vector>

#include "node.hpp"

namespace virtualfilesystem
{

class File;

class Directory : public Node
{
   public:
    Directory(std::string _name, long long _size, long long _creationTime,
              std::weak_ptr<Directory> _parentDirectory)
        : Node(std::move(_name), _size, _creationTime), parentDirectory(std::move(_parentDirectory))
    {
    }

    NodeType GetNodeType() const override { return NodeType::Directory; } 
    std::weak_ptr<Directory> parentDirectory;
    std::map<std::string, std::shared_ptr<Directory>> directoryMap;
    std::vector<std::shared_ptr<File>> fileList;
    std::vector<std::shared_ptr<Directory>> directoryList;
};
}  // namespace virtualfilesystem