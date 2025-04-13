#include "file_system.hpp"

#include <algorithm>
#include <chrono>

namespace virtualfilesystem
{

FileSystem::FileSystem()
{
    root = std::make_shared<Directory>(root_symbol, 0LL, GetCurrentEpoch(),
                                       std::weak_ptr<Directory>{});
    currentDirectory = root;
}

FileSystem::FileSystem(const std::string& serializedFileSystemPath)
{
    // todo
}

std::vector<Node> FileSystem::GetNodeList()
{
    std::vector<Node> nodeList;

    for (const auto& pair : currentDirectory->directoryMap)
    {
        nodeList.push_back(pair.first);
    }

    return nodeList;
}

// todo check and make sure dir isn't nested (just name)
ErrorCode FileSystem::MakeDir(const std::string& dirName)
{
    // check if directory already exists
    auto dirResult = GetDirectory(dirName);

    // if we have a directory, then it's made already, error out
    if (dirResult)
    {
        return ErrorCode(ErrorCode::Fail);
    }
    auto newDirectory = std::make_shared<Directory>("dirName", 0LL, GetCurrentEpoch(),
                                                    std::weak_ptr<Directory>(currentDirectory));

    currentDirectory->directoryMap.emplace(dirName, newDirectory);

    return ErrorCode(ErrorCode::Success);
}

ErrorCode FileSystem::CopyFile(const std::string& fileX, const std::string& fileY)
{
    // 1. check if fileX exists, if so get it
    auto originResult = GetDirectory(fileX);

    if (!originResult)
    {
        return originResult.error();
    }

    std::shared_ptr<Directory> dirOrigin = originResult.value();

    // 2. check if directoryX exists
    // 3. if new file name is specified use it, otherwise use name of fileX
    // 4. copy file to new directory (with new name if specified)

    return ErrorCode(ErrorCode::Success);
}

std::expected<std::shared_ptr<Directory>, ErrorCode> FileSystem::GetDirectory(
    const std::string& path)
{
    std::vector<std::string> directoryHierarchy = Split(path, seperator_symbol);

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
            if (tempCurrentDirectory->directoryMap.contains(nodeName))
            {
                tempCurrentDirectory = tempCurrentDirectory->directoryMap[nodeName];
            }
            else
            {
                return std::unexpected(ErrorCode::Fail);  // folder doesn't exist
            }
        }
    }

    return tempCurrentDirectory;
}

std::vector<std::string> FileSystem::Split(std::string s, const std::string& delimiter)
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
long long FileSystem::GetCurrentEpoch()
{
    return std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
}
}  // namespace virtualfilesystem