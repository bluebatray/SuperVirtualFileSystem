#include "file_system.hpp"

#include <algorithm>
#include <chrono>

#include "../helper/container_helper.hpp"

namespace virtualfilesystem
{

FileSystem::FileSystem()
{
    // static_assert(std::is_constructible_v<Directory, const std::string&, long long, std::time_t,
    // std::weak_ptr<Directory>>);
    root = std::make_shared<Directory>(root_symbol_display, 0LL, get_current_epoch(),
                                       std::weak_ptr<Directory>{});
    currentDirectory = root;
    full_directory_structure.push_back(root_symbol_display);

    calculate_full_path();
}

FileSystem::FileSystem(const std::string& serializedFileSystemPath)
{
    // todo
}

std::vector<std::shared_ptr<Node>> FileSystem::GetNodeList() const
{
    std::vector<std::shared_ptr<Node>> result;

    for (const auto& node : currentDirectory->nodeMap)
    {
        result.push_back(node.second);
    }

    return result;
}

// todo check and make sure dir isn't nested (just name)
ErrorCode FileSystem::make_directory(const std::string& dirName)
{
    // check if directory already exists
    auto dirResult = get_directory(dirName);

    // if we have a directory, then it's made already, error out
    if (dirResult)
    {
        return ErrorCode(ErrorCode::AlreadyExists);
    }
    std::shared_ptr<Directory> newDirectory = std::make_shared<Directory>(
        dirName, 0LL, get_current_epoch(), std::weak_ptr<Directory>(currentDirectory));

    currentDirectory->nodeMap.emplace(dirName, newDirectory);

    return ErrorCode(ErrorCode::Success);
}

ErrorCode FileSystem::make_file(const std::string& filex, const std::string& fileText)
{
    auto currentTime = get_current_epoch();
    std::shared_ptr<File> newFile =
        std::make_shared<File>(filex, fileText, fileText.length(), currentTime,
                               std::weak_ptr<Directory>(currentDirectory));
    /* File(std::string _name, std::string _contents, long long _size, std::time_t _creationTime,
          std::weak_ptr<Directory> _parentDirectory)*/
    currentDirectory->nodeMap.emplace(newFile->name, newFile);
    currentDirectory->lastModifiedTime = currentTime;
    currentDirectory->size += newFile->size;

    return ErrorCode(ErrorCode::Success);
}


ErrorCode FileSystem::copy_node(const std::string& originfullpathnode, const std::string& destfullpathnode)
{
    // split directory and file so we can deal with them seperately
    auto resultOriginNode = get_node_with_path(originfullpathnode);

    if (!resultOriginNode)
        return resultOriginNode.error();

    // origin node verified, get dest path
    auto resultDestNode = get_node_name_with_path(destfullpathnode);

    if (!resultDestNode)
        return resultDestNode.error();  // target directory is missing

    std::shared_ptr<Node> originNodePtr = resultOriginNode.value().second;  
    
    std::shared_ptr<Directory> destNodeParentDirectory = resultDestNode.value().first;
    std::string destName;

    //if they didn't specify new node name, let's use the origin one
    if (resultDestNode.value().second.empty())
    {
        destName = originNodePtr->name;
    }
    else {
        destName = resultDestNode.value().second;

        // check if destination name isn't already there
        auto destDirectoryIt = destNodeParentDirectory->nodeMap.find(destName);
        if (destDirectoryIt != destNodeParentDirectory->nodeMap.end())
        {
            return ErrorCode::AlreadyExists;
        }
    }
  
    // ok we've finally verified everything.
    // check if it's file or folder we're copying
    if (originNodePtr->get_node_type() == NodeType::Directory)
    {
        // go through the entire directory and copy over everything
    }
    else if (originNodePtr->get_node_type() == NodeType::File)
    {
        std::shared_ptr<File> originFile = std::static_pointer_cast<File>(originNodePtr);
        std::weak_ptr<Directory> weakParent(destNodeParentDirectory);

        std::shared_ptr<File> destFile =
            std::make_shared<File>(*originFile, get_current_epoch(), weakParent);

        destNodeParentDirectory->nodeMap.emplace(destName, destFile);
        destNodeParentDirectory->size += destFile->size;
    }
 
    // in case new nodetypes are added, error out for now
    return ErrorCode(ErrorCode::Fail);
}

ErrorCode FileSystem::change_directory(const std::string& directoryFullName)
{
    auto result = get_directory(directoryFullName);

    if (!result)
    {
        return result.error();
    }

    // valid, traverse and build the new structure
    currentDirectory = result.value();

    full_directory_structure.clear();

    full_directory_structure.push_back(root_symbol_display);

    std::shared_ptr<Directory> dir = currentDirectory;

    while (dir && dir != root)
    {
        full_directory_structure.insert(full_directory_structure.begin() + 1, dir->name);
        dir = dir->parentDirectory.lock();
    }

    calculate_full_path();

    return ErrorCode(ErrorCode::Success);
}

std::expected<std::shared_ptr<Directory>, ErrorCode> FileSystem::get_directory(
    const std::string& path)
{
    std::vector<std::string> directoryHierarchy = split(path, seperator_symbol);

    if (directoryHierarchy.size() == 0)
        return std::unexpected(ErrorCode::Fail);

    std::shared_ptr<Directory> tempCurrentDirectory = currentDirectory;

    // loop through only folders
    for (size_t i = 0; i < directoryHierarchy.size(); i++)
    {
        const std::string& nodeName = directoryHierarchy[i];

        if (nodeName == parent_directory_symbol)
        {
            if (auto parent = tempCurrentDirectory->parentDirectory.lock())
            {
                tempCurrentDirectory = parent;
            }
            else
            {
                // at root already, discard
            }
        }
        else if (nodeName == root_symbol)
        {
            tempCurrentDirectory = root;
        }
        else
        {
            if (tempCurrentDirectory->nodeMap.contains(nodeName) &&
                tempCurrentDirectory->nodeMap[nodeName]->get_node_type() == NodeType::Directory)
            {
                std::shared_ptr<Node> childNode = tempCurrentDirectory->nodeMap[nodeName];
                tempCurrentDirectory = std::dynamic_pointer_cast<Directory>(childNode);
            }
            else
            {
                return std::unexpected(ErrorCode::Fail);  // folder doesn't exist
            }
        }
    }

    return tempCurrentDirectory;
}

std::expected<std::pair<std::shared_ptr<Directory>, std::string>, ErrorCode>
FileSystem::get_node_name_with_path(const std::string& nodefullpath)
{
    // split directory and file so we can deal with them seperately
    size_t indexPathFileBreak = nodefullpath.rfind(seperator_symbol);

    std::shared_ptr<Directory> directory;
    std::string nodeName;

    if (indexPathFileBreak == std::string::npos)
    {
        nodeName = nodefullpath;
        directory = currentDirectory;
    }
    else
    {
        nodeName = nodefullpath.substr(indexPathFileBreak + 1);

        auto result = get_directory(nodefullpath.substr(0, indexPathFileBreak));

        if (result)
        {
            directory = result.value();
        }
        else
        {
            // directory doesn't exist
            return std::unexpected(result.error());
        }
    }

    return std::make_pair(directory, nodeName);
}

std::expected<std::pair<std::shared_ptr<Directory>, std::shared_ptr<Node>>, ErrorCode>
FileSystem::get_node_with_path(const std::string& nodefullpath)
{
    auto directoryNameResult = get_node_name_with_path(nodefullpath);

    if (!directoryNameResult) {
        return std::unexpected(directoryNameResult.error());
    }

    std::shared_ptr<Directory> directory = directoryNameResult.value().first;
    std::string nodeName = directoryNameResult.value().second;

    auto it = directory->nodeMap.find(nodeName);

    if (it == directory->nodeMap.end())
    {
        // node doesn't exist
        return std::unexpected(ErrorCode::NotFound);
    }

    return std::make_pair(directory, it->second);
}

std::vector<std::string> FileSystem::split(std::string s, const std::string& delimiter)
{
    std::vector<std::string> splitStringVector;
    size_t pos = 0;
    while (pos < s.size())
    {
        pos = s.find(delimiter);
        std::string temp = s.substr(0, pos);

        // check if there's spaces, if so ignore
        if (!temp.empty() && !std::all_of(temp.begin(), temp.end(), isspace))
        {
            splitStringVector.push_back(temp);
        }

        s.erase(0, pos + delimiter.length());
    }
    return splitStringVector;
}
std::time_t FileSystem::get_current_epoch()
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}

void FileSystem::calculate_full_path()
{
    current_full_path = helper::join(full_directory_structure.begin(),
                                     full_directory_structure.end(), seperator_symbol.c_str());
}
}  // namespace virtualfilesystem
